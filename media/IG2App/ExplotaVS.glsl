#version 330 core

in vec2 uv0;
in vec3 normal;
in vec4 vertex; // out del vertex shader
out vec2 vvUv0;
out vec3 vNormal;

void main() {
	vvUv0 = uv0; 
	vNormal = normalize(normal);
	gl_Position = vertex;
}

