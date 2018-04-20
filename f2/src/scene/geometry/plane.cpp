//
// Created by Dillon Yao on 4/16/18.
//

#include "plane.h"
#include "../../common.h"
#include <glm/gtc/type_ptr.hpp>

Plane::Plane() {
    _pos = glm::vec3();
    _n = WORLD_UP;
    _width = 1.f;
    _height = 1.f;

    _vao.bind();
    _vbo.bind();
    _vao.vertex_attr(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    update_points();
    _vbo.unbind();
    _vao.unbind();

    VertexShader vert;
    FragmentShader frag;
    vert.load_from_file("../shaders/plane.vert");
    frag.load_from_file("../shaders/plane.frag");
    vert.compile();
    frag.compile();

    _program.attach_shader(vert);
    _program.attach_shader(frag);
    _program.link();
}

void Plane::set(glm::vec3 p, glm::vec3 n, float width, float height) {
    _pos = p;
    _n = n;
    _width = width;
    _height = height;
    update_points();
}

void Plane::set_position(glm::vec3 p) {
    _pos = p;
    update_points();
}

void Plane::set_normal(glm::vec3 n) {
    _n = glm::normalize(n);
    update_points();
}

void Plane::set_dimensions(float width, float height) {
    _width = width;
    _height = height;
    update_points();
}

void Plane::render(Camera &camera) {
    _program.use();
    glUniformMatrix4fv(_program.get_uniform_location("proj"), 1, GL_FALSE, glm::value_ptr(camera.get_proj()));
    glUniformMatrix4fv(_program.get_uniform_location("view"), 1, GL_FALSE, glm::value_ptr(camera.get_view()));
    glUniformMatrix4fv(_program.get_uniform_location("model"), 1, GL_FALSE, glm::value_ptr(glm::mat4(1.f)));

    _vao.bind();
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void Plane::collide(pbf::Particle &p) {
    float curr_proj_mag = glm::dot(_n, p.pos - _pos);
    float pred_proj_mag = glm::dot(_n, p.pred_pos - _pos);

    if ((curr_proj_mag >= 0) == (pred_proj_mag >= 0))
        return;

    glm::vec3 tangent = p.pred_pos - (pred_proj_mag - EPS_F) * _n;
    glm::vec3 from_center = tangent - _pos;
    float w_dist = glm::dot(from_center, _right);
    if (w_dist > _width / 2.f)
        return;
    float h_dist = glm::dot(from_center, _front);
    if (h_dist > _height / 2.f)
        return;

    glm::vec3 correction = (tangent - p.pos) * (1 - FRICTION);
    p.pred_pos = correction + p.pos;
}

void Plane::update_points() {
    _right = glm::normalize(glm::cross(_n, WORLD_UP));
    if (glm::length(_right) == 0.f) {
        _right = WORLD_RIGHT;
    }
    _front = glm::normalize(glm::cross(_n, _right));

    glm::vec3 r_2 = (_width / 2) * _right;
    glm::vec3 f_2 = (_height / 2) * _front;
    glm::vec3 points[4] = {
        _pos - r_2 - f_2,
        _pos - r_2 + f_2,
        _pos + r_2 - f_2,
        _pos + r_2 + f_2
    };

    _vbo.bind();
    _vbo.set_data(sizeof(float) * 12, points, GL_STATIC_DRAW);
}