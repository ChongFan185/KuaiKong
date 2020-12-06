
#version 100 
precision mediump float;

varying vec3 vVaryingVertex;
varying vec4 vVaryingColor; 
varying vec2 vVaryingUv;
varying vec2 vVaryingUv1;

uniform sampler2D uTexture;
// uniform vec4  uUvAdapter; 	   // (k1,b1,k2,b2)   newU=U*k1+b1;  newV=V*k2+b2;
uniform vec4  uBlankAndCamera; // x= blank width, y= blank height, z=camId, w=0,disable 补偿，w=1，enable 补偿
uniform vec4  uCofficent0;     // x或者y坐标负方向的补偿因子，跟C++代码里的 rgn0 并不一致
uniform vec4  uCofficent1;     // x或者y坐标正方向的补偿因子，跟C++代码里的 rgn1 并不一致


void main() 
{ 

	float blankhw = uBlankAndCamera.x / 2.0;
	float blankhh = uBlankAndCamera.y / 2.0;

	vec3 k;
	float b;
	vec3 tCofficient;

	bvec2 undertest, overtest;
	bvec2 undertest1, overtest1;

	vec3 rgb;

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
	
//
	if(vVaryingColor.a < 0.98 && (undertest1.x || undertest1.y || overtest1.x || overtest1.y)){
		gl_FragColor = vec4(0.0,0.0,0.0,0.0);
	}
	else if(undertest.x || undertest.y || overtest.x || overtest.y){
		gl_FragColor = vec4(0.0, 0.0, 0.0, 0.0);
	}
	else{

	//adjUv.x = (vVaryingUv.x + uUvAdapter.x) / uUvAdapter.z;
	//adjUv.y = (vVaryingUv.y + uUvAdapter.y) / uUvAdapter.w;
	// adjUv.x = vVaryingUv.x * uUvAdapter.x + uUvAdapter.y;
	// adjUv.y = vVaryingUv.y * uUvAdapter.z + uUvAdapter.w;

	rgb = texture2D(uTexture, vVaryingUv).rgb;

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
	//gl_FragColor = vec4(0.9, 0.5, 0.5, 0.5);
	}

} 
