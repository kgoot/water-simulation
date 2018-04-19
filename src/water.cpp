#include <iostream>
#include <math.h>
#include <random>
#include <vector>

#include "water.h"
#include "collision/plane.h"
#include "collision/sphere.h"

using namespace std;

Water::Water(double width, double height, int num_width_points,
             int num_height_points, float thickness) {
  this->width = width;
  this->height = height;
  this->num_width_points = num_width_points;
  this->num_height_points = num_height_points;
  this->thickness = thickness;

  buildGrid();
  buildClothMesh();
}

Water::~Water() {
  point_masses.clear();
  springs.clear();

  if (clothMesh) {
    delete clothMesh;
  }
}

void Water::buildGrid() {
  // TODO (Part 1.1): Build a grid of masses.
  int num_nodes = num_width_points * num_height_points;
  double w_offset = width / num_width_points;
  double h_offset = height / num_height_points;
  if (orientation == HORIZONTAL) {
    Vector3D position = Vector3D(0, 1, 0);
    for (int m = 0; m < num_nodes; m++) {
      PointMass mass = PointMass(position, false);
      point_masses.emplace_back(mass);
      if ((m + 1) % num_width_points == 0) {
        position = Vector3D(0, 1, position.z + h_offset);
      } else {
        position = Vector3D(position.x + w_offset, 1, position.z);
      }
    }
  } else {
    Vector3D position = Vector3D(0, 0, (rand() % 2001 - 1000) / (1000.0 * 1000));
    for (int m = 0; m < num_nodes; m++) {
      PointMass mass = PointMass(position, false);
      point_masses.emplace_back(mass);
      if ((m + 1) % num_width_points == 0) {
        position = Vector3D(0, position.y + h_offset, (rand() % 2001 - 1000) / (1000.0 * 1000));
      } else {
        position = Vector3D(position.x + w_offset, position.y, (rand() % 2001 - 1000) / (1000.0 * 1000));
      }
    }
  }

  for (vector<int> i : pinned) {
    point_masses[num_width_points * i[1] + i[0]].pinned = true;
  }
}

void Water::simulate(double frames_per_sec, double simulation_steps, WaterParameters *cp,
                     vector<Vector3D> external_accelerations,
                     vector<CollisionObject *> *collision_objects) {
  double mass = width * height * cp->density / num_width_points / num_height_points;
  double delta_t = 1.0f / frames_per_sec / simulation_steps;

  // TODO (Part 2.1): Compute total force acting on each point mass.
  for (PointMass &m: point_masses) {
    m.forces = Vector3D();
    for (Vector3D ext_force: external_accelerations) {
      m.forces += mass * ext_force;
    }
  }

  for (Spring &s: springs) {
    if ((s.spring_type == STRUCTURAL && cp->enable_structural_constraints) ||
        (s.spring_type == SHEARING && cp->enable_shearing_constraints) ||
        (s.spring_type == BENDING && cp->enable_bending_constraints)) {
      double Fs = cp->ks * ((s.pm_a->position - s.pm_b->position).norm() - s.rest_length);
      if (s.spring_type == BENDING) Fs *= 0.2;
      s.pm_a->forces += (s.pm_b->position - s.pm_a->position).unit() * Fs;
      s.pm_b->forces += (s.pm_a->position - s.pm_b->position).unit() * Fs;
    }
  }

  // TODO (Part 2.2): Use Verlet integration to compute new point mass positions
  for (PointMass &m: point_masses) {
    if (!m.pinned) {
      Vector3D curr_position = m.position;

      m.position = m.position + (1 - cp->damping / 100.0) * (m.position - m.last_position)
                   + (m.forces / mass) * pow(delta_t, 2);
      m.last_position = curr_position;
    }
  }



  // This won't do anything until you complete Part 4.
  build_spatial_map();
  for (PointMass &pm : point_masses) {
    self_collide(pm, simulation_steps);
  }

  // This won't do anything until you complete Part 3.
  for (PointMass &pm : point_masses) {
    for (CollisionObject *co : *collision_objects) {
      co->collide(pm);
    }
  }


  // TODO (Part 2.3): Constrain the changes to be such that the spring does not change
  // in length more than 10% per timestep [Provot 1995].
  for (Spring s: springs) {
    if (distance(s.pm_a, s.pm_b) > s.rest_length * 1.1) {
      if (s.pm_a->pinned && s.pm_b->pinned) {
        continue;
      } else if (s.pm_a->pinned) {
        s.pm_b->position = -(s.rest_length * 1.1) / (s.pm_a->position - s.pm_b->position).norm() * s.pm_b->position;
      } else if (s.pm_b->pinned) {
        s.pm_a->position = (s.rest_length * 1.1) / (s.pm_a->position - s.pm_b->position).norm() * s.pm_a->position;
      } else {
        s.pm_a->position = 0.5 * (s.rest_length * 1.1) / (s.pm_a->position - s.pm_b->position).norm() * s.pm_a->position;
        s.pm_b->position = -0.5 * (s.rest_length * 1.1) / (s.pm_a->position - s.pm_b->position).norm() * s.pm_b->position;
      }
    }
  }

}

void Water::build_spatial_map() {
  for (const auto &entry : map) {
    delete(entry.second);
  }
  map.clear();

  // TODO (Part 4.2): Build a spatial map out of all of the point masses.
  for (PointMass &m : point_masses) {
    float hash = hash_position(m.position);
    if (map.count(hash) == 0) {
      vector<PointMass *> * pm_vector = new vector<PointMass *>();
      pm_vector->push_back(&m);
      map.insert({hash, pm_vector});
    } else {
      map.at(hash)->push_back(&m);
    }
  }
}

