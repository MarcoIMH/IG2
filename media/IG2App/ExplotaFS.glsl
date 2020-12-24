#version 330 core

in vec2 a;
uniform sampler2D bumpy;
uniform sampler2D corrosion;
uniform float Flipping;
out vec4 fFragColor;

void main() {

	bool frontFacing = (Flipping > -1)? gl_FrontFacing : !gl_FrontFacing;

	vec3 color;
	if(frontFacing){
		color = vec3(texture(bumpy, a));
	}
	else{
		color = vec3(texture(corrosion, a));
	}

	fFragColor = vec4(color, 1.);
}

