#version 330 core

in vec2 vvvUv0;
in vec3 normal;
in vec3 gvertex;
uniform sampler2D bumpy;
uniform sampler2D corrosion;
uniform vec3 lightAmbient;
uniform vec3 lightDiffuse;
uniform vec4 lightPosition;
uniform float Flipping;
out vec4 fFragColor;

float diff(vec3 cVertex, vec3 cNormal){
	vec3 lightDir = lightPosition.xyz;
	if(lightPosition.w == 1){
		lightDir = lightPosition.xyz - cVertex;
	}

	return max(dot(cNormal, normalize(lightDir)), 0.0);
}

void main() {
	bool frontFacing = (Flipping > -1)? gl_FrontFacing : !gl_FrontFacing;

	vec3 colorTex;
	vec3 diffuse;
	if(frontFacing){
		colorTex = vec3(texture(bumpy, vvvUv0));
		diffuse = diff(gvertex, normal) * lightDiffuse;
	}
	else{
		colorTex = vec3(texture(corrosion, vvvUv0));
		diffuse = diff(gvertex, -normal) * lightDiffuse;
	}
	vec3 vFrontColor = lightAmbient + diffuse;
	vec3 color = vFrontColor * colorTex;

	fFragColor = vec4(color, 1.);
}