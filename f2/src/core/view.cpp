//
// Created by Dillon Yao on 4/11/18.
//

#include <iostream>
#include "view.h"
#include "input.h"

View::~View() {
    glfwDestroyWindow(_window);
    glfwTerminate();
}

bool View::init(ViewConfig &config) {
    if (!glfwInit()) {
        std::cerr << "Initialization of GLFW failed" << std::endl;
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    _width = config.width;
    _height = config.height;
    _title = config.title;

    _window = glfwCreateWindow(_width, _height, _title, NULL, NULL);
    if (!_window) {
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(_window);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    glfwSwapInterval(1);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glfwGetFramebufferSize(_window, &_width, &_height);
    glViewport(0, 0, _width, _height);

    return true;
}

void View::swap_buffers() {
    glfwSwapBuffers(_window);
}

bool View::should_close() {
    return (bool) glfwWindowShouldClose(_window);
}

GLFWwindow *View::get_window() {
    return _window;
}
