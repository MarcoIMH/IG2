#version 330 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in vec3 vNormal[];
in vec2 vvUv0[];
uniform mat4 modelViewProjMat;
uniform mat4 modelViewMat;
uniform mat4 normalMat;
uniform float tiempo;
uniform float angulo;
const float VD = 50;
const float scaleFact = 2;
out vec2 vvvUv0;
out vec3 normal;
out vec4 gvertex;
mat4 yaw;

vec3 baricentro(vec3 vertex[3]){
	return vec3((vertex[0] + vertex[1] + vertex[2]) / 3.0);
}

void main() {
	vec3 vertices[3] = vec3[]( gl_in[0].gl_Position.xyz,
							   gl_in[1].gl_Position.xyz,
							   gl_in[2].gl_Position.xyz);

    yaw[0] = vec4(cos(angulo), 0, -sin(angulo), 0);
    yaw[1] = vec4(0,1,0, 0);
    yaw[2] = vec4(sin(angulo), 0, cos(angulo), 0);
    yaw[3] = vec4(0,0,0,1);

	vec3 bar = baricentro(vertices);
	vec3 dir = normalize(bar);

	for(int i = 0; i < 3; ++i){
		//-----Escala-------------
		vec3 escalaDir = normalize(vertices[i] - bar);
		//-----Aumento tamaño------
		vec3 posDes = vertices[i] + (dir * VD * tiempo) + (escalaDir * scaleFact * tiempo);
		vec4 vertexPosDes = vec4(posDes, 1.0);
		vec4 normalDes = vec4(vNormal[i], 0);
		vvvUv0 = vvUv0[i];
		vertexPosDes = vertexPosDes * yaw;
		gl_Position = modelViewProjMat * vertexPosDes;
		gvertex = vec4(modelViewProjMat * vertexPosDes);
		normalDes = normalDes * yaw;
		normal = normalize(vec3(normalMat * normalDes));

		EmitVertex();
	}	
	EndPrimitive();
}

