
#version 100
precision mediump float;

attribute vec3 vVertex;
attribute vec4 vColor;
//layout(location = 2) in vec2 vUv;

//uniform vec4 vUniColor;
uniform mat4 mMvp;

varying vec4 vVaryingColor;
varying vec2 vVaryingUv;

void main(void)
{
vVaryingColor = vColor;
gl_Position = mMvp * vec4(vVertex, 1);
//vVaryingUv = vUv;
}

