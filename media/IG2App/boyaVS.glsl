#version 330 core

in vec2 uv0;
in vec4 vertex;
in vec3 normal;
uniform mat4 modelViewProjMat;
uniform mat4 modelViewMat;
uniform mat4 normalMat;
out vec2 vUv0; 
out vec3 vXxxNormal;
out vec4 vXxxVertex;

void main() {
	vXxxVertex = vec4(modelViewMat * vertex);
	vXxxNormal = normalize(vec3(normalMat * vec4(normal,0)));
	vUv0 = uv0; // se pasan las coordenadas de textura
	gl_Position = modelViewProjMat * vertex; //obligatorio
}