//
// Created by Karina Goot on 4/18/18.
//

#ifndef CLOTHSIM_CONTAINER_H
#define CLOTHSIM_CONTAINER_H
#include <nanogui/nanogui.h>
#include "CGL/vector3D.h"
#include "CGL/CGL.h"
#include "CGL/misc.h"

using namespace CGL;
using namespace std;

class Container {
public:
  Vector3D max,min; //corners

  Container(Vector3D,Vector3D);

};


#endif //CLOTHSIM_CONTAINER_H
