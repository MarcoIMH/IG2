#version 330 core

in vec3 normal;
in vec4 vertex; // out del vertex shader
out vec3 gNormal;

void main() {
	gNormal = normalize(normal);
	gl_Position = vertex;
}

