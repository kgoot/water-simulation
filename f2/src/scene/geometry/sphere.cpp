//
// Created by Dillon Yao on 4/16/18.
//

#include "sphere.h"
#include <glm/gtc/type_ptr.hpp>

Sphere::Sphere() {

}

void Sphere::set(glm::vec3 origin, float r) {
    _pos = origin;
    _r = r;
}

void Sphere::render(Camera &camera) {

}
