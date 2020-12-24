#version 330 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in vec3 vNormal[];
in vec2 vvUv0[];
uniform mat4 modelViewProjMat;
uniform mat4 modelViewMat;
uniform mat4 normalMat;
uniform float tiempo;
const float VD = 50;
out vec2 vvvUv0;
out vec3 normal;
out vec4 gvertex;

vec3 baricentro(vec3 vertex[3]){
	return normalize(vec3((vertex[0] + vertex[1] + vertex[2]) / 3.0));
}

void main() {
	vec3 vertices[3] = vec3[]( gl_in[0].gl_Position.xyz,
							   gl_in[1].gl_Position.xyz,
							   gl_in[2].gl_Position.xyz);
	vec3 dir = baricentro(vertices);

	for(int i = 0; i < 3; ++i){
		vec3 posDes = vertices[i] + dir * VD * tiempo;
		vvvUv0 = vvUv0[i];
		gl_Position = modelViewProjMat * vec4(posDes, 1.0);
		gvertex = vec4(modelViewMat * vec4(posDes, 1.0));
		normal = normalize(vec3(normalMat * vec4(vNormal[i], 0)));
		EmitVertex();
	}	
	EndPrimitive();
}

