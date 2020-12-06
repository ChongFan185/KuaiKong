
//<P-VERT>
// #version 100
// precision mediump float;

// attribute vec3 vVertex;

// uniform vec4 vUniColor;
// uniform mat4 mMvp;

// varying vec4 vVaryingColor;
// varying vec2 vVaryingUv;

// void main(void)
// {
// vVaryingColor = vUniColor;
// gl_Position = mMvp * vec4(vVertex, 1);
// //vVaryingUv = vUv;
// }
//</P_VERT>


//<P-FRAG>
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
//</P-FRAG>