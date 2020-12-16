#version 330 core

in vec2 vUv0; // out del vertex shader
uniform sampler2D RTT0; //textura con la escena
out vec4 fFragColor; // out del fragment shader
const vec3 WsRGB = vec3(0.2125, 0.7154, 0.0721);

void main() {
	vec4 sceneColor = texture(RTT0, vUv0);
	float lum = dot(vec3(sceneColor), WsRGB);
	fFragColor = vec4(lum, lum, lum, sceneColor.a ); // out
}

