
#version 100
precision mediump float;

attribute vec3 vVertex;
attribute vec4 vColor;
attribute vec2 vUv;

uniform mat4 mMvp;
uniform bool bMirror;

varying vec4 vVaryingColor;
varying vec2 vVaryingUv;


void main(void)
{
	vVaryingColor = vColor;
	
	vec3 vVertex1 = vVertex;
	
	if(bMirror){
		vVertex1 = vVertex * vec3(-1.0,1.0,1.0);
	}

	gl_Position = mMvp * vec4(vVertex1, 1);
	vVaryingUv = vUv;

}

