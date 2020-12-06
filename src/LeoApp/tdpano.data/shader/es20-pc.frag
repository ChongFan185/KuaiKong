
#version 100
precision mediump float; 

varying vec4 vVaryingColor; 
varying vec2 vVaryingUv;

//uniform sampler2DRect texture;

//out vec4 vFragColor;

void main() 
{ 
	gl_FragColor = vVaryingColor;
//	vFragColor.a = vVaryingColor.a;
//  vFragColor = vVaryingColor;
//	vFragColor = texture(texture, vVaryingUv.st);
} 

