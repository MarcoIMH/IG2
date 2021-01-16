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

vec3 getBaricentro(vec3 vertex[3]){
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

    /////////////////////////////////////////
    // Rotaciones -> vértices y normales ///
    ///////////////////////////////////////
    vec3 normalesRotadas[3] = vec3[](vec3(0.0,0.0,0.0), vec3(0.0,0.0,0.0), vec3(0.0,0.0,0.0));

	for(int x = 0; x < 3; ++x){
		vec4 verticeRotado = vec4(vertices[x], 1.0) * yaw;
		vertices[x] = vec3(verticeRotado);

		normalesRotadas[x] = vec3(normalMat * (vec4(vNormal[x], 0.0) * yaw));
	}

	vec3 baricentro = getBaricentro(vertices);
	vec3 direccionAumento = normalize(baricentro);

    /////////////////////////////////////////
    // Escalar explosión -> vértices ///////
    ///////////////////////////////////////
	for(int i = 0; i < 3; ++i){
		vec3 direccionEscala = normalize(vertices[i] - baricentro); 

		vertices[i] = vertices[i] + (direccionAumento * VD * tiempo) + (direccionEscala * scaleFact * tiempo);		
	}	


    /////////////////////////////////////////
    // Outs de cada vértice ////////////////
    ///////////////////////////////////////
	for(int i = 0; i < 3; ++i){
		gl_Position = modelViewProjMat  * vec4(vertices[i], 1.0);
		gvertex = vec4(modelViewProjMat * vec4(vertices[i], 1.0));

		vvvUv0 = vvUv0[i];

		normal = normalize(normalesRotadas[i]);

		EmitVertex();
	}
	EndPrimitive();
}

