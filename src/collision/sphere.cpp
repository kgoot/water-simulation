#include <nanogui/nanogui.h>

#include "../clothMesh.h"
#include "../misc/sphere_drawing.h"
#include "sphere.h"

using namespace nanogui;
using namespace CGL;

void Sphere::collide(PointMass &pm) {
  // TODO (Part 3.1): Handle collisions with spheres.

  // 1. Compute tangent line
  Vector3D d = (origin - pm.position).unit();
  Vector3D o = pm.position;

  double a = dot(d, d);
  double b = dot(2 * (o - origin), d);
  double c = dot(o - origin, o - origin) - radius2;

  if ((pm.position - origin).norm() > radius) {
    return;
  }

  double t1 = (-b - sqrt(pow(b, 2) - 4*a*c)) / (2*a);
  double t2 = (-b + sqrt(pow(b, 2) - 4*a*c)) / (2*a);
  double min_t = std::min(t1, t2);


  Vector3D tangent_point = o + min_t * d;

  Vector3D correction = tangent_point - pm.last_position;
  pm.position = pm.last_position + correction * (1 - friction);

}

void Sphere::render(GLShader &shader) {
  // We decrease the radius here so flat triangles don't behave strangely
  // and intersect with the sphere when rendered
  Misc::draw_sphere(shader, origin, radius * 0.92);
}
