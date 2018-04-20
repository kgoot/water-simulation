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
                if (glm::length(p_offset) <= r) {
                    glm::vec3 p = origin + p_offset;
                    _particles.emplace_back(p);
                    ++added;
                }
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

}