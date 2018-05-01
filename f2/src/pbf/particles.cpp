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
#include "color.h"

#include "../common.h"

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


    void Particles::updateColor(Particle &p) {
      double ratio = pow(1.0/sqrt(pow(p.vel.x,2) + pow(p.vel.y,2) + pow(p.vel.z,2)),4);
      vec3 hsl_color = rgbToHsl(vec3(0.1686f, 0.73333f, 1.0f));

      hsl_color.z = 1.0  - ratio;
      if (hsl_color.z < 0.58) {
        hsl_color.z = 0.58;
      }

      vec3 rgb_color = hslToRgb(hsl_color);
      p.color = vec4(rgb_color, 1.0);
    }

    void Particles::update(double dt) {
        float timestep = (float) dt;

        for (Particle &p : _particles) {
            p.vel += glm::vec3(0, -9.8f, 0) * timestep;
            p.pred_pos = p.pos + p.vel * timestep;
            updateColor(p);
        }


        build_spatial_map();

        double rho0 = 6000.0;
        double epsilon = 600.0;
        double k = 0.001;
        double n = 4.0;
        double delta_q = 0.001 * _h;

        float vorticity_epsilon = 0.00002f;
        float c = 0.0000001f;


        for (int i = 0; i < 2; i++) {
            for (Particle &p : _particles) {
                find_neighbors(p);
                p.rho = get_rho(p);
                p.lambda = lambda(p.rho, rho0, p, epsilon);
            }

            for (Particle &p : _particles) {
                double lambda_i = p.lambda;

                glm::vec3 delta_p(0.f);
                for (Particle *neighbor : p.neighbors) {
                    double lambda_j = neighbor->lambda;
                    double s_corr_j = s_corr(p, *neighbor, k, delta_q, n);
                    delta_p += (float) (lambda_i + lambda_j + s_corr_j) * w_gradient_spiky(p, *neighbor);
                }
                delta_p /= rho0;
                p.delta_p = delta_p;
            }

            for (Particle &p : _particles) {
                p.pred_pos += p.delta_p;
            }
        }


        for (Thing *t : _scene->get_collidables()) {
            for (Particle &p : _particles)
                t->collide(p);
        }


        for (Particle &p : _particles) {
            p.vel = (p.pred_pos - p.pos) / timestep;
            p.pos = p.pred_pos;
            p.vel += find_vorticity(p) * timestep * vorticity_epsilon + find_viscosity(p) * c;
        }
    }

    void Particles::clear() {
        _particles.clear();
    }


    glm::ivec3 Particles::cell(glm::vec3 pos) {
        int x = (int) (pos.x / _h);
        int y = (int) (pos.y / _h);
        int z = (int) (pos.z / _h);

        return glm::ivec3(x, y, z);
    }


    int Particles::hash_position(glm::ivec3 cell) {
        return (cell.x * 31 + cell.y) * 31 + cell.z;
    }


    void Particles::build_spatial_map() {
        for (const auto &entry : _spatial_map) {
            delete (entry.second);
        }
        _spatial_map.clear();

        for (Particle &p : _particles) {
            int hash_pos = hash_position(cell(p.pred_pos));
            if (_spatial_map.find(hash_pos) == _spatial_map.end()) {
                vector<Particle *> *box_p = new vector<Particle *>();
                box_p->push_back(&p);
                _spatial_map[hash_pos] = box_p;
            } else {
                _spatial_map.find(hash_pos)->second->push_back(&p);
            }
        }
    }


    void Particles::find_neighbors(Particle &p) {
        p.neighbors.clear();
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                for (int k = -1; k <= 1; k++) {
                    int hash_pos = hash_position(cell(p.pred_pos) + glm::ivec3(i, j, k));
                    if (_spatial_map.find(hash_pos) != _spatial_map.end()) {
                        for (Particle *neighbor : *_spatial_map[hash_pos]) {
                            if (glm::distance(p.pred_pos, neighbor->pred_pos) < _h) {
                                p.neighbors.push_back(neighbor);
                            }
                        }
                    }
                }
            }
        }
    }


    double Particles::w_poly_6(double r) {
        if (r >= _h) {
            return 0.0;
        }
        return 315.0 / (64.0 * M_PI * pow(_h, 9.0)) * pow(_h * _h - r * r, 3.0);
    }


    glm::vec3 Particles::w_gradient_spiky(Particle &p, Particle &neighbor) {
        glm::vec3 r = p.pred_pos - neighbor.pred_pos;
        if (glm::length(r) >= _h || glm::length(r) < EPS_F) {
            return glm::vec3(0.f);
        }
        return (float) (-45.0 / (M_PI * powf(_h, 6.0))) * powf(_h - glm::length(r), 2.0) * glm::normalize(r);
    }


    double Particles::get_rho(Particle &p) {
        double total = 0.0;

        for (Particle *neighbor : p.neighbors) {
            double r = glm::distance(p.pred_pos, neighbor->pred_pos);
            total += w_poly_6(r);
        }

        return total;
    }


    double Particles::C(double rho, double rho0) {
        return rho / rho0 - 1;
    }


    double Particles::lambda(double rho, double rho0, Particle &p, double epsilon) {
        double total = epsilon;
        glm::vec3 self_constraint(0.f);
        for (Particle *neighbor : p.neighbors) {
            glm::vec3 grad = -w_gradient_spiky(p, *neighbor) / (float) rho0;
            total += glm::dot(grad, grad);
            self_constraint += grad;
        }

        return -C(rho, rho0) / (total + glm::dot(self_constraint, self_constraint));
    }


    double Particles::s_corr(Particle &p, Particle &neighbor, double k, double delta_q, double n) {
        double r = glm::distance(p.pred_pos, neighbor.pred_pos);
        if (w_poly_6(delta_q) == 0.0) {
            return 0.0;
        }
        return -k * pow(w_poly_6(r) / w_poly_6(delta_q), n);
    }


    glm::vec3 Particles::find_vorticity(Particle &p) {
        glm::vec3 w(0.f);
        for (Particle* neighbor : p.neighbors) {
            glm::vec3 v_ij = neighbor->vel - p.vel;
            glm::vec3 grad = w_gradient_spiky(p, *neighbor);
            w += glm::cross(v_ij, grad);
        }
        float vorticity = glm::length(w);

        glm::vec3 eta(0.f);
        for (Particle* neighbor : p.neighbors) {
            eta += vorticity * w_gradient_spiky(p, *neighbor);
        }
        glm::vec3 N(0.f);
        if (glm::length(eta) > EPS_F) {
            N = normalize(eta);
        }

        return glm::cross(N, w);
    }


    glm::vec3 Particles::find_viscosity(Particle &p) {
        glm::vec3 viscosity(0.f);
        for (Particle *neighbor : p.neighbors) {
            glm::vec3 v_ij = neighbor->vel - p.vel;
            viscosity += v_ij * (float) w_poly_6(glm::distance(p.pred_pos, neighbor->pred_pos));
        }
        return viscosity;
    }
}
