#version 330 core

in vec2 vUv0;
in vec3 vXxxNormal;
in vec4 vXxxVertex;

uniform sampler2D textura;
uniform sampler2D texturaCorrosion;
uniform vec3 InColor;
uniform vec3 OutColor;
uniform float Flipping;
uniform vec3 lightAmbient;
uniform vec3 lightDiffuse;
uniform vec4 lightPosition;
uniform vec3 materialDiffuse;

out vec4 fFragColor; // out del fragment shader

float diff(vec3 cVertex, vec3 cNormal){
	vec3 lightDir = lightPosition.xyz;
	if(lightPosition.w == 1){
		lightDir = lightPosition.xyz - cVertex;
	}

	return max(dot(cNormal, normalize(lightDir)), 0.0);
}

void main() {

	vec3 colorTexCorr = vec3(texture(texturaCorrosion, vUv0));

	if(colorTexCorr.r > 0.5) discard;

	bool frontFacing = (Flipping > -1)? gl_FrontFacing : !gl_FrontFacing;

	vec3 ambient = lightAmbient * materialDiffuse;

	vec3 color;
	if(frontFacing){
		vec3 diffuse = diff(vXxxVertex.xyz, vXxxNormal) * lightDiffuse * materialDiffuse;
		vec3 vFrontColor = ambient + diffuse;
		vec3 colorTex = vec3(texture(textura, vUv0));
		color = OutColor * vFrontColor * colorTex;
	}
	else{
		vec3 diffuse = diff(vXxxVertex.xyz, -vXxxNormal) * lightDiffuse * materialDiffuse;
		vec3 vBackColor = ambient + diffuse;
		color = InColor * vBackColor;
	}

	fFragColor = vec4(color, 1.0);
} 
