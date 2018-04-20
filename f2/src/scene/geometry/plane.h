//
// Created by Dillon Yao on 4/16/18.
//

#ifndef F2_PLANE_H
#define F2_PLANE_H

#include "../camera.h"
#include "../../gl/buffer.h"
#include "../../gl/shader.h"

class Plane : public Thing {
public:
    Plane();
    void set(glm::vec3 p, glm::vec3 n, float width, float height);
    void set_position(glm::vec3 p);
    void set_normal(glm::vec3 n);
    void set_dimensions(float width, float height);

    void render(Camera &camera);
    void collide(pbf::Particle &p);

private:
    glm::vec3 _n;
    glm::vec3 _front, _right;
    float _width, _height;

    Buffer _vbo;
    VertexArray _vao;
    Program _program;

    void update_points();
};

#endif //F2_PLANE_H
