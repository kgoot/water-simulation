//
// Created by Dillon Yao on 4/11/18.
//

#ifndef F2_VIEW_STATE_H
#define F2_VIEW_STATE_H

#include "../core/state.h"
#include "../pbf/particles.h"
#include "../scene/camera.h"
#include "../scene/scene.h"
#include "../scene/geometry/plane.h"

class ViewState : public AppState {
public:
    const char *name() { return "view state"; }
    void init();
    void handle_input();
    void update(double dt);
    void render();
    bool should_terminate();

private:
    pbf::Particles _particles;
    Plane _bottom;
    Plane _left;
    Plane _right;
    Plane _front;
    Plane _back;

    Camera _camera;
    Scene _scene;

    float _sim_modifier;
    bool _pause;
    bool _terminate;

    bool _mouse_down;
    glm::vec2 _last_cursor;
    float _mouse_sensitivity;

    void reset_scene();

    void bind_input_listeners();
    void handle_on_key(int key, int scancode, int action);
    void update_camera_dir_from_cursor(float x, float y);
};

#endif //F2_VIEW_STATE_H
