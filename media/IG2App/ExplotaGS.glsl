#version 330 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in vec2 vvUv0[];
uniform mat4 modelViewProjMat;
uniform float tiempo;
const float VD = 50;
out vec2 a;

vec3 normalVec(vec3 vertex[3]){
	vec3 edge1 = vertex[1] - vertex[0];
	vec3 edge2 = vertex[2] - vertex[0];
	return normalize(cross(edge1, edge2));
}

void main() {
	vec3 vertices[3] = vec3[]( gl_in[0].gl_Position.xyz,
							   gl_in[1].gl_Position.xyz,
							   gl_in[2].gl_Position.xyz);
	vec3 dir = normalVec(vertices);

	for(int i = 0; i < 3; ++i){
		vec3 posDes = vertices[i] + dir * VD * tiempo;
		a = vvUv0[i];
		gl_Position = modelViewProjMat * vec4(posDes, 1.0);

		EmitVertex();
	}	
	EndPrimitive();
}

