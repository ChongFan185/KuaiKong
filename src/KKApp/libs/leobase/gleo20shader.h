#ifndef GLES20SHADER_H
#define GLES20SHADER_H

#include <string>

namespace Gleo20Shader{

const std::string SHADER_TEST = R"(
                           this is model.
                           )";

//SHADER-P
const std::string SHADER_P_VERT = R"(
                             #version 100
                             precision mediump float;

                             attribute vec3 vVertex;

                             uniform vec4 vUniColor;
                             uniform mat4 mMvp;

                             varying vec4 vVaryingColor;
                             varying vec2 vVaryingUv;

                             void main(void)
                             {
                             vVaryingColor = vUniColor;
                             gl_Position = mMvp * vec4(vVertex, 1);
                             //vVaryingUv = vUv;
                             }

                             )";

const std::string SHADER_P_FRAG = R"(
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

                             )";

//SHADER-P-DEPTH
const std::string SHADER_P_DEPTH_VERT = R"(
                             #version 100
                             precision highp float;

                             attribute vec3 vVertex;

                             //uniform vec4 vUniColor;
                             uniform mat4 mMvp;

                             //varying vec4 vVaryingColor;
                             //varying vec2 vVaryingUv;

                             void main(void)
                             {
                             //vVaryingColor = vUniColor;
                             gl_Position = mMvp * vec4(vVertex, 1);
                             //vVaryingUv = vUv;
                             }

                             )";

const std::string SHADER_P_DEPTH_FRAG = R"(
                             #version 100
                             precision highp float;

                             //varying vec4 vVaryingColor;
                             //varying vec2 vVaryingUv;

                             //uniform sampler2DRect texture;

                             //out vec4 vFragColor;

                             void main()
                             {
                             //gl_FragColor = vVaryingColor;
                             //	vFragColor.a = vVaryingColor.a;
                             //  vFragColor = vVaryingColor;
                             //	vFragColor = texture(texture, vVaryingUv.st);
                             }

                             )";

// SHADER-PC
const std::string SHADER_PC_VERT = R"(
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

                              )";

const std::string SHADER_PC_FRAG = R"(
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

                              )";

//SHADER-PU
const std::string SHADER_PU_VERT = R"(

                               #version 100
                               precision highp float;

                               attribute vec3 vVertex;
                               //attribute vec4 vColor;
                               attribute vec2 vUv;

                               uniform mat4 mMvp;
                               uniform vec4 vDiffuse;

                               varying vec4 vVaryingColor;
                               varying vec2 vVaryingUv;


                               void main(void)
                               {
                               vVaryingColor = vDiffuse;

                               vec3 vVertex1 = vVertex;

                               gl_Position = mMvp * vec4(vVertex1, 1);
                               vVaryingUv = vUv;

                               }

                               )";


const std::string SHADER_PU_FRAG = R"(

                               #version 100
                               precision highp float;

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

                               gl_FragColor.rgb = rgb;
                               gl_FragColor.a = vVaryingColor.a;

                               }

                               )";


//SHADER-PUC
const std::string SHADER_PUC_VERT = R"(

                               #version 100
                               precision mediump float;

                               attribute vec3 vVertex;
                               attribute vec4 vColor;
                               attribute vec2 vUv;

                               uniform mat4 mMvp;
                               //uniform bool bMirror;

                               varying vec4 vVaryingColor;
                               varying vec2 vVaryingUv;


                               void main(void)
                               {
                               vVaryingColor = vColor;

                               vec3 vVertex1 = vVertex;

                               //if(bMirror){
                               //vVertex1 = vVertex * vec3(-1.0,1.0,1.0);
                               //}

                               gl_Position = mMvp * vec4(vVertex1, 1);
                               vVaryingUv = vUv;

                               }

                               )";


const std::string SHADER_PUC_FRAG = R"(

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
                                float alp;
                               //vec4 out;

                               rgb = texture2D(uTexture, vec2(vVaryingUv.x, vVaryingUv.y)).rgb;
                               alp = texture2D(uTexture, vec2(vVaryingUv.x, vVaryingUv.y)).w;
                               //rgb = yuv;
                            
                               gl_FragColor.rgb = rgb;
                               //if(rgb.r < 0.02 && rgb.g < 0.02 && rgb.b < 0.02){
                                //   gl_FragColor.a = 0.0;
                                //}
                                //else{
                                //    gl_FragColor.a = vVaryingColor.a;
                               // }
                                gl_FragColor.a = alp * vVaryingColor.a;
                                }

                                )";

