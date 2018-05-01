#version 330 core

in vec4 particleColor;
out vec4 color;

in vec3 fPos;


void main() {
	color = particleColor;
}
