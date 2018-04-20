//
// Created by Dillon Yao on 4/11/18.
//

#ifndef F2_VIEW_H
#define F2_VIEW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "config.h"

class View {
public:
    ~View();
    void swap_buffers();
    bool should_close();

    bool init(ViewConfig &config);
    GLFWwindow *get_window();

private:
    const char *_title;
    int _width, _height;
    GLFWwindow *_window;
};

#endif //F2_VIEW_H