//SHADER-ADSG
const std::string SHADER_PN_ADSG_VERT = R"(

                              #version 100
                              precision highp float;

                              attribute vec3 vVertex;
                              attribute vec3 vNormal;

                              uniform vec4 vAmbient;
                              uniform vec4 vDiffuse;
                              uniform vec4 vSpecular;
                              uniform vec3 vLightPosition;

                              uniform mat4 mMvp;
                              uniform mat4 mMv;

                              //uniform bool bMirror;

                              varying vec4 vVaryingColor;

                              //mat3 mNormalMatrix = {{mMv[0][0],mMv[0][1],mMv[0][2]},{mMv[1][0],mMv[1][1],mMv[1][2]},{mMv[2][0],mMv[2][1],mMv[2][2]}};
                              //mat3 mNormalMatrix = mat3(mMv[0][0],mMv[0][1],mMv[0][2],mMv[1][0],mMv[1][1],mMv[1][2],mMv[2][0],mMv[2][1],mMv[2][2]);

                              void main(void)
                              {
                              mat3 mNormalMatrix = mat3(mMv[0][0],mMv[0][1],mMv[0][2],mMv[1][0],mMv[1][1],mMv[1][2],mMv[2][0],mMv[2][1],mMv[2][2]);

                              //mat3 mNormalMatrix = {{mMv[0][0],mMv[0][1],mMv[0][2]},{mMv[1][0],mMv[1][1],mMv[1][2]},{mMv[2][0],mMv[2][1],mMv[2][2]}};
                              vec3 vEyeNormal = normalize(mNormalMatrix * vNormal);	  // 表面法线的视觉坐标
                              vec3 vVertex1 = vVertex;
                              //if(bMirror){
                              //    vVertex1 = vVertex * vec3(-1.0,1.0,1.0);
                              //}

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
                                  float fspec = pow(spec, vSpecular.w) ;
                                  vVaryingColor.rgb += vSpecular.rgb * fspec ;

                                  //vVaryingColor.a = vDiffuse.a;
                              }
                              vVaryingColor.a = vDiffuse.a;

                              gl_Position = mMvp * vec4(vVertex1, 1);
                              }

                              )";


const std::string SHADER_PN_ADSG_FRAG = R"(

                              #version 100
                              precision highp float;

                              varying vec4 vVaryingColor;

                              //uniform vec4 vColor;

                              //out vec4 vFragColor;

                              void main()
                              {
                                  gl_FragColor = vVaryingColor ;
                              //	gl_FragColor.a = vVaryingColor.a;
                              }

                              )";

//SHADER-P2UC-AVM
const std::string SHADER_P2UC_AVM_VERT = R"(

                                    #version 100
                                    precision mediump float;

                                    attribute vec3 vVertex;
                                    attribute vec4 vColor;
                                    attribute vec2 vUv;
                                    attribute vec2 vUv1;

                                    uniform mat4 mMvp;
                                    //uniform bool bMirror;

                                    varying vec3 vVaryingVertex;
                                    varying vec4 vVaryingColor;
                                    varying vec2 vVaryingUv;
                                    varying vec2 vVaryingUv1;

                                    void main(void)
                                    {
                                        vVaryingColor = vColor;
                                        vVaryingVertex = vVertex;

                                        vec3 vVertex1 = vVertex;

                                        //if(bMirror){
                                        //    vVertex1 = vVertex * vec3(-1.0,1.0,1.0);
                                        //}

                                        gl_Position = mMvp * vec4(vVertex1, 1);
                                        vVaryingUv = vUv;
                                        vVaryingUv1 = vUv1;

                                    }

                                    )";

const std::string SHADER_P2UC_AVM_FRAG = R"(

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

                                        )";

//SHADER-P2UC-AVM_OES
const std::string SHADER_P2UC_AVM_OES_VERT = R"(

                                        #version 100
                                        precision mediump float;

                                        attribute vec3 vVertex;
                                        attribute vec4 vColor;
                                        attribute vec2 vUv;
                                        attribute vec2 vUv1;

                                        uniform mat4 mMvp;
                                        //uniform bool bMirror;

                                        varying vec3 vVaryingVertex;
                                        varying vec4 vVaryingColor;
                                        varying vec2 vVaryingUv;
                                        varying vec2 vVaryingUv1;

                                        void main(void)
                                        {
                                            vVaryingColor = vColor;
                                            vVaryingVertex = vVertex;

                                            vec3 vVertex1 = vVertex;

                                            //if(bMirror){
                                            //    vVertex1 = vVertex * vec3(-1.0,1.0,1.0);
                                            //}

                                            gl_Position = mMvp * vec4(vVertex1, 1);
                                            vVaryingUv = vUv;
                                            vVaryingUv1 = vUv1;

                                        }

                                        )";

