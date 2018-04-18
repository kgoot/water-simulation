#include <nanogui/nanogui.h>

#include "../clothMesh.h"
#include "../misc/sphere_drawing.h"
#include "sphere.h"

using namespace nanogui;
using namespace CGL;

void Sphere::collide(PointMass &pm) {
  // TODO (Part 3.1): Handle collisions with spheres.
  Vector3D pos = pm.position;
  if (pow(pos.x - origin.x, 2) + pow(pos.y - origin.y, 2) + pow(pos.z - origin.z, 2) <= radius2) {
    Vector3D tangentPoint = origin + (pm.position - origin).unit() * radius;
    Vector3D correctionVector = tangentPoint - pm.last_position;
    pm.position = pm.last_position + (1 - friction) * correctionVector;
  }
}

void Sphere::render(GLShader &shader) {
  // We decrease the radius here so flat triangles don't behave strangely
  // and intersect with the sphere when rendered
  Misc::draw_sphere(shader, origin, radius * 0.92);
}
