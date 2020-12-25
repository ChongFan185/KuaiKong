#ifndef _MDOTIRELINE_H_
#define _MDOTIRELINE_H_

#include "leobase/Vectors.h"
#include "leobase/Matrices.h"
#include "leobase/mdobject.h"

class MdoTireLine
{
private:
    bool prebAhead;
    float premoveAngle;

    int SEG = 40;     //轨迹线分段数量
    float DIS = 0.15; //每一段轨迹线的长度
    float HalfTireWidth = 0.1; //轮胎宽度的一版

    float fronty; //前轮轴位置
    float reary; //后轮轴位置 ， fronty + reary = 轴距。

    float frontgap; //前轮距
    float reargap;  //后轮距

    float R;

    float CurRadian;
    Vector2 CurCenter;

public:

    Vector2 center;

    typedef struct _tireLinePara{
        float R;
        //float Radian;
        Vector3 St;
        Vector3 seg0;
        //Vector2 IncSeg;
        float rd0;
        float rd1;
        Matrix3 mRot0; //起始线段的旋转矩阵
        Matrix3 mRot1; //后续线段的旋转矩阵
    }tireLinePara;


    tireLinePara line0;

    //MdObject tline;
    VertexBlock vb;
    IndexBlock ib;
//    float R_tire[8]; //每个车轮两条 轨迹线，车身4个角 4条线。
//    float R_body[4];

//    Vector2 Fir_tire[8]; //8条轨迹线的首段
//    Vector2 Fir_body[4]; //4条轨迹线的首段43

//    Vector2 Inc_tire[8]; //8条轨迹线的增量
//    Vector2 Inc_body[4]; //4条轨迹线的增量


public:
    MdoTireLine();
    ~MdoTireLine();

    void setFronty(float f);
    void setReary(float f);
    void setFrontgap(float f);
    void setReargap(float f);
    void set(float fy, float ry, float fgap, float rgap);


    void init(int seg, float dis);
    void createCenter(float degree);

    void createLine(tireLinePara& line, bool bAhead, int vboffset, int color);
//    void createLine(bool bAhead = true);
    void create(float degree, bool ahead);
};

#endif // TIRELINE_H
