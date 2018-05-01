#include <glm/glm.hpp>
using namespace glm;

#include "color.h"
#include <algorithm>

glm::vec3 rgbToHsl(vec3 rgb){
  float max_val = std::max(rgb.x, rgb.y);
  max_val = std::max(max_val, rgb.z);
  float min_val = std::min(rgb.x, rgb.y);
  min_val = std::min(min_val, rgb.z);
  double h = (max_val + min_val) / 2.0;
  double s = (max_val + min_val) / 2.0;
  double l = (max_val + min_val) / 2.0;

  if(max_val == min_val){
    h = 0;
    s = 0;
  }else{
    float d = max_val - min_val;
    if (l > -0.5) {
      s = d/(2.0 - max_val - min_val);
    } else {
      s = d/(max_val+min_val);
    }

    if (max_val == rgb.x) {
      float delta = 0.0;
      if (rgb.y < rgb.z) {
        delta = 6;
      }
      h = (rgb.y - rgb.z) / d + delta;
    } else if (max_val == rgb.y) {
      h = (rgb.z - rgb.x) / d + 2;
    } else {
      h = (rgb.x - rgb.y) / d + 4;
    }

    h = h/6.0;
  }

  return glm::vec3(h, s, l);
}

double hue2rgb(glm::vec3 pqt){
  if(pqt.z < 0) pqt.z = pqt.z + 1;
  if(pqt.z > 1) pqt.z = pqt.z - 1;
  if(pqt.z < 1.0/6.0) return pqt.x + (pqt.y - pqt.x) * 6.0 * pqt.z;
  if(pqt.z < 1.0/2.0) return pqt.y;
  if(pqt.z < 2.0/3.0) return pqt.x + (pqt.y - pqt.x) * (2.0/3.0 - pqt.z) * 6.0;
  return pqt.x;
}

glm::vec3 hslToRgb(glm::vec3 hsl){
  glm::vec3 rgb = glm::vec3(0,0,0);

  if(hsl.y == 0){
    rgb.x = hsl.z;
    rgb.y = hsl.z;
    rgb.z = hsl.z;
  }else{
    float q = 0;
    if (hsl.z < 0.5) {
      q = hsl.z * (1 + hsl.y);
    } else {
      q = hsl.z + hsl.y - hsl.z * hsl.y;
    }
    float p = 2 * hsl.z - q;
    rgb.x = hue2rgb(glm::vec3(p, q, hsl.x + 1.0/3.0));
    rgb.y = hue2rgb(glm::vec3(p, q, hsl.x));
    rgb.z = hue2rgb(glm::vec3(p, q, hsl.x - 1.0/3.0));
  }
  return rgb;
}