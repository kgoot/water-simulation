//
// Created by Dillon Yao on 4/11/18.
//

#ifndef F2_THING_H
#define F2_THING_H

#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>
#include "../pbf/particle.h"

class Scene;
class Camera;

class Thing {
public:
    Thing();
    virtual void render(Camera &camera) {};
    virtual void collide(pbf::Particle &p) {};

    void set_collidable(bool collidable) {
        _is_collidable = collidable;
    }

protected:
    Scene *_scene;
    glm::vec3 _pos;
    glm::quat _orientation;

    bool _is_collidable = true;

friend class Scene;
};

#endif //F2_THING_H
