
#version 100 
precision mediump float;

varying vec3 vVaryingVertex;
varying vec4 vVaryingColor; 
varying vec2 vVaryingUv;
varying vec2 vVaryingUv1;

uniform sampler2D uTexture;
uniform vec4  uYuvInfo; // x= yuv width, y = yuv height

// uniform vec4  uUvAdapter; 	   // (k1,b1,k2,b2)   newU=U*k1+b1;  newV=V*k2+b2;
uniform vec4  uBlankAndCamera; // x= blank width, y= blank height, z=camId, w=0,disable 补偿，w=1，enable 补偿
uniform vec4  uCofficent0;     // x或者y坐标负方向的补偿因子，跟C++代码里的 rgn0 并不一致
uniform vec4  uCofficent1;     // x或者y坐标正方向的补偿因子，跟C++代码里的 rgn1 并不一致


void main() 
{ 
	const vec3 offset = vec3(-0.0625, -0.5, -0.5);
	const vec3 rcoeff = vec3(1.164, 0.000, 1.596);
	const vec3 gcoeff = vec3(1.164, -0.391, -0.813);
	const vec3 bcoeff = vec3(1.164, 2.018, 0.000);

	float blankhw = uBlankAndCamera.x / 2.0;
	float blankhh = uBlankAndCamera.y / 2.0;

	vec3 k;
	float b;
	vec3 tCofficient;

	vec2 intUv0, intUv1, intUv2, intUv3;
	vec2 dotUv;
	float dotx;

	bvec2 undertest, overtest;
	bvec2 undertest1, overtest1;

	vec4 _c0,_c1,_c2,_c3;
	vec3 _yuv0,_yuv1,_yuv2,_yuv3, _yuva0, _yuva1;

	vec3 yuv;
	vec3 rgb;

	float uYuvHalfWidth, uYuvHeight;

	uYuvHalfWidth = uYuvInfo.x / 2.0;
	uYuvHeight = uYuvInfo.y;
	
	if(uBlankAndCamera.z < 0.5){
	undertest = lessThanEqual(vVaryingUv, vec2(0.0, 0.0));
	overtest = greaterThanEqual(vVaryingUv, vec2(0.5,0.5));
	} //cam0 的UV clamp
	if(uBlankAndCamera.z >= 0.5 && uBlankAndCamera.z < 1.5){
	undertest = lessThanEqual(vVaryingUv, vec2(0.5, 0.0));
	overtest = greaterThanEqual(vVaryingUv, vec2(1.0,0.5));
	} //cam1 的UV clamp
	if(uBlankAndCamera.z >= 1.5 && uBlankAndCamera.z < 2.5){
	undertest = lessThanEqual(vVaryingUv, vec2(0.0, 0.5));
	overtest = greaterThanEqual(vVaryingUv, vec2(0.5, 1.0));
	} //cam2 的UV clamp
	if(uBlankAndCamera.z >= 2.5 && uBlankAndCamera.z < 3.5){
	undertest = lessThanEqual(vVaryingUv, vec2(0.5, 0.5));
	overtest = greaterThanEqual(vVaryingUv, vec2(1.0, 1.0));
	} //cam3 的UV clamp
	if(uBlankAndCamera.z >= 3.5){
		undertest = bvec2(0, 0);
		overtest = bvec2(0, 0);
	}

	if(uBlankAndCamera.z < 3.5){
	// 在creatMesh函数中，参考UV用的是单幅贴图的坐标，所以无需再根据camID进行坐标偏移。
		undertest1 = lessThanEqual(vVaryingUv1, vec2(0.0, 0.0));
		overtest1 = greaterThanEqual(vVaryingUv1, vec2(1.0, 1.0));	
	}
	if(uBlankAndCamera.z >= 3.5){
	// 在creatMesh函数中，参考UV用的是单幅贴图的坐标，所以无需再根据camID进行坐标偏移。
		undertest1 = bvec2(0, 0);
		overtest1 = bvec2(0, 0);	
	}
	// undertest = lessThanEqual(vVaryingUv, vec2(0.0,0.0));
	// overtest = greaterThanEqual(vVaryingUv, vec2(1.0,1.0));

	// undertest1 = lessThanEqual(vVaryingUv1, vec2(0.0,0.0));
	// overtest1 = greaterThanEqual(vVaryingUv1, vec2(1.0, 1.0));	
	
	if(vVaryingColor.a < 0.98 && (undertest1.x || undertest1.y || overtest1.x || overtest1.y)){
		gl_FragColor = vec4(0.0,0.0,0.0,0.0);
	}
	else if(undertest.x || undertest.y || overtest.x || overtest.y){
		gl_FragColor = vec4(0.0, 0.0, 0.0, 0.0);
	}
	else{


	intUv0 = vec2(floor(vVaryingUv.x * uYuvHalfWidth) +0.1, floor(vVaryingUv.y * uYuvHeight)+0.1);
	intUv1 = vec2(intUv0.x + 1.0, intUv0.y);
	intUv2 = vec2(intUv0.x , intUv0.y + 1.0);
	intUv3 = vec2(intUv0.x + 1.0, intUv0.y + 1.0);

	dotUv = vec2(fract(vVaryingUv.x * uYuvHalfWidth), fract(vVaryingUv.y * uYuvHeight));	
	
	if(dotUv.x < 0.5){
		dotx = dotUv.x * 2.0;
		
		_c0 = texture2D(uTexture, vec2(intUv0.x/uYuvHalfWidth , intUv0.y/uYuvHeight));
	//	_c1 = texture2D(uTexture, vec2(intUv1.x/640.0 , intUv1.y/720.0));
		_c2 = texture2D(uTexture, vec2(intUv2.x/uYuvHalfWidth , intUv2.y/uYuvHeight));
	//	_c3 = texture2D(uTexture, vec2(intUv3.x/640.0 , intUv3.y/720.0));

		_yuv0 = vec3(_c0.g, _c0.b, _c0.r);
		_yuv1 = vec3(_c0.w, _c0.b, _c0.r);

		_yuv2 = vec3(_c2.g, _c2.b, _c2.r);
		_yuv3 = vec3(_c2.w, _c2.b, _c2.r);
	
	}

    else{
		dotx = fract(dotUv.x * 2.0);
		
		_c0 = texture2D(uTexture, vec2(intUv0.x/uYuvHalfWidth , intUv0.y/uYuvHeight));
		_c1 = texture2D(uTexture, vec2(intUv1.x/uYuvHalfWidth , intUv1.y/uYuvHeight));
		_c2 = texture2D(uTexture, vec2(intUv2.x/uYuvHalfWidth , intUv2.y/uYuvHeight));
		_c3 = texture2D(uTexture, vec2(intUv3.x/uYuvHalfWidth , intUv3.y/uYuvHeight));

		_yuv0 = vec3(_c0.w, _c0.b, _c0.r);
		_yuv1 = vec3(_c1.g, _c1.b, _c1.r);

		_yuv2 = vec3(_c2.w, _c2.b, _c2.r);
		_yuv3 = vec3(_c3.g, _c3.b, _c3.r);
	
	}

	_yuva0 = mix(_yuv0, _yuv1, dotx);
	_yuva1 = mix(_yuv2, _yuv3, dotx);
	yuv = mix(_yuva0, _yuva1, dotUv.y);

	//yuv = _yuv0;

	yuv+= offset;
	rgb.b = dot(yuv,rcoeff);
	rgb.g = dot(yuv,gcoeff);
	rgb.r = dot(yuv,bcoeff);

////亮度补偿部分的代码
	if(uBlankAndCamera.w > 0.5){
		if(uBlankAndCamera.z < 1.5){  //// cam0,cam1, compenset by x direction
			if(vVaryingVertex.x <= -blankhw) {
				rgb = rgb * uCofficent0.rgb;
				}
			else if(vVaryingVertex.x < blankhw) {
				k = (uCofficent1.rgb - uCofficent0.rgb);
				b = ((vVaryingVertex.x + blankhw) / (blankhw * 2.0));
				tCofficient = k * b + uCofficent0.rgb;
				rgb = rgb * tCofficient;
			}
			else{
				rgb = rgb * uCofficent1.rgb;
			}
		}
		else{						//// cam0,cam1, compenset by y direction
			if(vVaryingVertex.y <= -blankhh) {
				rgb = rgb * uCofficent0.rgb;
				}
			else if(vVaryingVertex.y < blankhh) {
				k = (uCofficent1 - uCofficent0).rgb;
				b = ((vVaryingVertex.y + blankhh) / (blankhh * 2.0));
				tCofficient = k * b + uCofficent0.rgb;
				rgb = rgb * tCofficient;
			}
			else{
				rgb = rgb * uCofficent1.rgb;
			}
		}
	}

//////补偿代码结束
	rgb.r = clamp(rgb.r , 0.0, 1.0);
	rgb.g = clamp(rgb.g , 0.0, 1.0);
	rgb.b = clamp(rgb.b , 0.0, 1.0);

 	gl_FragColor.rgb = rgb;
 	gl_FragColor.a = vVaryingColor.a;
	}

} 
