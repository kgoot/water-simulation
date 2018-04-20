//
// Created by Dillon Yao on 4/11/18.
//

#ifndef F2_INPUT_H
#define F2_INPUT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
#include <vector>

class App;
class View;

class Input {
public:

    bool init(App *app, View *view);

    static Input *get() {
        return &_self;
    }

    int poll_key(int key) {
        return glfwGetKey(_window, key);
    }

    int poll_mouse(int button) {
        return glfwGetMouseButton(_window, button);
    }

    void set_cursor_shape(int cursor) {
        GLFWcursor *c = NULL;
        switch (cursor) {
            case GLFW_HAND_CURSOR:
                c = _selection;
                break;
            default:
                break;
        }
        glfwSetCursor(_window, c);
    }

    glm::dvec2 poll_cursor() {
        glm::dvec2 cursor;
        glfwGetCursorPos(_window, &cursor.x, &cursor.y);
        return cursor;
    }

    glm::ivec2 poll_viewport() {
        glm::ivec2 vp;
        glfwGetFramebufferSize(_window, &vp.x, &vp.y);
        return vp;
    }

    void listen_on_key(std::function<void(int, int, int)> cb) {
        _key_cbs.push_back(cb);
    }
    void listen_on_cursor(std::function<void(double, double)> cb) {
        _cursor_cbs.push_back(cb);
    }
    void listen_on_mouse(std::function<void(int, int)> cb) {
        _mouse_cbs.push_back(cb);
    }
    void listen_on_scroll(std::function<void(double, double)> cb) {
        _scroll_cbs.push_back(cb);
    }
    void listen_on_resize(std::function<void(int, int)> cb) {
        _resize_cbs.push_back(cb);
    }

//    void remove_on_key();
//    void remove_on_cursor();
//    void remove_on_mouse();
//    void remove_on_scroll();
//    void remove_on_resize();

    static void on_key(GLFWwindow *window, int key, int scancode, int action, int mods);
    static void on_cursor(GLFWwindow *window, double x, double y);
    static void on_mouse(GLFWwindow *window, int button, int action, int mods);
    static void on_scroll(GLFWwindow *window, double dx, double dy);
    static void on_resize(GLFWwindow *window, int width, int height);

private:
    static Input _self;
    Input() {}

    App *_app;
    GLFWwindow *_window;

    GLFWcursor *_selection;

    std::vector<std::function<void(int, int, int)>>     _key_cbs;
    std::vector<std::function<void(double, double)>>    _cursor_cbs;
    std::vector<std::function<void(int, int)>>          _mouse_cbs;
    std::vector<std::function<void(double, double)>>    _scroll_cbs;
    std::vector<std::function<void(int, int)>>          _resize_cbs;
};

#endif //F2_INPUT_H
