
#version 100
precision mediump float;

attribute vec3 vVertex;
attribute vec3 vNormal;

uniform vec4 vAmbient;
uniform vec4 vDiffuse;
uniform vec4 vSpecular;
uniform vec3 vLightPosition;
 
uniform mat4 mMvp;
uniform mat4 mMv;

uniform bool bMirror;

varying vec4 vVaryingColor;

//mat3 mNormalMatrix = {{mMv[0][0],mMv[0][1],mMv[0][2]},{mMv[1][0],mMv[1][1],mMv[1][2]},{mMv[2][0],mMv[2][1],mMv[2][2]}}; 
//mat3 mNormalMatrix = mat3(mMv[0][0],mMv[0][1],mMv[0][2],mMv[1][0],mMv[1][1],mMv[1][2],mMv[2][0],mMv[2][1],mMv[2][2]); 

void main(void)
{
mat3 mNormalMatrix = mat3(mMv[0][0],mMv[0][1],mMv[0][2],mMv[1][0],mMv[1][1],mMv[1][2],mMv[2][0],mMv[2][1],mMv[2][2]); 

//mat3 mNormalMatrix = {{mMv[0][0],mMv[0][1],mMv[0][2]},{mMv[1][0],mMv[1][1],mMv[1][2]},{mMv[2][0],mMv[2][1],mMv[2][2]}}; 
vec3 vEyeNormal = normalize(mNormalMatrix * vNormal);	  // 表面法线的视觉坐标
vec3 vVertex1 = vVertex;
if(bMirror){
	vVertex1 = vVertex * vec3(-1.0,1.0,1.0);
}

vec4 vPosition4 = mMv * vec4(vVertex1, 1);	// 顶点位置的视觉坐标 （不就是 gl_Position 么？）
vec3 vPosition3 = vPosition4.xyz / vPosition4.w; 

vec3 vLightDir =  normalize(vLightPosition - vPosition3);	// 光照方向

//float diff = max(0.0, dot(vEyeNormal, vLightDir));	//光照方向*法线就得到
float diff = dot(vEyeNormal, vLightDir);
if(diff < 0.0){
	diff = -diff;
}

vVaryingColor.rgb = diff * vDiffuse.rgb;		//计算漫反射颜色

vVaryingColor.rgb += vAmbient.rgb;			// 再加上环境色

vec3 vReflection = normalize(reflect(-vLightDir, vEyeNormal));	//计算镜面光

//float spec = max(0.0 , dot(vEyeNormal, vReflection));
float spec = dot(vEyeNormal, vReflection);
if(spec < 0.0){
	spec = -spec;
}

if(diff != 0.0){
	//float fspec = pow(spec, 64.0);
	//vVaryingColor.rgb += vec3(fspec, fspec,fspec) * vSpecular.rgb ;
	float fspec = pow(spec, 64.0) ;
	vVaryingColor.rgb += vSpecular.rgb * fspec ;
	
	vVaryingColor.a = vDiffuse.a;
}

gl_Position = mMvp * vec4(vVertex1, 1);
}
