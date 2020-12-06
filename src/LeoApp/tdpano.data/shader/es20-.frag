
#version 100 
precision mediump float;

varying vec4 vVaryingColor; 
varying vec2 vVaryingUv;

uniform sampler2D uTexture;

//out vec4 vFragColor;

void main() 
{ 
	const vec3 offset = vec3(-0.0625, -0.5, -0.5);
	const vec3 rcoeff = vec3(1.164, 0.000, 1.596);
	const vec3 gcoeff = vec3(1.164, -0.391, -0.813);
	const vec3 bcoeff = vec3(1.164, 2.018, 0.000);

	vec3 yuv;
	vec3 rgb;

	yuv = texture2D(uTexture, vec2(vVaryingUv.x, vVaryingUv.y)).rgb ;
	rgb = yuv;

	yuv+= offset;
	rgb.r = dot(yuv,rcoeff);
	rgb.g = dot(yuv,gcoeff);
	rgb.b = dot(yuv,bcoeff);

	gl_FragColor.rgb = rgb;
	gl_FragColor.a = vVaryingColor.a;

} 

