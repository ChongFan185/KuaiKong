
#version 100
precision mediump float;

attribute vec3 vVertex;
attribute vec4 vColor;
attribute vec2 vUv;
attribute vec2 vUv1;

uniform mat4 mMvp;
uniform bool bMirror;

varying vec3 vVaryingVertex;
varying vec4 vVaryingColor;
varying vec2 vVaryingUv;
varying vec2 vVaryingUv1;

void main(void)
{
	vVaryingColor = vColor;
	vVaryingVertex = vVertex;
		
	vec3 vVertex1 = vVertex;
	
	if(bMirror){
		vVertex1 = vVertex * vec3(-1.0,1.0,1.0);
	}

	gl_Position = mMvp * vec4(vVertex1, 1);
	vVaryingUv = vUv;
	vVaryingUv1 = vUv1;

}


