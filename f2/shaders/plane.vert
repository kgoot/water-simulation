#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 fPos;

uniform mat4 eye;
uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main() {
    fPos = (model * vec4(aPos, 1.f)).xyz;
	gl_Position = proj * view * model * vec4(aPos, 1.f);
}
