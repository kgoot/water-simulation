//
// Created by Dillon Yao on 4/12/18.
//

#ifndef F2_PARTICLES_H
#define F2_PARTICLES_H

#include <vector>
#include <map>
#include "../scene/thing.h"
#include "particle.h"
#include "../gl/shader.h"
#include "../gl/buffer.h"

namespace pbf {

  class Particles : public Thing {
  public:
    Particles();

    void spawn() {
      _particles.emplace_back();
    }

    void spawn_disk();

    void spawn_sphere(glm::vec3 &origin, float r, float density=3.f);

    void spawn_rect();

    void spawn_prism();

    void spawn_from_model();

    void update(double dt);

    void render(Camera &camera);

    void clear();

    int hash_position(Particle p);

    void build_spatial_map();

    std::vector<Particle *> find_neighbors(Particle p);

    double wPoly6(Particle p, Particle neighbor);

    glm::vec3 wGradientSpiky(Particle p, Particle neighbor);

    double getRho(Particle p, std::vector<Particle *> * neighbors);

    double C(double rho, double p0);

    glm::vec3 cGradient(Particle p, Particle neighbor, double rho0);

    double lambda(double rho, double rho0, Particle p, std::vector<Particle *> * neighbors, double epsilon);


  private:
    Buffer _vbo;
    VertexArray _vao;
    std::vector<Particle> _particles;
    std::map<int, std::vector<Particle *> *> _spatial_map;
    Program _program;

    bool _is_collidable = false;
  };

}

#endif //F2_PARTICLES_H