const std::string SHADER_P2UC_AVM_OES_FRAG = R"(


                                        #version 100
                                        #extension GL_OES_EGL_image_external : require

                                        precision mediump float;

                                        varying vec3 vVaryingVertex;
                                        varying vec4 vVaryingColor;
                                        varying vec2 vVaryingUv;
                                        varying vec2 vVaryingUv1;

                                        uniform samplerExternalOES uTexture;
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
                                            }

                                        }

                                        )";

//SHADER-PUC_I420
const std::string SHADER_PUC_I420_VERT = R"(

                                         #version 100
                                         precision mediump float;

                                         attribute vec3 vVertex;
                                         attribute vec4 vColor;
                                         attribute vec2 vUv;

                                         uniform mat4 mMvp;
                                         //uniform bool bMirror;

                                         varying vec3 vVaryingVertex;
                                         varying vec4 vVaryingColor;
                                         varying vec2 vVaryingUv;

                                         void main(void)
                                         {
                                             vVaryingColor = vColor;
                                             vVaryingVertex = vVertex;

                                             vec3 vVertex1 = vVertex;

                                             //if(bMirror){
                                             //    vVertex1 = vVertex * vec3(-1.0,1.0,1.0);
                                             //}

                                             gl_Position = mMvp * vec4(vVertex1, 1);
                                             vVaryingUv = vUv;
                                             vVaryingUv1 = vUv1;

                                         }

                                        )";

const std::string SHADER_PUC_I420_FRAG = R"(

                                         #version 100

                                         precision mediump float;

                                         varying vec3 vVaryingVertex;
                                         varying vec4 vVaryingColor;
                                         varying vec2 vVaryingUv;

                                         uniform sampler2D uTexY;
                                         uniform sampler2D uTexU;
                                         uniform sampler2D uTexV;

                                         void main()
                                         {
                                             const vec3 offset = vec3(-0.0625, -0.5, -0.5);
                                             const vec3 rcoeff = vec3(1.164, 0.000, 1.596);
                                             const vec3 gcoeff = vec3(1.164, -0.391, -0.813);
                                             const vec3 bcoeff = vec3(1.164, 2.018, 0.000);

                                             float fy, fu, fv;
                                             vec3 yuv;
                                             vec3 rgb;
                                             vec2 adjUv;
                                             bvec2 undertest, overtest;

                                             undertest = lessThanEqual(vVaryingUv, vec2(0.0,0.0));
                                             overtest = greaterThanEqual(vVaryingUv, vec2(1.0,1.0));


                                            if(undertest.x || undertest.y || overtest.x || overtest.y){
                                                 gl_FragColor = vec4(0.0, 0.0, 0.0, 0.0);
                                             }
                                             else{

                                                fy = texture2D(uTexY, vVaryingUv).r;
                                                fu = texture2D(uTexU, vVaryingUv).r;
                                                fv = texture2D(uTexV, vVaryingUv).r;

                                                yuv = vec3(fy, fu, fv) + offset;
                                                rgb.r = dot(yuv,rcoeff);
                                                rgb.g = dot(yuv,gcoeff);
                                                rgb.b = dot(yuv,bcoeff);

                                                rgb.r = clamp(rgb.r , 0.0, 1.0);
                                                rgb.g = clamp(rgb.g , 0.0, 1.0);
                                                rgb.b = clamp(rgb.b , 0.0, 1.0);

                                                gl_FragColor.rgb = rgb;
                                                gl_FragColor.a = vVaryingColor.a;
                                            }

                                        }

                                        )";

