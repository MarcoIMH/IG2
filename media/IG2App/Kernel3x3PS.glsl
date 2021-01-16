#version 330 core

in vec2 vUv0; // out del vertex shader
uniform sampler2D RTT0; //textura con la escena
out vec4 fFragColor; // out del fragment shader
uniform float kernel[9];

void main() {
	ivec2 texSize = textureSize(RTT0,0);
	float incS = 1. / float(texSize.s); // s = inc horizontal   
	float incT = 1. / float(texSize.t); // t = inc vertical
	vec2 incUV[9] = vec2[] (		
					vec2(-incS, incT),  //top left
					vec2(0, incT),  	// top center
					vec2(incS, incT),  	// top Right

					vec2(-incS, 0),  	//Center Left
					vec2(0, 0),  		//Center Center
					vec2(incS, 0),  	//Center right

					vec2(-incS, -incT), //Bottom left
					vec2(0, -incT),  	//Bottom center
					vec2(incS, -incT));  //Bottom right

    vec3 color = vec3(0.0, 0.0, 0.0);

	for(int x=0; x<9; x++){	   
		vec2 result = vUv0 + incUV[x];

		//if((result.s <= 1 && result.s >= 0) && (result.t <=1 && result.t >= 0))
	      color+= vec3(texture(RTT0, result)) * kernel[x];
	}

	fFragColor = vec4(color, 1.0);
}

