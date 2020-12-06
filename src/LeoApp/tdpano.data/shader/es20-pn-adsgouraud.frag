
#version 100 
precision mediump float;

varying vec4 vVaryingColor; 

//uniform vec4 vColor;

//out vec4 vFragColor;

void main() 
{ 
	gl_FragColor = vVaryingColor ;
//	gl_FragColor.a = vVaryingColor.a;
} 

