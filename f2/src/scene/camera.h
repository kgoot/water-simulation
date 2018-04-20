//
// Created by Dillon Yao on 4/11/18.
//

#ifndef F2_CAMERA_H
#define F2_CAMERA_H

#include <glm/detail/type_mat4x4.hpp>
#include "thing.h"

enum CamDir {
    FRONT,
    BACK,
    LEFT,
    RIGHT,
    TOP,
    BOTTOM
};

class Camera : public Thing {
public:
    Camera();

    glm::vec3 &position();
    glm::mat4 &proj();
    glm::mat4 &view();

    void set_position(glm::vec3 &v);
    void set_orientation(float pitch, float yaw, float roll);

    void set_aspect(float aspect);
    void set_perspective(float fovy, float aspect, float near, float far);

    void translate(glm::vec3 &p);
    void rotate(float pitch, float yaw, float roll, bool constrain_pitch=false);
    void move(CamDir dir, float v);

    glm::mat4 &get_proj();
    glm::mat4 &get_view();

private:
    glm::mat4 _proj;
    glm::mat4 _view;

    float _aspect, _afovy, _near, _far;
    float _pitch, _yaw, _roll;

    glm::vec3 front();
    glm::vec3 up();
    glm::vec3 right();

    void calc_proj();
    void calc_view();
};

#endif //F2_CAMERA_H
