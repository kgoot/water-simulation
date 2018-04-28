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

        // TODO: Calculate lambdas
        build_spatial_map();

        double rho0 = 6300.0;
        double epsilon = 600.0;
        double k = 0.0001;
        double n = 4.0;
        double delta_q = 0.001 * _h;
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
                delta_p += (float) (lambda_i + lambda_j + s_corr_j) * w_gradient_spiky(p, *neighbor); // + s_corr_j
            }
            delta_p /= rho0;
            p.pred_pos += delta_p;
        }


        for (Thing *t : _scene->get_collidables()) {
            for (Particle &p : _particles)
                t->collide(p);
        }


        for (Particle &p : _particles) {
            p.vel = (p.pred_pos - p.pos) / timestep;
            p.pos = p.pred_pos;
        }
    }

    void Particles::clear() {
        _particles.clear();
    }


    int Particles::hash_position(glm::vec3 pos) { //float
        int x = (int) (pos.x / _h);
        int y = (int) (pos.y / _h);
        int z = (int) (pos.z / _h);

        return (x * 31 + y) * 31 + z; // (float)
    }


    void Particles::build_spatial_map() {
        for (const auto &entry : _spatial_map) {
            delete (entry.second);
        }
        _spatial_map.clear();

        for (Particle &p : _particles) {
            int hash_pos = hash_position(p.pred_pos);
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
                    int hash_pos = hash_position(p.pred_pos + (float) _h * glm::vec3(i, j, k));
                    if (_spatial_map.find(hash_pos) != _spatial_map.end()) {
                        for (Particle *neighbor : *_spatial_map[hash_pos]) {
//                            if (&p != neighbor) {
                            p.neighbors.push_back(neighbor);
//                            }
                        }
                    }
                }
            }
        }
    }


    double Particles::w_poly_6(double r) {
//        double h = p.radius + neighbor.radius;
//        double r = glm::length(p.pos - neighbor.pos); // [0] ?
        if (r > _h) {
            return 0.0;
        }
        return 315 / (64 * M_PI * powf(_h, 9.0)) * powf(powf(_h, 2.0) - powf(r, 2.0), 3.0);
    }


    glm::vec3 Particles::w_gradient_spiky(Particle &p, Particle &neighbor) {
//        double h = p.radius + neighbor.radius;
        glm::vec3 r = p.pred_pos - neighbor.pred_pos;
        if (glm::length(r) > _h || glm::length(r) == 0.f) {
            return glm::vec3(0.f);
        }
        return (float) -(45 / (M_PI * powf(_h, 6.0)) * powf(_h - glm::length(r), 2.0)) * glm::normalize(r); // do I normalize r or the whole thing?
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
        double total = 0.0;
        glm::vec3 self_constraint(0.f);
        for (Particle *neighbor : p.neighbors) {
            glm::vec3 grad = -w_gradient_spiky(p, *neighbor) / (float) rho0;
            total += glm::dot(grad, grad);
            self_constraint += grad;
        }

        return -C(rho, rho0) / (total + glm::dot(self_constraint, self_constraint) + epsilon);
    }


    double Particles::s_corr(Particle &p, Particle &neighbor, double k, double delta_q, double n) {
        double r = glm::distance(p.pred_pos, neighbor.pred_pos);
        if (w_poly_6(delta_q) == 0.0) {
            return 0.0;
        }
        return -k * pow(w_poly_6(r) / w_poly_6(delta_q), n);
    }


    glm::vec3 Particles::find_vorticity(Particle &p) {
        glm::vec3 vorticity(0.f);
        for (Particle *neighbor : p.neighbors) {
            glm::vec3 v_ij = neighbor->vel - p.vel;
            glm::vec3 grad = w_gradient_spiky(p, *neighbor);
            vorticity += glm::cross(v_ij, grad);
        }
        return vorticity;
    }

    glm::vec3 Particles::find_vorticity_force(glm::vec3 vorticity, double epsilon) {
        return (float) epsilon * vorticity;
    }


}
