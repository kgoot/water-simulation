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

    void spawn_sphere(glm::vec3 &origin, float r, float density=10.f);

    void spawn_rect();

    void spawn_prism();

    void spawn_from_model();

    void update(double dt);

    void render(Camera &camera);

    void clear();

    glm::ivec3 cell(glm::vec3 pos);

    int hash_position(glm::ivec3 cell);

    void build_spatial_map();

    void find_neighbors(Particle &p);

    double w_poly_6(double r);

    glm::vec3 w_gradient_spiky(Particle &p, Particle &neighbor);

    double get_rho(Particle &p);

    double C(double rho, double p0);

    double lambda(double rho, double rho0, Particle &p, double epsilon);

    double s_corr(Particle &p, Particle &neighbor, double k, double delta_q, double n);

    glm::vec3 find_vorticity(Particle &p);

    glm::vec3 find_vorticity_force(Particle &p, glm::vec3 vorticity, double epsilon);


  private:
    Buffer _vbo;
    VertexArray _vao;
    std::vector<Particle> _particles;
    std::map<int, std::vector<Particle *> *> _spatial_map;
    Program _program;
    double _h = 0.105;

    bool _is_collidable = false;
  };

}

#endif //F2_PARTICLES_H