void Water::self_collide(PointMass &pm, double simulation_steps) {
  // TODO (Part 4.3): Handle self-collision for a given point mass.
  vector<PointMass *> collision_candidates = * map[hash_position(pm.position)];
  if (collision_candidates.size() > 1) {
    Vector3D correction_vector = Vector3D(0, 0, 0);
    int count = 0;
    for (PointMass *m : collision_candidates) {
      if (&pm != m && (pm.position - m->position).norm() < 2.0 * thickness) {
        Vector3D tangentPoint = m->position + 2.0 * thickness * (pm.position - m->position).unit();
        correction_vector += tangentPoint - pm.position;
        count += 1;
      }
    }
    if (count > 0) {
      pm.position += correction_vector / (float) count / simulation_steps;
    }
  }
}

float Water::hash_position(Vector3D pos) {
  // TODO (Part 4.1): Hash a 3D position into a unique float identifier that represents
  // membership in some uniquely identified 3D box volume.
  double w = 3 * width / num_width_points;
  double h  = 3 * height / num_height_points;
  double t = max(w,h);

  int x =  floor(pos.x / w);
  int y =  floor(pos.y / h);
  int z =  floor(pos.z / t);

  return (float) (x * 31 + y) * 31 + z;
}

///////////////////////////////////////////////////////
/// YOU DO NOT NEED TO REFER TO ANY CODE BELOW THIS ///
///////////////////////////////////////////////////////

void Water::reset() {
  PointMass *pm = &point_masses[0];
  for (int i = 0; i < point_masses.size(); i++) {
    pm->position = pm->start_position;
    pm->last_position = pm->start_position;
    pm++;
  }
}

void Water::buildClothMesh() {
  if (point_masses.size() == 0) return;

  ClothMesh *clothMesh = new ClothMesh();
  vector<Triangle *> triangles;

  // Create vector of triangles
  for (int y = 0; y < num_height_points - 1; y++) {
    for (int x = 0; x < num_width_points - 1; x++) {
      PointMass *pm = &point_masses[y * num_width_points + x];
      // Both triangles defined by vertices in counter-clockwise orientation
      triangles.push_back(new Triangle(pm, pm + num_width_points, pm + 1));
      triangles.push_back(new Triangle(pm + 1, pm + num_width_points,
                                       pm + num_width_points + 1));
    }
  }

  // For each triangle in row-order, create 3 edges and 3 internal halfedges
  for (int i = 0; i < triangles.size(); i++) {
    Triangle *t = triangles[i];

    // Allocate new halfedges on heap
    Halfedge *h1 = new Halfedge();
    Halfedge *h2 = new Halfedge();
    Halfedge *h3 = new Halfedge();

    // Allocate new edges on heap
    Edge *e1 = new Edge();
    Edge *e2 = new Edge();
    Edge *e3 = new Edge();

    // Assign a halfedge pointer to the triangle
    t->halfedge = h1;

    // Assign halfedge pointers to point masses
    t->pm1->halfedge = h1;
    t->pm2->halfedge = h2;
    t->pm3->halfedge = h3;

    // Update all halfedge pointers
    h1->edge = e1;
    h1->next = h2;
    h1->pm = t->pm1;
    h1->triangle = t;

    h2->edge = e2;
    h2->next = h3;
    h2->pm = t->pm2;
    h2->triangle = t;

    h3->edge = e3;
    h3->next = h1;
    h3->pm = t->pm3;
    h3->triangle = t;
  }

  // Go back through the cloth mesh and link triangles together using halfedge
  // twin pointers

  // Convenient variables for math
  int num_height_tris = (num_height_points - 1) * 2;
  int num_width_tris = (num_width_points - 1) * 2;

  bool topLeft = true;
  for (int i = 0; i < triangles.size(); i++) {
    Triangle *t = triangles[i];

    if (topLeft) {
      // Get left triangle, if it exists
      if (i % num_width_tris != 0) { // Not a left-most triangle
        Triangle *temp = triangles[i - 1];
        t->pm1->halfedge->twin = temp->pm3->halfedge;
      } else {
        t->pm1->halfedge->twin = nullptr;
      }

      // Get triangle above, if it exists
      if (i >= num_width_tris) { // Not a top-most triangle
        Triangle *temp = triangles[i - num_width_tris + 1];
        t->pm3->halfedge->twin = temp->pm2->halfedge;
      } else {
        t->pm3->halfedge->twin = nullptr;
      }

      // Get triangle to bottom right; guaranteed to exist
      Triangle *temp = triangles[i + 1];
      t->pm2->halfedge->twin = temp->pm1->halfedge;
    } else {
      // Get right triangle, if it exists
      if (i % num_width_tris != num_width_tris - 1) { // Not a right-most triangle
        Triangle *temp = triangles[i + 1];
        t->pm3->halfedge->twin = temp->pm1->halfedge;
      } else {
        t->pm3->halfedge->twin = nullptr;
      }

      // Get triangle below, if it exists
      if (i + num_width_tris - 1 < 1.0f * num_width_tris * num_height_tris / 2.0f) { // Not a bottom-most triangle
        Triangle *temp = triangles[i + num_width_tris - 1];
        t->pm2->halfedge->twin = temp->pm3->halfedge;
      } else {
        t->pm2->halfedge->twin = nullptr;
      }

      // Get triangle to top left; guaranteed to exist
      Triangle *temp = triangles[i - 1];
      t->pm1->halfedge->twin = temp->pm2->halfedge;
    }

    topLeft = !topLeft;
  }

  clothMesh->triangles = triangles;
  this->clothMesh = clothMesh;
}
