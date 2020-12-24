#version 330 core

in vec2 uv0;
in vec4 vertex; // out del vertex shader
out vec2 vvUv0;

void main() {
	vvUv0 = uv0; 
	gl_Position = vertex;
}

