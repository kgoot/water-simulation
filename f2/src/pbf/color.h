#ifndef COLOR_H
#define COLOR_H
#include <glm/glm.hpp>
using namespace glm;

vec3 rgbToHsl(vec3 rgb);
double hue2rgb(vec3 pqt);
vec3 hslToRgb(vec3 hsl);

#endif