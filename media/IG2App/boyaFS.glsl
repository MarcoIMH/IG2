#version 330 core

uniform sampler2D textura; // tipo sampler2D para texturas 2D
uniform vec4 InColor;
uniform vec4 OutColor;
uniform float Flipping;
in vec2 vUv0; // out del vertex shader
uniform vec3 lightAmbient; // intensidades de la luz
uniform vec3 lightDiffuse;
uniform vec4 lightPosition;
uniform vec3 materialDiffuse;
in vec3 normal;
in vec4 vertex; // atributos de los vértices a procesar
out vec4 fFragColor; // out del fragment shader

void main() {
	// ambient
	vec3 ambient = lightAmbient * materialDiffuse;
	// diffuse en view space
	vec3 viewVertex = vec3(modelViewMat * vertex);
	vec3 viewNormal = normalize(vec3(normalMat * vec4(normal,0)));
	vec3 diffuse = diff(viewVertex, viewNormal) * lightDiffuse * materialDiffuse;
	vFrontColor = ambient + diffuse; // + specular
	diffuse = diff(viewVertex, ‐viewNormal) * lightDiffuse * materialDiffuse;
	vBackColor = ambient + diffuse; // + specular

	vec3 colorTex = vec3(texture(textura, vUv0));
	vec4 color;

	if(colorTex.r > 0.5) discard;
	
	bool frontFacing = (Flipping > -1)? gl_FrontFacing : !gl_FrontFacing; 

	if(frontFacing)	color = OutColor; 
	else color = InColor;	

	fFragColor = diffuse; // out
} 

float diff(float cVertex, float cNormal)
{
	vec3 lightDir = lightPosition.xyz; // directional light ?
	if (lightPosition.w == 1) // positional light ?
	lightDir = lightPosition.xyz ‐ cVertex;
	return max(dot(cNormal, normalize(lightDir)), 0.0); // dot: coseno ángulo
}