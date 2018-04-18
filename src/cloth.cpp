#include <iostream>
#include <math.h>
#include <random>
#include <vector>

#include "cloth.h"
#include "collision/plane.h"
#include "collision/sphere.h"

using namespace std;

Cloth::Cloth(double width, double height, int num_width_points,
             int num_height_points, float thickness) {
  this->width = width;
  this->height = height;
  this->num_width_points = num_width_points;
  this->num_height_points = num_height_points;
  this->thickness = thickness;

  buildGrid();
  buildClothMesh();
}

Cloth::~Cloth() {
  point_masses.clear();
  springs.clear();

  if (clothMesh) {
    delete clothMesh;
  }
}

void Cloth::buildGrid() {
  // TODO (Part 1.1): Build a grid of masses.
  double height_step = height / num_height_points;
  double width_step = width / num_width_points;
  for (int j = 0; j < num_height_points; ++j) {
    for (int i = 0; i < num_width_points; ++i) {
      double x = i * width_step;
      double y;
      double z;
      if (orientation == HORIZONTAL) {
        y = 1.0;
        z = j * height_step;
      } else if (orientation == VERTICAL) {
        y = j * height_step;;
        z = (rand() % 2001 - 1000) / (1000.0 * 1000);
      } else {
        y = 0.0;
        z = 0.0;
      }

      bool cloth_pinned = false;
      for (vector<int> pin_index : pinned) {
        if (i == pin_index[0] && j == pin_index[1]) {
          cloth_pinned = true;
          break;
        }
      }
      point_masses.push_back(PointMass(Vector3D(x, y, z), cloth_pinned));
    }
  }

  // TODO (Part 1.2): Add springs
  for (int j = 0; j < num_height_points; ++j) {
    for (int i = 0; i < num_width_points; ++i) {
      // Structural Constraint
      if (i > 0) {
        springs.push_back(Spring(&point_masses[j * num_width_points + i - 1], &point_masses[j * num_width_points + i], STRUCTURAL));
      }
      if (j < num_height_points-1) {
        springs.push_back(Spring(&point_masses[(j + 1) * num_width_points + i], &point_masses[j * num_width_points + i], STRUCTURAL));
      }


      // Shearing Constraint
      if (i > 0 && j < num_height_points-1) {
        springs.push_back(Spring(&point_masses[(j + 1) * num_width_points + i - 1], &point_masses[j * num_width_points + i], SHEARING));
      }
      if (i < num_width_points-1 && j < num_height_points-1) {
        springs.push_back(Spring(&point_masses[(j + 1) * num_width_points + i + 1], &point_masses[j * num_width_points + i], SHEARING));
      }


      // Bending Constraint
      if (i > 1) {
        springs.push_back(Spring(&point_masses[j * num_width_points + i - 2], &point_masses[j * num_width_points + i], BENDING));
      }
      if (j < num_height_points-2) {
        springs.push_back(Spring(&point_masses[(j + 2) * num_width_points + i], &point_masses[j * num_width_points + i], BENDING));
      }

    }
  }


}

