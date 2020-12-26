#ifndef _RDRRPANO_H_
#define _RDRRPANO_H_

#include "leobase/common_leo.h"
#include "leobase/mdobject.h"
#include "leobase/gleo.h"
#include "leobase/gleoshader.h"
#include "leobase/gleu.h"

#include "renderer/whitebalance.h"
#include "renderer/mdotireline.h"
#include "renderer/mdotunerect.h"
#include "renderer/mdoallbs.h"

#include <string>

//#define QT
#ifdef QT
#include <QOpenGLFunctions>
#else
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#endif

using namespace std;

class IndexBlock;
class MdObject;

class ModelAvmesh;
class GleoCamera;
//class Gleu;
class TduiP1;
class TduiP2;
class TduiTune;
class TduiAuto;
class TduiMark;
class Tdui;
class BmpLsimple;




class RendererTdp //: public RendererHelper
#ifdef QT
        : public QOpenGLFunctions
#endif
{

public:
    RendererTdp();
    ~RendererTdp();

    void modiDirectory(const char* dir);
    void modiModelFile(const char* file);
    void modiBrpFile(const char* file);

    bool loadModelFile(const char* file = NULL);
    bool loadBrpFile(const char* file = NULL);
    bool loadMergerFile(const char* file = NULL);
    bool loadMountFile(const char* file = NULL);

    bool reloadVs();
    bool initial(std::string& error);  // 主要用于加载必要的外部文件
    void initGL();

    void drawFrame();
    void resize(int width, int height);

    bool process(int cmd);
    bool config(int cmd);

    void drawOrg(int cam);
    void drawAvm();
    void drawCar(bool bTrans = false);
    void drawTune(int item, int cam);
    void drawUi();
//    void drawLine();



    void keyPressEvent(char key);
    void mouseReleaseEvent(int x,int y);
    void mousePressEvent(int x,int y);
    void mouseMoveEventLB(int x,int y); //鼠标左键移动
    void mouseMoveEventRB(int x,int y); //鼠标右键移动

    void setTextureType(int type);
    void setTextureAssemble(bool b);
    void setTextureIsBuf(bool b);
    void setTextureId(int tid0, int tid1, int tid2);
    void setTextureSepId(int camid, int tid0, int tid1, int tid2);

    void switchInnerDemo(bool b);
    void switchTex();
    void switchExtex(bool ext_assb2x2mode);
    void switchIntex(bool bUsePic);

    void innerTexture();
    int getTextureId(int yuv);

//    void _textureOffset(bool b);

    void update(int width, int height); //外部告知capture 的长宽， 内部为预处理参数做一些准备

    void update(unsigned char* buf, int width, int height,const Vector3& ex_angle=Vector3(0,0,0)); // 更新 buf
    void update(unsigned char* bufy, unsigned char* bufu, unsigned char* bufv, int width, int height,const Vector3& ex_angle=Vector3(0,0,0)); //更新 buf
    void update(unsigned char* buf0, unsigned char* buf1, unsigned char* buf2 , unsigned char* buf3, int width, int height,const Vector3& ex_angle=Vector3(0,0,0)); //更新 buf

    void updateExtra();

//    void updatewb(unsigned char* buf, int width, int height);
    void initialwb(int bufwidth, int bufheight);
    void updatewb(unsigned char* bufy, unsigned char* bufu, unsigned char* bufv, int width, int height);

    void turnCamera(int item, int cam);

    /*
    *为了在JNI层（不依赖UI系统），实现滑动窗口的效果，drawFrame函数修改为以viewPort为绘图对象的模式。
    * 通过索引viewport 来绘制各种界面， 这样，就可以通过修改 viewport，实现 窗口滑动的功能
    */
    //在resize函数中调用， 用来初始化各种 viewport 的参数
    void viewPortResize(int width, int height);
    //void viewPortResize_client_fuhuang(int width, int height);
    //把viewport约束到 显示窗口内
    Vector4 viewPortClamp(const Vector4& rct,const Vector4& clp);
    //生成viewport的边框
    void viewPort2vb(const Vector4& rct, VertexBlock* vb);  //通过Viewport Vector4， 生成一个边框vb（画边框用）
    //void viewPortDynamic(int disMode, int disCam);
    //切换viewport，以前代码中的各种显示切换操作， 都可以全部转向调用下面这个函数了。
    void viewPortChange(int item, bool bResetCamera = true);
    void viewPortChange_client_fuhuang(int item);

    //针对特定的应用场景，修改相机配置
    void cameraAdaption();
    void cameraAdaption_client_fuhuang(int item);

    //下面两个函数， 主要实现了手指滑动切换窗口， 但是这两个函数，都用到了全局变量，
    //不仅要系统的事件触发， 还需要在drawFrame 里，主动调用，实现完整的界面滑动
    //单指操作，切换界面的接口
    void viewPortMove(float x, float y, bool check = false);
    //双指操作，切换界面的接口
    void viewPortMove2(float x, float y, bool check = false);
    //用来实现，在2D界面上通过点选切换 摄像头的功能
    int viewPortPick(float x, float y);

    bool getDrawing(){
        return opera.isDrawing;
    }

    void setUpdating(bool b){
        opera.isTexUpdating = b;
        return;
    }

    bool checkMdoTexture(MdObject* ob);


    //调试控制

    struct{
        bool enableConfig=true;
        bool forceCopyCamera = false;

        bool slide2dOn = false;
        bool slideOrgOn = false;
        bool slide3dOn = false;
        bool slideMirrorOn = false;

        bool enAllbs = false;
        bool enAvm2d = false;

        bool enButton = false;
        bool en2DPick = false;

        bool enDrawCar = true;
        bool enDrawAvm = true;
        bool enDrawOrg = true;

        bool lineTrailOn = false;
        bool lineRearOn = false;
        bool lineRadarOn = false;

        bool innerIsBmp = false;
    }ctrl;

 private:

    // 窗口大小，绘图位置，相关的变量
    int WndRet;
    int VpRet;

    struct _operation{
        int tmpCmd;
        bool isDrawing;
        bool isTexUpdating;
        bool isAutoCalib;
        bool isSaveImage;
        bool isCalibImageOk;
    }opera;

    // 保存交互过程中，上一个触摸位置
    int lastx;
    int lasty;

    // 保存交互过程中，
    int startx;
    int starty;

    bool pressIn2D;
    bool pressResponding;
    bool viewportChanging;
    bool deepChanging;
    bool checkSlideAction;
    bool slideAction0;
    bool slideAction2;

    bool bAhead = true;
    float moveAngle = 0.0;

public:

    int disMode; // 0, 单窗口， 1，双窗口， 2， 调试窗口
    int disCam;  // 在双窗口模式下，第二口显示哪个摄像头 0~3=摄像头，4=3D
    int disAngle; // 视角，目前代码设置了4个视角

    struct _scrn{
        int w;
        int h;
        float ratio;
        float scalew;  //代码中很多图像区域都是按 1280*720来设计规划的，所以屏幕尺寸不是1280*720时，
        float scaleh; //需要用这两个变量来进行尺寸缩放
        bool isHorizontal; // 记录屏幕的方向状态， true：水平方向 false：垂直方向

        //显示模式0，全屏显示
        float AW;
        float AH;

        //显示模式1,  2分屏,屏幕分为BC 两个区域
        float BW;
        float CW;
        float BH;

        //调试模式， 3分屏， 屏幕分为DEF 三个区域
        float DW;
        float DH;
        float EW;
        float EH;
        float FW;
        float FH;
    }scrn;



    //分屏显示相关参数，区域，vb，ib， 目前是三种显示模式，每个模式有两个屏幕区域
    Vector4  vuport_pad;
    static const int DIS_GRP = 2; //num_group, 组数
    static const int DIS_ITEM = 8; //num_item，每组的项数  //为了实现显示切换过程中的滑动窗效果，代码逻辑修改为以 ViewPort 为基本显示对象。遍历ViewPort，把需要显示的绘制出来

    //_painter结构体 对应一个viewport，一个边框vb，以及绘图模式，绘图的时候直接遍历 _painter,然后通过viewport状态来决定是否绘图显示
    struct _painter{
        bool on;
        // item用来表示此vuport 显示什么内容
        // 0,1,2,3 = 原始图像， 4= 3D， 5= 2D， 6=后视镜画面
        int item;
        Vector4 vuport;  //三种分屏模式，第一组全屏， 第二组2分屏，第三组调试界面3分屏，以后可能会有第四种，增加数组即可
        VertexBlock frame;  //对应分屏显示区域外框的 VB
    }painter[DIS_GRP][DIS_ITEM];

    IndexBlock ibrect;

    Vector4 viewport[4];
    VertexBlock viewport_frame[4];
    int viewport_cnt;

    VertexBlock vbottom;
    IndexBlock ibottom;

    //下面几个变量用来保存，窗口尺寸确定后， 屏幕分割的区域(DIV分区， 减去pad 才是viewport)
    Vector4 rect_A;    //单屏显示的画面分割
    Vector4 rect_B0, rect_B1;   //双屏显示的画面分割
    Vector4 rect_C0, rect_C1, rect_C2;  //调试界面的画面分割
    //下面几个变量，用来实现屏幕显示的滑动窗切换动画
    Vector4 rect_mv00;  //全屏滑动窗口
    Vector4 rect_mv10;  //单视和3D滑动窗口
    Vector4 rect_mv11;  //单视和3D滑动窗口
    Vector4 rect_mv12;  //2D滑动窗口
    unsigned int CurViewPort;
    unsigned int CurViewItem;



    // OpenGL相关的变量
    GLuint fboid;
    GLuint rborgba;
    GLuint rbodepth;

    unsigned char *NewBuf[4];
    unsigned int  NewBuffers;
    unsigned int  NewPaintRequest;

    std::string strFileView;
    std::string strFileMount;
    std::string strFileMerger;
    std::string strFileBrp;
    std::string strFileCar;
    std::string strStoragePath;

    std::string ifn;
    std::string ofn;

//    //GlsHelper hlp;
//    gleo::Shader shaderP;
//    gleo::Shader shaderPC;
//    gleo::Shader shaderAdsg;
//    gleo::Shader shaderPU;
//    gleo::Shader shaderPUC;
//    gleo::Shader shaderPDepth;

//    gleo::Shader shaderAvmRGB;
//    gleo::Shader shaderAvm422;
//    gleo::Shader shaderAvmNv21;
//    gleo::Shader shaderAvmOes;
//    gleo::Shader shaderAvmI420;
//    gleo::Shader *shaderAvm;

    ///给摄像头预先分配的最多12个纹理
    int cameraTxid[12];
    ///给贴图分配的3个纹理
    int mKbdTxid[3];

    int *pTxtrAvm[4];

    ModelAvmesh *mVs;
    TduiP1 *ui_p1;
    TduiP2 *ui_p2;
    TduiTune *ui_tune;
    Tdui *ui_virtual;
    TduiAuto *ui_auto;
    TduiMark *ui_mark;

    MdObject *mycar;

    MdoTireLine mdotline;
    MdoTuneRect mdotrect;

    MdoAllbs mdoabs;

    GleoCamera *camera;
    Gleu *uni;

    WhiteBalance wbagent;


    struct _global{
        //摄像头端输入的是单个组合纹理，还是摄像头分离的4个纹理
//        bool bUseStoredBmp;     // true ,打开保存的参考图像，没有摄像头输入时也可以看到模拟效果
//        bool bTextureAssemble;   // true = 1 2x2 texture picture;   false = 4 seperate texture picture
//        bool bUseOesTexture;    // true = 使用android 提供的 cam oes 纹理。
        int capwidth;       //摄像头采集的高度，输入的参考图片高度
        int capheight;      //摄像头采集的高度，输入的参考图片高度
//        TextureType extType;
        bool useInnerTexture;

    }global;

    struct _inTex{
        //bool isAssemble;
        int capW;
        int capH;
        Gleu::TextureType type;
        int txid[3];  //内部使用的参考图片是拼接到一起的2X2单幅图像， 所以只用了1组纹理id，无须三组。
        BmpLsimple *bmp; //用来保存内部参考图片，在没有视频输入的时候，也有效果显示
        unsigned char* i420Buf;

    }inTex;

    struct _exTex{
        int capW;
        int capH;
        bool isAssemble;
        Gleu::TextureType type;
        bool inputIsBuf;

        bool isOes;
//        bool currentIsOuterTex;
//        GLint outerTexId;
        //libpano内部产生一组纹理，如果是 2x2的画面，使用这一组纹理即可，否则就需要外部输入纹理ID
        // int txid[3];
        //分别对应4个摄像头的图像纹理， 目前的应用中，前端UVC给出的是 2X2 的画面，所以实际上这四组ID是相同的
        int txid0[3];
        int txid1[3];
        int txid2[3];
        int txid3[3];

        unsigned char* bb0[3];
        unsigned char* bb1[3];
        unsigned char* bb2[3];
        unsigned char* bb3[3];

        unsigned char *buf = NULL;//[1920*1080 + 1920*540];

    }exTex;


    ///这4个参数， 是GPU中绑定纹理的 宽度高度， 比如 在 单buf模式下， 每个摄像头数据 960*540， 那么绑定宽高 就是 1920*1080， 纹理1组
    /// 在分离buf 的模式下， 每个摄像头数据 960*540， 那么绑定宽高就是 960*540，但是纹理是 4组
    /// 这个参数 主要是 为了 GPU判断是否要从新分配内存，在分辨率不变的情况下， 使用 sub绑定函数， 节约时间
    int bindwidth = 320;
    int bindheight = 180;
    int pre_bindwidth = 0;
    int pre_bindheight = 0;

    //这两个数据，只在 forceCopyCamera true 时有效， 理论上， 外部传进来的 图像数据， 直接 绑定到 GPU 纹理即可
    //这里增加一个buf ，做一次拷贝，是测试时为了保证 在 各种硬件环境， 图像数据确保一致性
    int max_bufwidth = 1920;  //exTex 结构体内部用来保存 图像数据的 buf的宽度
    int max_bufheight = 1080; //exTex 结构体内部用来保存 图像数据的 buf的高度

};

#endif // RENDERERTDP_H
