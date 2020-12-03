#version 330 core

in vec4 vertex; // atributos de los vértices a procesar
in vec2 uv0; // coordenadas de textura 0
uniform mat4 modelViewProjMat; // constante de programa
uniform float sinTiempo; 
uniform float ZF;
out vec2 vUv1;
out vec2 vUv0; // out del vertex shader

void main() {
	vUv0 = uv0; // se pasan las coordenadas de textura
	vUv1 = (uv0 - 0.5) * ((sinTiempo * 0.5 + 0.5) * 0.5) + 0.5;
	gl_Position = modelViewProjMat * vertex; //obligatorio
	// (Clipping coordinates)
}