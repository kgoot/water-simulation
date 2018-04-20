//
// Created by Dillon Yao on 4/15/18.
//

#include <iostream>
#include "input.h"
#include "view.h"

Input Input::_self;

bool Input::init(App *app, View *view) {
    _app = app;
    _window = view->get_window();

    glfwSetKeyCallback(_window, on_key);
    glfwSetCursorPosCallback(_window, on_cursor);
    glfwSetMouseButtonCallback(_window, on_mouse);
    glfwSetScrollCallback(_window, on_scroll);
    glfwSetFramebufferSizeCallback(_window, on_resize);

    _selection = glfwCreateStandardCursor(GLFW_CROSSHAIR_CURSOR);

    return true;
}

void Input::on_key(GLFWwindow *window, int key, int scancode, int action, int mode) {
    for (auto cb : get()->_key_cbs) cb(key, scancode, action);
}

void Input::on_cursor(GLFWwindow *window, double x, double y) {
    for (auto cb : get()->_cursor_cbs) cb(x, y);
}

void Input::on_mouse(GLFWwindow *window, int button, int action, int mods) {
    for (auto cb : get()->_mouse_cbs) cb(button, action);
}

void Input::on_scroll(GLFWwindow *window, double dx, double dy) {
    for (auto cb : get()->_scroll_cbs) cb(dx, dy);
}

void Input::on_resize(GLFWwindow *window, int width, int height) {
    for (auto cb : get()->_resize_cbs) cb(width, height);
    glViewport(0, 0, width, height);
}