void Cloth::simulate(double frames_per_sec, double simulation_steps, ClothParameters *cp,
                     vector<Vector3D> external_accelerations,
                     vector<CollisionObject *> *collision_objects) {
  double mass = width * height * cp->density / num_width_points / num_height_points;
  double delta_t = 1.0f / frames_per_sec / simulation_steps;

  // TODO (Part 2.1): Compute total force acting on each point mass.

  // Clear forces
  for (PointMass &point_mass : point_masses) {
    point_mass.forces = Vector3D();
  }

  for (PointMass &point_mass : point_masses) {
    for (Vector3D external_acceleration : external_accelerations) {
      point_mass.forces += mass * external_acceleration;
    }
  }


  for (Spring &spring : springs) {
    double curr_ks = cp->ks;
    if (spring.spring_type == STRUCTURAL) {
      if (!cp->enable_structural_constraints) {
        continue;
      }
    } else if (spring.spring_type == SHEARING) {
      if (!cp->enable_shearing_constraints) {
        continue;
      }
    } else if (spring.spring_type == BENDING) {
      curr_ks = cp->ks * 0.2;
      if (!cp->enable_bending_constraints) {
        continue;
      }
    }

    double Fs = curr_ks * ((spring.pm_a->position - spring.pm_b->position).norm() - spring.rest_length);

    spring.pm_a->forces += (spring.pm_b->position - spring.pm_a->position).unit() * Fs;
    spring.pm_b->forces += (spring.pm_a->position - spring.pm_b->position).unit() * Fs;
  }



  // TODO (Part 2.2): Use Verlet integration to compute new point mass positions
  for (PointMass &point_mass : point_masses) {
    if (point_mass.pinned) {
      continue;
    }

    Vector3D new_position = point_mass.position
                            + (1 - cp->damping / 100.0) * (point_mass.position - point_mass.last_position)
                            + (point_mass.forces / mass) * pow(delta_t, 2.0);

    point_mass.last_position = point_mass.position;
    point_mass.position = new_position;

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
  for (Spring &spring : springs) {
    double dist = (spring.pm_a->position - spring.pm_b->position).norm();
    Vector3D dir = (spring.pm_b->position - spring.pm_a->position).unit();
    if (dist > (spring.rest_length * 1.1)) {

      if (!spring.pm_a->pinned && !spring.pm_b->pinned) {
        spring.pm_a->position = spring.pm_a->position + dir * (dist - spring.rest_length * 1.1) / 2.0;
        spring.pm_b->position = spring.pm_b->position + -dir * (dist - spring.rest_length * 1.1) / 2.0;

      } else if (!spring.pm_a->pinned) {
        spring.pm_a->position = spring.pm_a->position + dir * (dist - spring.rest_length * 1.1);

      } else if (!spring.pm_b->pinned) {
        spring.pm_b->position = spring.pm_b->position + -dir * (dist - spring.rest_length * 1.1);

      }

    }
  }

}

void Cloth::build_spatial_map() {
  for (const auto &entry : map) {
    delete(entry.second);
  }
  map.clear();

  // TODO (Part 4.2): Build a spatial map out of all of the point masses.

  for (PointMass &pm : point_masses) {
    float hash_pos = hash_position(pm.position);
    if (map.find(hash_pos) == map.end()) {
      vector<PointMass *>* box_pms = new vector<PointMass*>();
      box_pms->push_back(&pm);

      std::pair <float, vector<PointMass *>*> cand (hash_pos, box_pms);
      map.insert(cand);

    } else {
      map.find(hash_pos)->second->push_back(&pm);
    }
  }

}

void Cloth::self_collide(PointMass &pm, double simulation_steps) {
  // TODO (Part 4.3): Handle self-collision for a given point mass.

  float hash_pos = hash_position(pm.position);
  vector<PointMass *> box = *(map.find(hash_pos)->second);
  Vector3D correction = Vector3D();
  Vector3D pos = pm.position;
  int correction_count = 0;

  if (box.size() < 2) {
    return;
  }

  for (PointMass* candidate : box) {
    if (candidate != &pm) {
      Vector3D cand_pos = candidate->position;
      double dist = (pos - cand_pos).norm();
      if (dist < 2 * thickness) {
        correction += (2 * thickness - dist) * (pos - cand_pos).unit();
        correction_count++;
      }
    }
  }
  if (correction_count == 0) {
    return;
  }
  correction /= (float) correction_count;

  pm.position += correction / simulation_steps;

}

float Cloth::hash_position(Vector3D pos) {
  // TODO (Part 4.1): Hash a 3D position into a unique float identifier that represents
  // membership in some uniquely identified 3D box volume.

  double w = 3 * width / num_width_points;
  double h = 3 * height / num_height_points;
  double t = max(w, h);

//  double x = pos.x / w - fmod(pos.x, w);
//  double y = pos.y / h - fmod(pos.y, h);
//  double z = pos.z / t - fmod(pos.z, t);
  int x = (int) floor(pos.x / w);
  int y = (int) floor(pos.y / h);
  int z = (int) floor(pos.z / t);

  return (float) (x * 31 + y) * 31 + z;


}

///////////////////////////////////////////////////////
/// YOU DO NOT NEED TO REFER TO ANY CODE BELOW THIS ///
///////////////////////////////////////////////////////

void Cloth::reset() {
  PointMass *pm = &point_masses[0];
  for (int i = 0; i < point_masses.size(); i++) {
    pm->position = pm->start_position;
    pm->last_position = pm->start_position;
    pm++;
  }
}

void Cloth::buildClothMesh() {
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