//SHADER-P2UC-AVM_I420
const std::string SHADER_P2UC_AVM_I420_VERT = R"(

                                         #version 100
                                         precision mediump float;

                                         attribute vec3 vVertex;
                                         attribute vec4 vColor;
                                         attribute vec2 vUv;
                                         attribute vec2 vUv1;

                                         uniform mat4 mMvp;
                                         //uniform bool bMirror;

                                         varying vec3 vVaryingVertex;
                                         varying vec4 vVaryingColor;
                                         varying vec2 vVaryingUv;
                                         varying vec2 vVaryingUv1;

                                         void main(void)
                                         {
                                             vVaryingColor = vColor;
                                             vVaryingVertex = vVertex;

                                             vec3 vVertex1 = vVertex;

                                             //if(bMirror){
                                             //    vVertex1 = vVertex * vec3(-1.0,1.0,1.0);
                                             //}

                                             gl_Position = mMvp * vec4(vVertex1, 1);
                                             vVaryingUv = vUv;
                                             vVaryingUv1 = vUv1;

                                         }

                                        )";

const std::string SHADER_P2UC_AVM_I420_FRAG = R"(

                                         #version 100

                                         precision mediump float;

                                         varying vec3 vVaryingVertex;
                                         varying vec4 vVaryingColor;
                                         varying vec2 vVaryingUv;
                                         varying vec2 vVaryingUv1;

                                         uniform sampler2D uTexY;
                                         uniform sampler2D uTexU;
                                         uniform sampler2D uTexV;

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

                                             bvec2 undertest, overtest;
                                             bvec2 undertest1, overtest1;

                                             float fy, fu, fv;
                                             vec3 yuv;
                                             vec3 rgb;
                                             vec2 adjUv;


//                                             if(uBlankAndCamera.z < 0.5){
//                                             undertest = lessThanEqual(vVaryingUv, vec2(0.0, 0.0));
//                                             overtest = greaterThanEqual(vVaryingUv, vec2(0.5,0.5));
//                                             } //cam0 的UV clamp
//                                             if(uBlankAndCamera.z >= 0.5 && uBlankAndCamera.z < 1.5){
//                                             undertest = lessThanEqual(vVaryingUv, vec2(0.5, 0.0));
//                                             overtest = greaterThanEqual(vVaryingUv, vec2(1.0,0.5));
//                                             } //cam1 的UV clamp
//                                             if(uBlankAndCamera.z >= 1.5 && uBlankAndCamera.z < 2.5){
//                                             undertest = lessThanEqual(vVaryingUv, vec2(0.0, 0.5));
//                                             overtest = greaterThanEqual(vVaryingUv, vec2(0.5, 1.0));
//                                             } //cam2 的UV clamp
//                                             if(uBlankAndCamera.z >= 2.5 && uBlankAndCamera.z < 3.5){
//                                             undertest = lessThanEqual(vVaryingUv, vec2(0.5, 0.5));
//                                             overtest = greaterThanEqual(vVaryingUv, vec2(1.0, 1.0));
//                                             } //cam3 的UV clamp
//                                             if(uBlankAndCamera.z >= 3.5){
//                                                 undertest = bvec2(0, 0);
//                                                 overtest = bvec2(0, 0);
//                                             }

                                             if(uBlankAndCamera.z < 3.5){
                                             // 在creatMesh函数中，参考UV用的是单幅贴图的坐标，所以无需再根据camID进行坐标偏移。
                                                undertest = lessThanEqual(vVaryingUv, vec2(0.0, 0.0));
                                                overtest = greaterThanEqual(vVaryingUv, vec2(1.0, 1.0));
                                                 undertest1 = lessThanEqual(vVaryingUv1, vec2(0.0, 0.0));
                                                 overtest1 = greaterThanEqual(vVaryingUv1, vec2(1.0, 1.0));
                                             }
                                             if(uBlankAndCamera.z >= 3.5){
                                             // 在creatMesh函数中，参考UV用的是单幅贴图的坐标，所以无需再根据camID进行坐标偏移。
                                                undertest = lessThanEqual(vVaryingUv, vec2(0.0, 0.0));
                                                overtest = greaterThanEqual(vVaryingUv, vec2(1.0, 1.0));
                                                 undertest1 = bvec2(0, 0);
                                                 overtest1 = bvec2(0, 0);
                                             }

                                                 // undertest1 = bvec2(0, 0);
                                                 // overtest1 = bvec2(0, 0);
                                                 // undertest = bvec2(0, 0);
                                                 // overtest = bvec2(0, 0);

                                             // undertest = lessThanEqual(vVaryingUv, vec2(0.0,0.0));
                                             // overtest = greaterThanEqual(vVaryingUv, vec2(1.0,1.0));

                                             // undertest1 = lessThanEqual(vVaryingUv1, vec2(0.0,0.0));
                                             // overtest1 = greaterThanEqual(vVaryingUv1, vec2(1.0, 1.0));

                                         //
                                             if(vVaryingColor.a < 0.98 && (undertest1.x || undertest1.y || overtest1.x || overtest1.y)){
                                                 gl_FragColor = vec4(0.0, 0.0, 0.0, 0.0);
                                             }
                                             else if(undertest.x || undertest.y || overtest.x || overtest.y){
                                                 gl_FragColor = vec4(0.0, 0.0, 0.0, 0.0);
                                             }
                                             else{

                                                 if(uBlankAndCamera.z < 0.5){
                                                     adjUv.x = vVaryingUv.x * 0.5 ;
                                                     adjUv.y = vVaryingUv.y * 0.5 ;
                                                 } //cam0 的UV clamp
                                                 if(uBlankAndCamera.z >= 0.5 && uBlankAndCamera.z < 1.5){
                                                    adjUv.x = vVaryingUv.x * 0.5 + 0.5;
                                                    adjUv.y = vVaryingUv.y * 0.5 ;
                                                 } //cam1 的UV clamp
                                                 if(uBlankAndCamera.z >= 1.5 && uBlankAndCamera.z < 2.5){
                                                    adjUv.x = vVaryingUv.x * 0.5 ;
                                                    adjUv.y = vVaryingUv.y * 0.5 + 0.5;
                                                 } //cam2 的UV clamp
                                                 if(uBlankAndCamera.z >= 2.5 && uBlankAndCamera.z < 3.5){
                                                    adjUv.x = vVaryingUv.x * 0.5 + 0.5;
                                                    adjUv.y = vVaryingUv.y * 0.5 + 0.5;
                                                 } //cam3 的UV clamp
                                                 if(uBlankAndCamera.z >= 3.5){
                                                     adjUv.x = vVaryingUv.x;
                                                     adjUv.y = vVaryingUv.y;
                                                 }
                                             //adjUv.x = vVaryingUv.x * uUvAdapter.x + uUvAdapter.y;
                                             //adjUv.y = vVaryingUv.y * uUvAdapter.z + uUvAdapter.w;

                                             fy = texture2D(uTexY, adjUv).r;
                                             fu = texture2D(uTexU, adjUv).r;
                                             fv = texture2D(uTexV, adjUv).r;
                                             //fy = texture2D(uTexY, vVaryingUv).r;
                                             //fu = texture2D(uTexU, vVaryingUv).r;
                                             //fv = texture2D(uTexV, vVaryingUv).r;

                                             yuv = vec3(fy, fu, fv) + offset;
                                             rgb.r = dot(yuv,rcoeff);
                                             rgb.g = dot(yuv,gcoeff);
                                             rgb.b = dot(yuv,bcoeff);
                                             //rgb = yuv;

                                         //	rgb = texture2D(uTexture, adjUv).rgb;

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

                                        )";

