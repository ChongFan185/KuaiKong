#ifndef __GLEU_H__
#define __GLEU_H__

#include "Matrices.h"
#include "Vectors.h"
#include "gleoshader.h"


//namespace Gleu{




//}


class Gleu{
public:
    typedef enum{
        TextureType_YUV422 = 1,
        TextureType_NV21 = 2,
        TextureType_I420 = 3,
        TextureType_OES = 4,
        TextureType_Rgb = 5,
        TextureType_Inner = 6,
        TextureType_COUNT = 7
    }TextureType;

public:
    Gleu();
    ~Gleu();
    void calcFrustum(const Vector3& position, const Vector3& rotation, float windowRatio);
//    void calcFrustum(const ViewPoint& vp, float windowRatio);
    void calcOrthFrustum(float x0, float x1, float y0, float y1, float z0, float z1);

    void calc(const Matrix4 m4);

    void initShaderUni();
    void choiceAvmShader(int choice);

public:
// 设置Uniform时使用的变量
struct {
    int shaderId;
}current;

Matrix4 identity;
Matrix4 mv;
Matrix4 projection;
Matrix4 mvp;
Vector3 position;
Vector3 rotation;
float ratio;


//LeMvp mvp0,mvp1,mvpui,mvporg;

struct {
    Vector3 pos;
    Vector3 color;
}lit0;

struct {
    Vector4 color0;
    Vector4 color1;
//    bool bMirror;
}user;

struct {
    Vector4* pAmbient;
    Vector4* pDiffuse;
    Vector4* pSpecular;
    Vector4* pColor;
    float *pTransparency;
}material;

struct {
    Vector4 ambient;
    Vector4 diffuse;
    Vector4 specular;
    Vector4 color;
    float pTransparency;
}materialDefault;

struct _xUni{

    //uv坐标都是独立生成的，但是实际输入的纹理图像可能是2x2的组合形式，因为需要通知shader调整uv坐标
    //uvAdpter的保存格式是（kx，bx，ky，by）
    //shader调整的方法是 newU = kx*U + bx；newV = ky*V + by；
    //比如，2x2图像输入模式下，camera0位于左上角，那么它的纹理调整应该是 newU = 0.5*U + 0.0； newV = 0.5*V + 0.5；
    //如果输入的还是独立的纹理图像，那么 newU = 1.0*U + 0.0; newV = 1.0*V + 0.0; 则UV保持不变
    Vector4 uvAdpter;
    Vector4 uvAdpterValue[4];

    Vector4 yuvInfo;

    struct {
        Vector4 blankAndCamera;  //x= width，y= height，z=camid，w=enable wb，如果z=4， 则shader内部不做UV clamp。
        Vector4 coff0;
        Vector4 coff1;
    }cambalance;

}avm;


    //GlsHelper hlp;
    gleo::Shader shaderP;
    gleo::Shader shaderPC;
    gleo::Shader shaderAdsg;
    gleo::Shader shaderPU;
    gleo::Shader shaderPUC;
    gleo::Shader shaderPDepth;

    gleo::Shader shaderAvmRGB;
    gleo::Shader shaderAvm422;
    gleo::Shader shaderAvmNv21;
    gleo::Shader shaderAvmOes;
    gleo::Shader shaderAvmI420;
    gleo::Shader *shaderAvm;

//uv坐标都是独立生成的，但是实际输入的纹理图像可能是2x2的组合形式，因为需要通知shader调整uv坐标
//uvAdpter的保存格式是（kx，bx，ky，by）
//shader调整的方法是 newU = kx*U + bx；newV = ky*V + by；
//比如，2x2图像输入模式下，camera0位于左上角，那么它的纹理调整应该是 newU = 0.5*U + 0.0； newV = 0.5*V + 0.5；
//如果输入的还是独立的纹理图像，那么 newU = 1.0*U + 0.0; newV = 1.0*V + 0.0; 则UV保持不变
//    Vector4 uvAdpter;
//    Vector4 uvAdpterValue[4];

//struct {
//    Vector4 blankAndCamera;
//    Vector4 coff0;
//    Vector4 coff1;
//}cambalance;

//Matrix3 uniNmlMat;
//Vector3 uniLit0Pos;
//Vector4 uniLit0Color;
//Vector4 uniColor0;
};



#endif // SPECTATORTDP_H
