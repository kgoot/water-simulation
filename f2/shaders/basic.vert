#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 fPos;

uniform float radius;
uniform int vpheight;
uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;

void main() {
    fPos = (model * vec4(aPos, 1.f)).xyz;
	gl_Position = proj * view * vec4(fPos, 1.f);
    gl_PointSize = vpheight * proj[1][1] * radius / gl_Position.w;
}
