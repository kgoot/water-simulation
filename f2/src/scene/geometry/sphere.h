//
// Created by Dillon Yao on 4/16/18.
//

#ifndef F2_SPHERE_H
#define F2_SPHERE_H

#include "../camera.h"
#include "../../gl/buffer.h"
#include "../../gl/shader.h"

class Sphere : public Thing {
public:
    Sphere();
    void set(glm::vec3 origin, float r);
    void render(Camera &camera);

private:
    float _r;

    Buffer _vbo;
    VertexArray _vao;
    Program _program;
};

#endif //F2_SPHERE_H