//SHADER-P2UC-AVM_NV21
const std::string SHADER_P2UC_AVM_NV21_VERT = R"(

                                        )";

const std::string SHADER_P2UC_AVM_NV21_FRAG = R"(

                                        )";

//SHADER-P2UC-AVM_422
const std::string SHADER_P2UC_AVM_422_VERT = R"(


                                        #version 100
                                        precision mediump float;

                                        attribute vec3 vVertex;
                                        attribute vec4 vColor;
                                        attribute vec2 vUv;
                                        attribute vec2 vUv1;

                                        uniform mat4 mMvp;
                                        //uniform bool bMirror;

                                        varying vec3 vVaryingVertex;
                                        varying vec4 vVaryingColor;
                                        varying vec2 vVaryingUv;
                                        varying vec2 vVaryingUv1;

                                        void main(void)
                                        {
                                            vVaryingColor = vColor;
                                            vVaryingVertex = vVertex;

                                            vec3 vVertex1 = vVertex;

                                            //if(bMirror){
                                            //    vVertex1 = vVertex * vec3(-1.0,1.0,1.0);
                                            //}

                                            gl_Position = mMvp * vec4(vVertex1, 1);
                                            vVaryingUv = vUv;
                                            vVaryingUv1 = vUv1;

                                        }

                                       )";

const std::string SHADER_P2UC_AVM_422_FRAG = R"(

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

                                        )";

};

#endif // GLES20SHADER_H
