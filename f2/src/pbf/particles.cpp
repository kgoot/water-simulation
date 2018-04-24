//
// Created by Dillon Yao on 4/12/18.
//


#ifndef GLM_ENABLE_EXPERIMENTAL
#define GLM_ENABLE_EXPERIMENTAL
#endif

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "particles.h"
#include "../scene/camera.h"
#include "../core/input.h"
#include "../util/util.h"
#include "../scene/scene.h"

#include <math.h>
using namespace std;

namespace pbf {

  Particles::Particles() {
    _vao.bind();
    _vbo.bind();
    _vao.vertex_attr(0, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), offsetof(Particle, pos));
    _vbo.unbind();
    _vao.unbind();

    VertexShader vert;
    FragmentShader frag;
    vert.load_from_file("../shaders/basic.vert");
    frag.load_from_file("../shaders/basic.frag");
    vert.compile();
    frag.compile();

    _program.attach_shader(vert);
    _program.attach_shader(frag);
    _program.link();

    _program.use();
    glUniform1i(_program.get_uniform_location("vpheight"), Input::get()->poll_viewport().y);
    Input::get()->listen_on_resize([this](int width, int height) {
      _program.use();
      glUniform1i(_program.get_uniform_location("vpheight"), height);
    });
  }

  void Particles::render(Camera &camera) {
    if (_particles.size()) {
      _vbo.bind();
      _vbo.set_data(sizeof(Particle) * _particles.size(), &_particles[0], GL_STREAM_DRAW);
    }

    _program.use();
    glUniform1f(_program.get_uniform_location("radius"), PARTICLE_RADIUS);
    glUniform3fv(_program.get_uniform_location("eye"), 1, glm::value_ptr(camera.position()));
    glUniformMatrix4fv(_program.get_uniform_location("proj"), 1, GL_FALSE, glm::value_ptr(camera.get_proj()));
    glUniformMatrix4fv(_program.get_uniform_location("view"), 1, GL_FALSE, glm::value_ptr(camera.get_view()));
    glUniformMatrix4fv(_program.get_uniform_location("model"), 1, GL_FALSE, glm::value_ptr(glm::mat4(1.f)));
    _vao.bind();
    glDrawArrays(GL_POINTS, 0, (GLsizei) _particles.size());
  }

  void Particles::spawn_prism() {

  }

  void Particles::spawn_sphere(glm::vec3 &origin, float r, float density) {
    size_t added = 0;
    int dim_length = (int) (r * density);
    float offset = r / dim_length;
    for (int i = -dim_length; i < dim_length; ++i) {
      for (int j = -dim_length; j < dim_length; ++j) {
        for (int k = -dim_length; k < dim_length; ++k) {
          glm::vec3 ind(i, j, k);
          glm::vec3 p_offset = ind * offset;
          //                if (glm::length(p_offset) <= r) {
          glm::vec3 p = origin + p_offset;
          _particles.emplace_back(p);
          ++added;
          //                }
        }
      }
    }
    scoped_msg("Particles", "", 1);
    std::cout << "spawned " << added << " particles" << std::endl;
  }

  void Particles::update(double dt) {
    float timestep = (float) dt;

    for (Particle &p : _particles) {
      p.vel += glm::vec3(0, -9.8f, 0) * timestep;
      p.pred_pos = p.pos + p.vel * timestep;
    }
//    std::cout << ";lakjdsf";

    // TODO: Calculate lambdas
    double rho0 = 6300.0;
    double epsilon = 0.01;
    for (Particle &p : _particles) {
      std::vector<Particle *> neighbors_i = find_neighbors(p);
      double rho_i = getRho(p, &neighbors_i);
      double lambda_i = lambda(rho_i, rho0, p, &neighbors_i, epsilon);
      glm::vec3 delta_p = glm::vec3();
      for (Particle* neighbor : neighbors_i) {
        std::vector<Particle *> neighbors_j = find_neighbors(*neighbor);
        double rho_j = getRho(p, &neighbors_j);
        double lambda_j = lambda(rho_j, rho0, *neighbor, &neighbors_j, epsilon);
        delta_p += (float) (lambda_i + lambda_j) * wGradientSpiky(p, *neighbor);
      }
      delta_p /= rho0;
      if (delta_p != glm::vec3()) p.pred_pos += delta_p * timestep;
    }



    for (Thing *t : _scene->get_collidables()) {
      for (Particle &p : _particles)
        t->collide(p);
    }

    for (Particle &p : _particles) {
      p.pos = p.pred_pos;
    }
  }

  void Particles::clear() {
    _particles.clear();
  }


  int Particles::hash_position(Particle p) { //float
    int x = (int) floor(p.pos.x / (2 * p.radius));
    int y = (int) floor(p.pos.y / (2 * p.radius));
    int z = (int) floor(p.pos.z / (2 * p.radius));

    return (x * 31 + y) * 31 + z; // (float)
  }


  void Particles::build_spatial_map() {
    for (const auto &entry : _spatial_map) {
      delete(entry.second);
    }
    _spatial_map.clear();

    for (Particle &p : _particles) {
      int hash_pos = hash_position(p);
      if (_spatial_map.find(hash_pos) == _spatial_map.end()) {
        vector<Particle *> * box_p = new vector<Particle*>();
        box_p->push_back(&p);
        _spatial_map[hash_pos] = box_p;

      } else {
        _spatial_map.find(hash_pos)->second->push_back(&p);
      }
    }
  }


  vector<Particle *> Particles::find_neighbors(Particle p) {
    vector<Particle* >* neighbors = new vector<Particle *>();
    for (int i = -1; i <= 1; i++) {
      for (int j = -1; j <= 1; j++) {
        for (int k = -1; k <= 1; k++) {
          int hash_pos = hash_position(p);
          if (_spatial_map.find(hash_pos) != _spatial_map.end()) {
            for (Particle* neighbor : *_spatial_map[hash_pos]) {
              neighbors->push_back(neighbor);
            }
          }
        }
      }
    }
    return *neighbors;
  }


  double Particles::wPoly6(Particle p, Particle neighbor) {
    double h = p.radius + neighbor.radius;
//        double r = glm::length(p.pos - neighbor.pos); // [0] ?
    double r = glm::distance(p.pos, neighbor.pos);
    return 315 / (64 * M_PI * pow(h, 9.0)) * pow(pow(h, 2.0) - pow(r, 2.0), 3.0);
  }


  glm::vec3 Particles::wGradientSpiky(Particle p, Particle neighbor) {
    double h = p.radius + neighbor.radius;
    glm::vec3 r = p.pos - neighbor.pos;
    return (float) (45 / (M_PI * pow(h, 6.0)) * pow(h - glm::length(r), 2.0)) * r; // do I normalize r or the whole thing?
  }


  double Particles::getRho(Particle p, std::vector<Particle *> * neighbors) {
    double total = 0.0;

    for (Particle* neighbor : *neighbors) {
      total += wPoly6(p, *neighbor);
    }

    return total;
  }


  double Particles::C(double rho, double rho0) {
    return rho / rho0 - 1;
  }


  glm::vec3 Particles::cGradient(Particle p, Particle neighbor, double rho0) {
    // TODO: include case where k = i (?)
    return -wGradientSpiky(p, neighbor);
  }


  double Particles::lambda(double rho, double rho0, Particle p, std::vector<Particle *> * neighbors, double epsilon) {
    double total = 0.0;
    for (Particle* neighbor : *neighbors) {
        glm::vec3 grad = cGradient(p, *neighbor, rho0);
        total += pow(glm::length(cGradient(p, *neighbor, rho0)), 2.0);
    }

    return -C(rho, rho0) / (total + epsilon);
  }


}