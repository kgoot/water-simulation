//
// Created by Dillon Yao on 4/11/18.
//

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "camera.h"
#include "../core/input.h"
#include "../common.h"

Camera::Camera() :
    _yaw(-M_PI_2), _pitch(0), _roll(0)
{
    glm::ivec2 viewport = Input::get()->poll_viewport();
    set_perspective(60.0f, (float) viewport.x / viewport.y, 0.25f, 100.0f);
//    _orientation = glm::quat(1.f, 0.f, 0.f, 0.f);
    _pos = glm::vec3(0.f, 0.f, 0.f);
}

glm::vec3 &Camera::position()       { return _pos; }
glm::mat4 &Camera::proj()           { return _proj; }
glm::mat4 &Camera::view()           { return _view; }

void Camera::set_position(glm::vec3 &v) {
    _pos = v;
}

void Camera::set_orientation(float pitch, float yaw, float roll) {
    _pitch = pitch;
    _yaw = yaw;
    _roll = roll;
}

void Camera::set_aspect(float aspect) {
    _aspect = aspect;
}

void Camera::set_perspective(float fovy, float aspect, float near, float far) {
    _aspect = aspect;
    _afovy = glm::radians(fovy);
    _near = near;
    _far = far;
}

void Camera::translate(glm::vec3 &p) {
    _pos += p;
}

void Camera::rotate(float pitch, float yaw, float roll, bool constrain_pitch) {
    _pitch += pitch;
    if (constrain_pitch) {
        if (_pitch > M_PI_4) _pitch = (float) M_PI_4;
        if (_pitch < -M_PI_4 + 0.001) _pitch = (float) -M_PI_4 + 0.001f;
    }
    _yaw += yaw;
    _roll += roll;
    _yaw = std::fmod(_yaw, (float) M_PI * 2.f);
}

void Camera::move(CamDir dir, float dist) {
    if (dir == FRONT)
        _pos += dist * front();
    if (dir == BACK)
        _pos -= dist * front();
    if (dir == LEFT)
        _pos -= dist * right();
    if (dir == RIGHT)
        _pos += dist * right();
    if (dir == TOP)
        _pos.y += dist;
    if (dir == BOTTOM)
        _pos.y -= dist;
}

void Camera::calc_proj() {
    _proj = glm::perspective(_afovy, _aspect, _near, _far);
}

void Camera::calc_view() {
    _view = glm::lookAt(_pos, _pos + front(), up());
}

glm::mat4 &Camera::get_proj() {
    calc_proj();
    return _proj;
}

glm::mat4 &Camera::get_view() {
    calc_view();
    return _view;
}

glm::vec3 Camera::front() {
    float x = std::cos(_yaw) * std::cos(_pitch);
    float y = std::sin(_pitch);
    float z = std::sin(_yaw) * std::cos(_pitch);
    glm::vec3 front(x, y, z);
    front = glm::normalize(front);
    return front;
}

glm::vec3 Camera::up() {
    return glm::normalize(glm::cross(right(), front()));
}

glm::vec3 Camera::right() {
    return glm::normalize(glm::cross(front(), WORLD_UP));
}
