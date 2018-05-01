//
// Created by Dillon Yao on 4/11/18.
//

#ifndef F2_PARTICLE_H
#define F2_PARTICLE_H

#define PARTICLE_RADIUS 0.025f

#include <glm/vec3.hpp>
#include <vector>
//using namespace std;

namespace pbf {

  struct Particle {
    glm::vec3 pos;
    glm::vec3 pred_pos;
    glm::vec3 vel;

    float mass = 1;
    double radius = 0.5;
    double rho = 0.0;
    double lambda = 0.0;
    std::vector<Particle *> neighbors;
    glm::vec3 delta_p;


    Particle() :
        pos(0.f), vel(0.f)
    { }

    Particle(glm::vec3 &_pos) :
        pos(_pos), vel(0.f)
    { }
  };

}

#endif //F2_PARTICLE_H
