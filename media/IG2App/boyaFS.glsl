#version 330 core

in vec2 vUv0; // out del vertex shader 
in vec3 vXxxNormal;
in vec4 vXxxVertex;
uniform sampler2D textura; // tipo sampler2D para texturas 2D
uniform vec4 InColor;
uniform vec4 OutColor;
uniform float Flipping;
// uniform vec3 lightAmbient; // intensidades de la luz
// uniform vec3 lightDiffuse;
// uniform vec4 lightPosition;
// uniform vec3 materialDiffuse;
out vec4 fFragColor; // out del fragment shader


// float diff(vec3 cVertex, vec3 cNormal)
// {
// 	vec3 lightDir = lightPosition.xyz; // directional light ?
// 	if (lightPosition.w == 1) // positional light ?
// 		lightDir = lightPosition.xyz ‐ cVertex;

// 	return max(dot(cNormal, normalize(lightDir)), 0.0); // dot: coseno ángulo
// }

void main() {
	vec3 colorTex = vec3(texture(textura, vUv0));
	vec4 color;	

	if(colorTex.r > 0.5) discard;
	
	bool frontFacing = (Flipping > -1)? gl_FrontFacing : !gl_FrontFacing; 

	if(frontFacing)	color = OutColor;
	else color = InColor;	

	// // ambient
	// vec3 ambient = lightAmbient * materialDiffuse;
	// // diffuse en view space
	// vec3 viewVertex = vec3(modelViewMat * vertex);
	// vec3 viewNormal = normalize(vec3(normalMat * vec4(normal,0)));
	// vec3 diffuse = diff(viewVertex, viewNormal) * lightDiffuse * materialDiffuse;
	// vFrontColor = ambient + diffuse; // + specular
	// diffuse = diff(viewVertex, ‐viewNormal) * lightDiffuse * materialDiffuse;
	// vBackColor = ambient + diffuse; // + specular
	
	fFragColor = color; // out
} 
