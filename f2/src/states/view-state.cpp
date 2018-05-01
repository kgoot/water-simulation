//
// Created by Dillon Yao on 4/11/18.
//

#include <glad/glad.h>
#include <iostream>
#include <sstream>
#include "view-state.h"
#include "../core/input.h"

void ViewState::init() {
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);
  glEnable(GL_PROGRAM_POINT_SIZE);
  glClearColor(0.1f, 0.18f, 0.2f, 1.0f);

  glCullFace(GL_FRONT);
  glEnable(GL_CULL_FACE);

  _terminate = false;
  _sim_modifier = 1.f;
  _mouse_sensitivity = 0.002f;
  _mouse_down = false;

  _bottom.set_position(glm::vec3(0, 0, 0));
  _bottom.set_normal(glm::vec3(0, 1, 0));
  _bottom.set_dimensions(1, 1);

  _top.set_position(glm::vec3(0, 3, 0));
  _top.set_normal(glm::vec3(0, -1, 0));
  _top.set_dimensions(1, 1);

  _back.set_position(glm::vec3(0, 1.5, -0.5));
  _back.set_normal(glm::vec3(0, 0, 1));
  _back.set_dimensions(1, 3);

  _front.set_position(glm::vec3(0, 1.5, 0.5));
  _front.set_normal(glm::vec3(0, 0, -1));
  _front.set_dimensions(1, 3);

  _left.set_position(glm::vec3(-0.5, 1.5, 0));
  _left.set_normal(glm::vec3(1, 0, 0));
  _left.set_dimensions(1, 3);

  _right.set_position(glm::vec3(0.5, 1.5, 0));
  _right.set_normal(glm::vec3(-1, 0, 0));
  _right.set_dimensions(1, 3);


  _scene.add_thing(&_bottom);
  _scene.add_thing(&_top);
  _scene.add_thing(&_right);
  _scene.add_thing(&_left);
  _scene.add_thing(&_back);
  _scene.add_thing(&_front);
  _scene.add_thing(&_particles);

  glm::vec3 pos = glm::vec3(0, 0, 5);
  _camera.set_position(pos);

  reset_scene();
  bind_input_listeners();
}

void ViewState::reset_scene() {
  _pause = true;

  _particles.clear();
  glm::vec3 ori(0, 2, 0);
  _particles.spawn_sphere(ori, 0.25, 20.f);

}

void ViewState::handle_input() {
  Input *input = Input::get();
  if (input->poll_key(GLFW_KEY_W) == GLFW_PRESS) {
    _camera.move(FRONT, 0.02);
  }
  if (input->poll_key(GLFW_KEY_S) == GLFW_PRESS) {
    _camera.move(BACK, 0.02);
  }
  if (input->poll_key(GLFW_KEY_A) == GLFW_PRESS) {
    _camera.move(LEFT, 0.02);
  }
  if (input->poll_key(GLFW_KEY_D) == GLFW_PRESS) {
    _camera.move(RIGHT, 0.02);
  }
  if (input->poll_key(GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
    _camera.move(BOTTOM, 0.02);
  }
  if (input->poll_key(GLFW_KEY_SPACE) == GLFW_PRESS) {
    _camera.move(TOP, 0.02);
  }
}

void ViewState::update(double dt) {
  if (!_pause) {
    _particles.update(_sim_modifier * dt);
  }
}

void ViewState::render() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  _scene.render(_camera);
}

bool ViewState::should_terminate() {
  return _terminate;
}

void ViewState::bind_input_listeners() {
  Input::get()->listen_on_resize([this](int width, int height) {
    _camera.set_aspect((float) width / height);
  });

  Input::get()->listen_on_mouse([this](int button, int action) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
      if (action == GLFW_PRESS) {
        _last_cursor = Input::get()->poll_cursor();
        Input::get()->set_cursor_shape(GLFW_HAND_CURSOR);
        _mouse_down = true;
      } else if (action == GLFW_RELEASE) {
        Input::get()->set_cursor_shape(-1);
        _mouse_down = false;
      }
    }
  });

  Input::get()->listen_on_cursor([this](float x, float y) {
    update_camera_dir_from_cursor(x, y);
  });

  Input::get()->listen_on_key([this](int key, int scancode, int action) {
    handle_on_key(key, scancode, action);
  });
}

void ViewState::handle_on_key(int key, int scancode, int action) {
  if (action != GLFW_PRESS)
    return;
  if (key == GLFW_KEY_ESCAPE) {
    _terminate = true;
  } else if (key == GLFW_KEY_COMMA) {
    if (_sim_modifier > 0.1f) {
      _sim_modifier /= 1.25f;
      std::ostringstream msg;
      msg << "reduced sim speed to "<< _sim_modifier << std::endl;
      scoped_msg("view", msg.str().c_str());
    }
  } else if (key == GLFW_KEY_PERIOD) {
    if (_sim_modifier < 2.f) {
      _sim_modifier *= 1.25f;
      std::ostringstream msg;
      msg << "increased sim speed to "<< _sim_modifier << std::endl;
      scoped_msg("view", msg.str().c_str());
    }
  } else if (key == GLFW_KEY_P) {
    _pause = !_pause;
  } else if (key == GLFW_KEY_R) {
    reset_scene();
  }
}

void ViewState::update_camera_dir_from_cursor(float x, float y) {
  if (!_mouse_down)
    return;
  glm::vec2 p(x, y);
  glm::vec2 dp = _mouse_sensitivity * (p - _last_cursor);
  _camera.rotate(-dp.y, dp.x, 0, true);
  _last_cursor = p;
}
