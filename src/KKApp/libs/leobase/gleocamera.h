#ifndef __GLEOCAMERA_H__
#define __GLEOCAMERA_H__

#include "Matrices.h"
#include "Vectors.h"



//typedef struct{
//    Vector3 pos;
//    Vector3 rot;
//}ViewPoint;

class ViewPoint{
public:
    ViewPoint();
    ~ViewPoint();
    void rotate(float x, float y, float z);
    void trans(float x, float y, float z);
    void rotateTo(float x, float y, float z);
    void transTo(float x, float y, float z);
    void rotate(Vector3& v);
    void rotateTo(Vector3& v);
    void trans(Vector3& v);
    void transTo(Vector3& v);

    void customTrans2D(float x, float y);
    void clamp(ViewPoint &min, ViewPoint &max);
    void clamppos(ViewPoint &min, ViewPoint &max);
    void clamprot(ViewPoint &min, ViewPoint &max);
    void clamppos();
    void clamprot();
    void clamp();
    void setPos(const Vector3& min, const Vector3& vct, const Vector3& max);
    void setRot(const Vector3& min, const Vector3& vct, const Vector3& max);

public:
    Vector3 pos;
    Vector3 rot;
    Vector3 posmin;
    Vector3 posmax;
    Vector3 rotmin;
    Vector3 rotmax;
};

class GleoCamera
{
public:
    GleoCamera();
    ~GleoCamera();

    bool saveVp(const char* filename);
    bool loadVp(const char* filename);
    void defaultVp();

    void updateVp();

    void reset2D();
    //void turnTune(int getChkItemOutside, int getChkCamOutside);
    void turnTune(int item);

    void turn3dTo(int dismode);
    void turn3dTo(ViewPoint& vp);
    void jump3dTo(int dismode);
    void jump3dTo(ViewPoint& vp);

    void turnMirTo(int dismode);
    void jumpMirTo(int dismode);

    void clamp2d();
    void clamp3d();
    void clampmir();
    void dbclamp(Vector3& v, Vector3& min, Vector3& max)
    {
        if(v.x < min.x)v.x = min.x;
        else if(v.x > max.x)v.x = max.x;

        if(v.y < min.y)v.y = min.y;
        else if(v.y > max.y)v.y = max.y;

        if(v.z < min.z)v.z = min.z;
        else if(v.z > max.z)v.z = max.z;
        return;
    }


//    void rotate(float x, float y, float z);
//    void trans(float x, float y, float z);
//    void rotateTo(float x, float y, float z);
//    void transTo(float x, float y, float z);

    void resize(int width, int height);
//    void calcMatrix();

public:
    // 调整视角使用的变量
    ViewPoint vp2d; //2d画面的视角
    // ViewPoint vp2d_f;
    // ViewPoint vp2d_b;
    ViewPoint vp3d; //3d画面的视角
    ViewPoint vpmir;//后视镜画面的视角
//    ViewPoint vpTune[5];
    ViewPoint vpholder[14];  // 前6个用来保存默认视角， 后8个用来保存调试或者其他用处的视角，其实目前只用了三个


    ViewPoint vp2d_min;
    ViewPoint vp2d_max;
    ViewPoint vp3d_min;
    ViewPoint vp3d_max;
    ViewPoint vpmir_min;
    ViewPoint vpmir_max;

    int cameraChoice;

    bool bTimerOn;
    bool bTuneMode;
    bool bVideoOn;
    int nextVp;
    int currentVp;

    int camWidth;
    int camHeight;
    float camRatio;

    const int ANIMATION_STEPS = 30;

//    QTimer myTimer;
};





#endif // SPECTATORTDP_H
