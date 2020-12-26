
#include "leobase/common_leo.h"

#include "leobase/gleo20shader.h"
#include "leobase/imgconvert.h"
#include "leobase/imgbmp.h"
#include "leobase/gleoshader.h"
#include "leobase/gleo.h"
#include "leobase/gleocamera.h"
#include "leobase/gleu.h"

#include "rdrrpano.h"
#include "renderer/tdpanomesh.h"
#include "renderer/tdpanocmd.h"

//#include "tdkey.h"
#include "renderer/tduip1.h"
#include "renderer/tduip2.h"
#include "renderer/tduitune.h"
#include "renderer/tduiauto.h"
#include "renderer/tduimark.h"

#include "renderer/whitebalance.h"
#include "renderer/mdotireline.h"

#include <string>
#include <unistd.h>
#include <cmath>

#include "autocalib/calibwrap.h"
#include <opencv2/opencv.hpp>

//#define USE_INNER_BMP_TEST_EXTER_TEXTURE

using namespace std;

////此定义用来发布测试版本，开启之后， 代码屏蔽调试功能，不会进入调试界面，以便发布 用于APP调试的库
//#define VERSION_MAL_FUNCTION

////此处只能有一个 FUNC_* 定义， 此处用来临时区分不同客户需求的版本差异
#define FUNC_GENERAL
//#define FUNC_CLIENT_FH

#ifdef IMX6SOC
#define DATA_DIR        "/home/leoshih/tdpano.data"
#else
#ifdef ANDROID
#define DATA_DIR          "/storage/emulated/0/Android/data/com.leoshih.tdpano" //  "/sdcard/tdpano.data/" //  "/mnt/external_sd/tdpano.data/" // "/storage/sdcard0/tdpano.data/" //
#else
#define DATA_DIR        "/mnt/hgfs/leoshih/code-qt/tdpano.data" //"d:/leoshih/code-qt/tdpano.data"
#endif
#endif

#define FILE_MERGER		"param-mrg.data"
#define FILE_MOUNT		"param-mount.data"
#define FILE_VIEW		"param-vp.data"
//#define FILE_CAR		"mdl-focus-1.tdo" //"mdl-bus-1.tdo" //
#define FILE_CAR        "default.tdo"
//#define FILE_BRP        "lens-2603-r554.brp"
//#define FILE_BRP        "lens-2706-r562.brp"
#define FILE_BRP        "default.brp"

#define FILE_PIC0		"8296-1.bmp" //pic-1080p-default.jpg" //"pic-1080p-test1-r.bmp" //
#define FILE_LAB0		"pic-all.png"
// #define FILE_LAB1		"pic-lab2.bmp"
// #define FILE_LAB2		"pic-lab4.bmp"


//#define ORG_VIEW_MODE    0  //原始画面，无镜像无旋转
//#define ORG_VIEW_MODE    4    //后视镜像
//#define ORG_VIEW_MODE    8  //后视镜像，左右旋转

RendererTdp::RendererTdp(){
//    ctrl.enableConfig = true;

//    ctrl.enButton = true;
//    ctrl.enAllbs = false;
//    ctrl.enAvm2d = true;

//    ctrl.enDrawCar = true;
//    ctrl.enDrawAvm = true;
//    ctrl.enDrawOrg = true;

#ifdef FUNC_GENERAL
#define ORG_VIEW_MODE    12    //后视镜像
//    ctrl.slide2dOn = false;//false;
//    ctrl.slideOrgOn = false;//true;
//    ctrl.slide3dOn = true;//true;
//    ctrl.slideMirrorOn = false;
//    ctrl.en2DPick = true;

//    ctrl.lineTrailOn = true;
//    ctrl.lineRearOn = false;
//    ctrl.lineRadarOn = false;
#endif
#ifdef FUNC_CLIENT_FH
#define ORG_VIEW_MODE    8  //后视镜像，左右旋转
   ctrl.slide2dOn = false;//false;
//   ctrl.slide2dOnY = false;//true;
   ctrl.slide3dOn = false;//true;
   ctrl.slideOrgOn = false;//true;
   ctrl.slideMirrorOn = false;
   ctrl.en2DPick = false;

    ctrl.lineTrailOn = false;
    ctrl.lineRearOn = false;
    ctrl.lineRadarOn = false;
#endif

    ctrl.innerIsBmp = true;

    global.capwidth = 640; ///前端传感器采集的图像宽度和高度
    global.capheight = 360;///贴图的时候使用纹理， 因此对长宽不敏感了， 但是 预处理仍然需要知道长宽
    global.useInnerTexture = false;

    opera.isDrawing = false;
    opera.isTexUpdating = false;
    opera.isAutoCalib = false;
    opera.isCalibImageOk = false;
    opera.isSaveImage = false;

    inTex.type = Gleu::TextureType::TextureType_I420;
    inTex.capW = 1280;
    inTex.capH = 720;
    inTex.txid[0] = 0;
    inTex.txid[1] = 0;
    inTex.txid[2] = 0;
    inTex.i420Buf = NULL;

    exTex.type = Gleu::TextureType::TextureType_I420;
    exTex.isAssemble = true;
    exTex.isOes = false;
    exTex.inputIsBuf = false;
    exTex.capW = 1280;
    exTex.capH = 720;


    // exTex.txid[0] = 0;
    // exTex.txid[1] = 0;
    // exTex.txid[2] = 0;

    WndRet = NULL; // UI_** 返回的有效值从1开始
    VpRet = -1; // viewPortPick() 函数返回的有效值从 0 开始

    pressResponding = false;

    mVs = new ModelAvmesh;
    mVs->defaultParam();

    camera = new GleoCamera;
    ui_p1 = new TduiP1;
    ui_p2 = new TduiP2;
    ui_tune = new TduiTune;
    ui_auto = new TduiAuto;
    ui_mark = new TduiMark;

    mycar = new MdObject;
    uni = new Gleu;

//    ui_p1->disableSettingKey(true);

    inTex.i420Buf = NULL;

    NewPaintRequest = 0;
    NewBuffers = 0;
    disMode = 0; //默认2分频
    disCam = 1;  //默认显示后视
    disAngle = 0;
    scrn.isHorizontal = true;

    //初始化vuport 的设置
    //初始化分屏显示的方框线VB
    int _color = 0xffa0a0a0; //边框颜色
    vuport_pad = Vector4(8,8,-16,-16); //保留的一个细边
    for(int j=0; j<DIS_GRP; j++){
        for(int i=0; i< DIS_ITEM; i++){
            painter[j][i].on = false;
            painter[j][i].item = i;
            painter[j][i].vuport = Vector4(0,0,0,0);
            //初始化边框vb
            painter[j][i].frame.initial(VertexBlock::VertexType::PNUC, 4);
            //指定边框的颜色
            painter[j][i].frame.seek(0);
            painter[j][i].frame.clrNext() = _color;
            painter[j][i].frame.clrNext() = _color;
            painter[j][i].frame.clrNext() = _color;
            painter[j][i].frame.clrNext() = _color;
        }
    }

    painter[1][0].item = 4;


    //初始化分屏显示的方框线IB
    ibrect.mmalloc(8);
    ibrect.sdata[0] = 0;
    ibrect.sdata[1] = 1;
    ibrect.sdata[2] = 1;
    ibrect.sdata[3] = 2;
    ibrect.sdata[4] = 2;
    ibrect.sdata[5] = 3;
    ibrect.sdata[6] = 3;
    ibrect.sdata[7] = 0;



    uni->avm.uvAdpterValue[0] = Vector4(1.0, 0.0, 1.0, 0.0);
    uni->avm.uvAdpterValue[1] = Vector4(1.0, 0.0, 1.0, 0.0);
    uni->avm.uvAdpterValue[2] = Vector4(1.0, 0.0, 1.0, 0.0);
    uni->avm.uvAdpterValue[3] = Vector4(1.0, 0.0, 1.0, 0.0);

    opera.tmpCmd = 0;

    strFileMerger.clear();
    strFileMerger.append(FILE_MERGER);

    strFileMount.clear();
    strFileMount.append(FILE_MOUNT);

    strFileView.clear();
    strFileView.append(FILE_VIEW);

    strFileBrp.clear();
    strFileBrp.append(FILE_BRP);

    strFileCar.clear();
    strFileCar.append(FILE_CAR);

    strStoragePath.clear();
    strStoragePath.append(DATA_DIR);

    exTex.buf = new unsigned char[max_bufwidth * max_bufwidth * 3 / 2];
    exTex.bb0[0] = exTex.buf;
    exTex.bb0[1] = exTex.bb0[0] + max_bufwidth * max_bufheight;
    exTex.bb0[2] = exTex.bb0[1] + max_bufwidth * max_bufheight/4;

    exTex.bb1[0] = exTex.buf;
    exTex.bb1[1] = exTex.bb1[0] + max_bufwidth * max_bufheight;
    exTex.bb1[2] = exTex.bb1[1] + max_bufwidth * max_bufheight/4;

    exTex.bb2[0] = exTex.buf;
    exTex.bb2[1] = exTex.bb2[0] + max_bufwidth * max_bufheight;
    exTex.bb2[2] = exTex.bb2[1] + max_bufwidth * max_bufheight/4;

    exTex.bb3[0] = exTex.buf;
    exTex.bb3[1] = exTex.bb3[0] + max_bufwidth * max_bufheight;
    exTex.bb3[2] = exTex.bb3[1] + max_bufwidth * max_bufheight/4;
    return;
}

RendererTdp::~RendererTdp(){
    if(mVs != NULL) delete mVs;
    if(camera != NULL) delete camera;

    if(ui_p1 != NULL) delete ui_p1;
    if(ui_p2 != NULL) delete ui_p2;
    if(ui_tune != NULL) delete ui_tune;
    if(ui_auto != NULL) delete ui_auto;
    if(ui_mark != NULL) delete ui_mark;

    if(mycar != NULL) delete mycar;
    if(uni != NULL) delete uni;

//    delete inTex.bmp;

    if(inTex.i420Buf != NULL){
        delete inTex.i420Buf;
    }

    delete exTex.buf;
}

void RendererTdp::modiDirectory(const char* dir)
{
    if(!dir){
        return;
    }
    strStoragePath.clear();
    strStoragePath.append(dir);
    return;
}

void RendererTdp::modiModelFile(const char* file)
{
    if(!file){
        return;
    }
    strFileCar.clear();
    strFileCar.append(file);
    return;
}

void RendererTdp::modiBrpFile(const char* file)
{
    if(!file){
        return;
    }
    strFileBrp.clear();
    strFileBrp.append(file);
    return;
}

bool RendererTdp::loadModelFile(const char *file)
{
    ifn = strStoragePath;
    if(file != NULL){
        ifn.append("/").append(file);
    }
    else{
        ifn.append("/").append(strFileCar);
    }

    if( mycar->load(ifn.c_str()) ){
        return false;
    }
    else{
        return true;
    }
}

bool RendererTdp::loadBrpFile(const char *file)
{
    ifn = strStoragePath;
    if(file != NULL){
        ifn.append("/").append(file);
    }
    else{
        ifn.append("/").append(strFileBrp);
    }

    if( !mVs->loadBrp(ifn.c_str()) ){
        //error = "Brp Open Failed.\n";
        return false;
    }
    else{
        return true;
    }
}

bool RendererTdp::loadMergerFile(const char *file)
{
    ifn = strStoragePath;
    if(file != NULL){
        ifn.append("/").append(file);
    }
    else{
        ifn.append("/").append(strFileMerger);
    }

    if( !mVs->loadMergerData(ifn.c_str()) ){
//        error = "Merger File open failed.\n";
        return false;
    }
    else{
        return true;
    }
}

bool RendererTdp::loadMountFile(const char *file)
{
    ifn = strStoragePath;
    if(file != NULL){
        ifn.append("/").append(file);
    }
    else{
        ifn.append("/").append(strFileMount);
    }

    if( !mVs->loadMountData(ifn.c_str()) ){
//        error = "Merger File open failed.\n";
        return false;
    }
    else{
        return true;
    }
}


bool RendererTdp::reloadVs()
{
    loadMergerFile();

    loadMountFile();

    if(!mVs->updateAll()){
        LOGE("mVs updateAll error.\n");

    ////调整模型尺寸， 确保一个模型适配所有的车体大小和安装Blank大小
        Vector3 min, max;
        float k0, k1;

        if (mycar->measure(min, max)){
            k0 = mVs->meshPara.W_BLANK / (max.x - min.x);
            k1 = mVs->meshPara.H_BLANK / (max.y - min.y);
            //std::cout << "#### xscale= " << k0 << " yscale= " << k1 << std::endl;
            mycar->scale({ k0, k1, k0 });
            //comcar->infoSize();
           }
        ////调整模型尺寸完成
            return false;
        }

    return true;
}

bool RendererTdp::initial(std::string& error)
{
    if(!mVs->updateAll()){
        error = "mVs updateAll error.";
        return false;
    }

    //色彩均衡模块
//    wbagent.setSeperateCap(640, 360);
//    wbagent.setComposeCap(1280, 720, 640, 360);
    initialwb(global.capwidth, global.capheight);

    mVs->vtxFront->info(true);

    // CAR
    mycar->info(true);

    //mycar->resize

    ////调整模型尺寸， 确保一个模型适配所有的车体大小和安装Blank大小
    Vector3 min, max;
    float k0, k1;

    if (mycar->measure(min, max)){
        k0 = mVs->meshPara.W_BLANK / (max.x - min.x);
        k1 = mVs->meshPara.H_BLANK / (max.y - min.y);
        //std::cout << "#### xscale= " << k0 << " yscale= " << k1 << std::endl;
        mycar->scale({ k0, k1, k0 });
        //comcar->infoSize();
       }
    ////调整模型尺寸完成

    // CAMERA
    camera->defaultVp();
    ifn = strStoragePath;
    if( !camera->loadVp(ifn.append("/").append(strFileView).c_str()) ){
        error = "Vp load failed.\n";
        return false;
    }


    /// 初始化轨迹线
    mdotline.init(40, 0.1);
    mdotline.create(0.0, true);

    /// 初始化调试框
    mdotrect.init();
    mdotrect.create(mVs->getBlankWidth(), mVs->getBlankHeight());
    // 加载静态纹理

    ///底部白板初始化
    vbottom.initial(VertexBlock::VertexType::PNUC, 4);
    ibottom.mmalloc(6);
    ibottom.sdata[0] = 0;
    ibottom.sdata[1] = 1;
    ibottom.sdata[2] = 3;
    ibottom.sdata[3] = 0;
    ibottom.sdata[4] = 3;
    ibottom.sdata[5] = 2;

    float thw = mVs->getBlankWidth()/2.0;
    float thh = mVs->getBlankHeight()/2.0;

    vbottom.posAt(0) = Vector3(-thw, -thh, 0.0);
    vbottom.posAt(1) = Vector3(thw, -thh, 0.0);
    vbottom.posAt(2) = Vector3(-thw, thh, 0.0);
    vbottom.posAt(3) = Vector3(thw, thh, 0.0);

    vbottom.clrAt(0) = 0xffaaaaaa;
    vbottom.clrAt(1) = 0xffaaaaaa;
    vbottom.clrAt(2) = 0xffaaaaaa;
    vbottom.clrAt(3) = 0xffaaaaaa;   


    mdoabs.initial();
    mdoabs.create(mVs->meshPara.W_BLANK, mVs->meshPara.H_BLANK);

    return true;
}



void RendererTdp::initGL(){

#ifdef QT
    initializeOpenGLFunctions();
#endif
    gleo::initGL();

    //initial();

    LOGI("initalGL begin.\n");

    // KBD
    ui_p1->initial();
    ui_p2->initial();
    ui_tune->initial();
    ui_auto->initial();
    ui_virtual = ui_p1;

    ui_p1->enOrgBtn(ctrl.enButton);
    ui_p1->en3dBtn(ctrl.enButton);
    ui_p1->enMirrorBtn(false);
    ui_p1->enSettingBtn(ctrl.enButton);

    for(int i=0;i<12;i++){
        cameraTxid[i] = gleo::createTexture2D();
    }

    // 绑定纹理
    inTex.txid[0] = gleo::createTexture2D();
    inTex.txid[1] = gleo::createTexture2D();
    inTex.txid[2] = gleo::createTexture2D();

    exTex.txid0[0] = cameraTxid[0];//gleo::createTexture2D();
    exTex.txid0[1] = cameraTxid[1];//gleo::createTexture2D();
    exTex.txid0[2] = cameraTxid[2];//gleo::createTexture2D();

    exTex.txid1[0] = cameraTxid[3];//gleo::createTexture2D();
    exTex.txid1[1] = cameraTxid[4];//gleo::createTexture2D();
    exTex.txid1[2] = cameraTxid[5];//gleo::createTexture2D();

    exTex.txid2[0] = cameraTxid[6];//gleo::createTexture2D();
    exTex.txid2[1] = cameraTxid[7];//gleo::createTexture2D();
    exTex.txid2[2] = cameraTxid[8];//gleo::createTexture2D();

    exTex.txid3[0] = cameraTxid[9];//gleo::createTexture2D();
    exTex.txid3[1] = cameraTxid[10];//gleo::createTexture2D();
    exTex.txid3[2] = cameraTxid[11];//gleo::createTexture2D();


    mKbdTxid[0] = gleo::createTexture2D();
    mKbdTxid[1] = gleo::createTexture2D();
    mKbdTxid[2] = gleo::createTexture2D();

    mVs->createOrgVbIb(0);

    std::string strTmpFile;

    strTmpFile.clear();
    strTmpFile.append(strStoragePath);
    strTmpFile.append("/");
    strTmpFile.append(FILE_LAB0);

    cv::Mat lab0 = cv::imread(strTmpFile, -1);  
    //lab0.
	for (int i = 0; i < lab0.rows; ++i) {
		for (int j = 0; j < lab0.cols; ++j) {
			Vec4b& pix = lab0.at<Vec4b>(i, j); //指针或引用
			std::swap(pix[0], pix[2]);
		}
	}

//    LOGI("%s read, w=%d, h=%d ,channel=%d.\n", lab0.cols, lab0.rows, lab0.channels());

    if(lab0.channels() == 4){
        gleo::texBindRgba(mKbdTxid[0], lab0.data, lab0.cols, lab0.rows);
    }else if(lab0.channels() == 3){
        gleo::texBindRgb(mKbdTxid[0],  lab0.data, lab0.cols, lab0.rows);
        LOGE("%s is 3channel, no alpha, UI maybe has unexpected effect.", strTmpFile.c_str());
        //gleo::texBindRgbFromBmp(mKbdTxid[0], strTmpFile.c_str());
    }


    // KBD set TEXTURE ID
    ui_p1->setTextureId(mKbdTxid[0]);
    ui_p2->setTextureId(mKbdTxid[0]);
    ui_tune->setTextureId(mKbdTxid[0]);
    ui_auto->setTextureId(mKbdTxid[0]);
    ui_mark->setTextureId(mKbdTxid[0]);

    // VBO,IBO
    gleo::bindVb(mVs->vtxFront);
    gleo::bindVb(mVs->vtxBack);
    gleo::bindVb(mVs->vtxLeft);
    gleo::bindVb(mVs->vtxRight);

    gleo::bindIb(mVs->idxFront);
    gleo::bindIb(mVs->idxBack);
    gleo::bindIb(mVs->idxLeft);
    gleo::bindIb(mVs->idxRight);

// 	glGenFramebuffers(1, &fboid);
// 	glBindFramebuffer(GL_FRAMEBUFFER, fboid);
//
// 	glGenRenderbuffers(1, &rborgba);
// 	glBindRenderbuffer(GL_RENDERBUFFER, rborgba);
// 	glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA, width(), height());
// 	glBindRenderbuffer(GL_RENDERBUFFER, 0);
//
// 	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_RENDERBUFFER, rborgba);

// 	glGenRenderbuffers(1, &rbodepth);
// 	glBindRenderbuffer(GL_RENDERBUFFER, rbodepth);
// 	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width(), height());
// 	glBindRenderbuffer(GL_RENDERBUFFER, 0);
//
// 	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,  GL_RENDERBUFFER, rbodepth);
//    string vshaderstr,fshaderstr;

    uni->user.color0 = Vector4(0.8, 0.8, 0.4, 1.0);
    uni->avm.uvAdpter = Vector4(1.0, 0.0, 1.0, 0.0 );
    uni->avm.cambalance.blankAndCamera = Vector4(1.8, 4.8, 0.0, 0.0);
    uni->avm.cambalance.coff0 = Vector4(1.0,1.0,1.0,1.0);
    uni->avm.cambalance.coff1 = Vector4(1.0,1.0,1.0,1.0);

    //uni->lit0.pos = Vector3(8, 8, 1);
    uni->lit0.pos = Vector3(0,4,20);
    uni->avm.yuvInfo = Vector4(inTex.capW, inTex.capH, 0, 0);


    uni->initShaderUni();

    checkMdoTexture(mycar);

//    LOGI("intialGL OK.\n");
    return;
}


void RendererTdp::setTextureType(int type)
{
    switch((Gleu::TextureType)type){
    case Gleu::TextureType::TextureType_I420:
        exTex.type = Gleu::TextureType::TextureType_I420;
        break;
    case Gleu::TextureType::TextureType_NV21:
        exTex.type = Gleu::TextureType::TextureType_NV21;
        break;
    case Gleu::TextureType::TextureType_YUV422:
        exTex.type = Gleu::TextureType::TextureType_YUV422;
        break;
#ifdef ANDROID
    case TextureType_OES:
        exTex.type = TextureType_OES;
        break;
#endif
    default:
        break;
    }

    return;
}

void RendererTdp::setTextureAssemble(bool b)
{
    exTex.isAssemble = b;
    return;
}

int RendererTdp::getTextureId(int yuv)
{
    if(yuv >= 0 && yuv <3){
        return exTex.txid0[yuv%3];
    }
    else if(yuv <6){
        return exTex.txid1[yuv%3];
    }
    else if(yuv < 9){
        return exTex.txid2[yuv%3];
    }
    else if(yuv < 12){
        return exTex.txid3[yuv%3];
    }
    else{
        return 0;
    }
}

void RendererTdp::setTextureId(int tid0, int tid1, int tid2)
{

    exTex.txid0[0] = tid0;
    exTex.txid0[1] = tid1;
    exTex.txid0[2] = tid2;

    // exTex.txid1[0] = tid0;
    // exTex.txid1[1] = tid1;
    // exTex.txid1[2] = tid2;

    // exTex.txid2[0] = tid0;
    // exTex.txid2[1] = tid1;
    // exTex.txid2[2] = tid2;

    // exTex.txid3[0] = tid0;
    // exTex.txid3[1] = tid1;
    // exTex.txid3[2] = tid2;

    return;

//    if(outerTexIsOes) {
////        global.bUseOesTexture = true;
//#ifdef ANDROID
//        shaderCamAvm = &shaderP2UCAvmOes;
//#else
//        LOGE("GL_TEXTURE_EXTERNAL_OES not supported.\n");
//        shaderAvm = &shaderAvmRGB;
//#endif

//    }
//    else{
//        global.bUseOesTexture = false;
//        shaderAvm = &shaderAvmRGB;
//    }

//    exTex.hasOuterTex = true;
//    exTex.isOes = outerTexIsOes;
//    exTex.outerTexId = outerTexId;
//    exTex.currentIsOuterTex = true;

    return;
}


void RendererTdp::setTextureSepId(int camid, int tid0, int tid1, int tid2)
{
    if(camid < 0 || camid > 3){
        LOGE("illegal camid\n");
        return;
    }
    switch(camid){
    case 0:
        exTex.txid0[0] = tid0;
        exTex.txid0[1] = tid1;
        exTex.txid0[2] = tid2;
        break;
    case 1:
        exTex.txid1[0] = tid0;
        exTex.txid1[1] = tid1;
        exTex.txid1[2] = tid2;
        break;
    case 2:
        exTex.txid2[0] = tid0;
        exTex.txid2[1] = tid1;
        exTex.txid2[2] = tid2;
        break;
    case 3:
        exTex.txid3[0] = tid0;
        exTex.txid3[1] = tid1;
        exTex.txid3[2] = tid2;
        break;
    default:break;
    }
    return;
}


void RendererTdp::setTextureIsBuf(bool b)
{
    exTex.inputIsBuf = b;
    return;
}



void RendererTdp::switchTex()
{
    static bool b=true;
    b = !b;
    switchInnerDemo(b);
    return;
}

//predicated
void RendererTdp::switchInnerDemo(bool b){
    if(b){
        switchIntex(ctrl.innerIsBmp);
    }
    else{
        switchExtex(exTex.isAssemble);
    }

    return;
}

void RendererTdp::switchIntex(bool bUsePic)
{
    uni->avm.uvAdpterValue[0] = Vector4(0.5, 0.0, 0.5, 0.0);
    uni->avm.uvAdpterValue[1] = Vector4(0.5, 0.5, 0.5, 0.0);
    uni->avm.uvAdpterValue[2] = Vector4(0.5, 0.0, 0.5, 0.5);
    uni->avm.uvAdpterValue[3] = Vector4(0.5, 0.5, 0.5, 0.5);

    uni->choiceAvmShader((int)inTex.type);

    pTxtrAvm[0] = inTex.txid;
    pTxtrAvm[1] = inTex.txid;
    pTxtrAvm[2] = inTex.txid;
    pTxtrAvm[3] = inTex.txid;

    ctrl.innerIsBmp = bUsePic;

//    if(ctrl.innerIsBmp){
    innerTexture();
//    }
//    else{
//        innerTexDark();
//    }
    global.capwidth = inTex.capW;
    global.capheight = inTex.capH;
    global.useInnerTexture = true;

    return;
}

void RendererTdp::switchExtex(bool ext_assb2x2mode) {

    exTex.isAssemble = ext_assb2x2mode;
    // 外部纹理 是assemble 还是seperate
    if(exTex.isAssemble){
        //设置纹理的坐标矫正为 2x2 拼图
        uni->avm.uvAdpterValue[0] = Vector4(0.5, 0.0, 0.5, 0.0);
        uni->avm.uvAdpterValue[1] = Vector4(0.5, 0.5, 0.5, 0.0);
        uni->avm.uvAdpterValue[2] = Vector4(0.5, 0.0, 0.5, 0.5);
        uni->avm.uvAdpterValue[3] = Vector4(0.5, 0.5, 0.5, 0.5);

        pTxtrAvm[0] = exTex.txid0;
        pTxtrAvm[1] = exTex.txid0;
        pTxtrAvm[2] = exTex.txid0;
        pTxtrAvm[3] = exTex.txid0;

    }
    else{
        uni->avm.uvAdpterValue[0] = Vector4(1.0, 0.0, 1.0, 0.0);
        uni->avm.uvAdpterValue[1] = Vector4(1.0, 0.0, 1.0, 0.0);
        uni->avm.uvAdpterValue[2] = Vector4(1.0, 0.0, 1.0, 0.0);
        uni->avm.uvAdpterValue[3] = Vector4(1.0, 0.0, 1.0, 0.0);

        pTxtrAvm[0] = exTex.txid0;
        pTxtrAvm[1] = exTex.txid1;
        pTxtrAvm[2] = exTex.txid2;
        pTxtrAvm[3] = exTex.txid3;
    }

    uni->choiceAvmShader((int)exTex.type);


//        }
#ifdef USE_INNER_BMP_TEST_EXTER_TEXTURE
    pTxtrAvm[0] = inTex.txid;
    pTxtrAvm[1] = inTex.txid;
    pTxtrAvm[2] = inTex.txid;
    pTxtrAvm[3] = inTex.txid;
#endif
    global.capwidth = exTex.capW;
    global.capheight = exTex.capH;
    global.useInnerTexture = false;
    return;
}



///用一张图片来生成内部纹理，当外部没有输入时，仍然可以显示画面，
/// 外部没有视频时可以自行 用图像刷新，这个机制放外部好（depracated）
void RendererTdp::innerTexture()
{
    // 初始化内部测试纹理
    std::string strTmpFile;

    strTmpFile.clear();
    strTmpFile.append(strStoragePath);
    strTmpFile.append("/");
    strTmpFile.append(FILE_PIC0);  // 内部纹理图片文件路径

    cv::Mat pic0 = cv::imread(strTmpFile, 1);

    ///打开图像不正常， 生成一张黑背景
    if(pic0.rows <= 2 || pic0.cols <= 2){

        inTex.capW = 320;
        inTex.capH = 180;
        inTex.i420Buf = new unsigned char[inTex.capW * inTex.capH * 3 / 2];
        memset(inTex.i420Buf, 64, inTex.capW*inTex.capH);
        memset(inTex.i420Buf + inTex.capW*inTex.capH, 128, inTex.capW*inTex.capH / 2);

        gleo::texBindLumi(inTex.txid[0], inTex.i420Buf, inTex.capW, inTex.capH);
        gleo::texBindLumi(inTex.txid[1], inTex.i420Buf+ inTex.capW*inTex.capH, inTex.capW/2, inTex.capH/2);
        gleo::texBindLumi(inTex.txid[2], inTex.i420Buf+ inTex.capW*inTex.capH + inTex.capW*inTex.capH/4, inTex.capW/2, inTex.capH/2);

        delete [] inTex.i420Buf;
        inTex.i420Buf = NULL;
    }
    ///正常打开，使用图像背景
    else{
        //lab0.
        for (int i = 0; i < pic0.rows; ++i) {
            for (int j = 0; j < pic0.cols; ++j) {
                Vec3b& pix = pic0.at<Vec3b>(i, j); //指针或引用
                std::swap(pix[0], pix[2]);
            }
        }

        inTex.capW = pic0.cols;
        inTex.capH = pic0.rows;
        inTex.type = Gleu::TextureType::TextureType_I420;

        unsigned char *ttp = new unsigned char[inTex.capW * inTex.capH * 2];
        imRgbtoYuv422(pic0.data, ttp, pic0.cols, pic0.rows, true);

        inTex.i420Buf = new unsigned char[inTex.capW * inTex.capH * 3 / 2];
        imYuv422toI420(ttp, inTex.i420Buf, pic0.cols, pic0.rows);

        delete [] ttp;

    //    inTex.bmp = new BmpLsimple;
    //    inTex.bmp->load(strTmpFile.c_str());
    //    inTex.bmp->exchangeRB();
    //    inTex.bmp->reverse();
    //    inTex.capW = inTex.bmp->width();
    //    inTex.capH = inTex.bmp->height();

        if(inTex.type == Gleu::TextureType::TextureType_Rgb){
            gleo::texBindRgb(inTex.txid[0], inTex.bmp->bits(), inTex.capW, inTex.capH);
        }
        else if(inTex.type == Gleu::TextureType::TextureType_YUV422){
            imRgbtoYuv422(inTex.bmp->bits(), inTex.bmp->bits(), inTex.capW, inTex.capH, true);
            gleo::texBindUYVY(inTex.txid[0], inTex.bmp->bits(), inTex.capW, inTex.capH);
        }
        else if(inTex.type == Gleu::TextureType::TextureType_I420){
            gleo::texBindLumi(inTex.txid[0], inTex.i420Buf, inTex.capW, inTex.capH);
            gleo::texBindLumi(inTex.txid[1], inTex.i420Buf+ inTex.capW*inTex.capH, inTex.capW/2, inTex.capH/2);
            gleo::texBindLumi(inTex.txid[2], inTex.i420Buf+ inTex.capW*inTex.capH + inTex.capW*inTex.capH/4, inTex.capW/2, inTex.capH/2);
    //        wbagent.calcI420Level(inTex.i420Buf, inTex.i420Buf+ inTex.capW*inTex.capH, inTex.i420Buf+ inTex.capW*inTex.capH + inTex.capW*inTex.capH/4);
    //        wbagent.dbg();
            //updatewb(inTex.i420Buf, inTex.capW, inTex.capH);
    //        delete inTex.bmp;
            inTex.bmp = NULL;
            delete [] inTex.i420Buf;
            inTex.i420Buf = NULL;

        }
    }


    return;
}

void RendererTdp::update(int width, int height)
{
    if(!wbagent.isTableAvail()){
        initialwb(width, height);
        global.capwidth = width;
        global.capheight = height;
    }
    else if(width != wbagent.CAP_WIDTH || height != wbagent.CAP_HEIGHT){
        initialwb(width, height);
        global.capwidth = width;
        global.capheight = height;       
    }
    return;
}

void RendererTdp::update(unsigned char* buf0, unsigned char* buf1, unsigned char* buf2 , unsigned char* buf3, int width, int height,const Vector3& ex_angle) //更新 buf
{
//    static int time = 0;
//    static int cur_w, cur_h;
    static clock_t t1, t2;

    int offu = width*height;
    int offv = width*height + width*height/4;
    int offyuv = width*height + width*height/2;

    if(width <= 2 || height <= 2){
        return;
    }

    //LOGE("update,%d,%d,%d, = %d,%d ", exTex.txid[0],exTex.txid[1],exTex.txid[2], width, height);
    t1 = clock();

    if(exTex.isAssemble){
        switchExtex(false);
    }
    ///如果打开了数据拷贝， 则多执行一次 camera数据拷贝， 这个操作最好不执行
    ///可以保证数据 一致性，但是 消耗性能， 最好由外部摄像头驱动来保证数据一致性
    if(ctrl.forceCopyCamera){
    ///如果输入图像尺寸已经超过预设的最大尺寸， 则重新分配纹理内存
        if(max_bufwidth < width*2 || max_bufheight < height*2){
            delete exTex.buf;
            exTex.buf = new unsigned char[4*width*height*3/2];
            if(exTex.buf == NULL){
                LOGE("jni_tdp alloc error.");
                return;
            }
            exTex.bb0[0] = exTex.buf;
            exTex.bb0[1] = exTex.bb0[0] + offu;
            exTex.bb0[2] = exTex.bb0[0] + offv;

            exTex.bb1[0] = exTex.buf + offyuv;
            exTex.bb1[1] = exTex.bb1[0] + offu;
            exTex.bb1[2] = exTex.bb1[0] + offv;

            exTex.bb2[0] = exTex.buf + 2*offyuv;
            exTex.bb2[1] = exTex.bb2[0] + offu;
            exTex.bb2[2] = exTex.bb2[0] + offv;

            exTex.bb3[0] = exTex.buf + 3*offyuv;
            exTex.bb3[1] = exTex.bb3[0] + offu;
            exTex.bb3[2] = exTex.bb3[0] + offv;

            max_bufwidth = width*2;
            max_bufheight = height*2;
        }
        LOGE("memcpy %d,%d", width, height);
        memcpy(exTex.bb0[0], buf0,  width*height*3/2);
        memcpy(exTex.bb1[0], buf1,  width*height*3/2);
        memcpy(exTex.bb2[0], buf2,  width*height*3/2);
        memcpy(exTex.bb3[0], buf3,  width*height*3/2);

        bindwidth = width;
        bindheight = height;
    }
    else{
        exTex.bb0[0]=buf0;
        exTex.bb0[1]=buf0 + offu;
        exTex.bb0[2]=buf0 + offv;

        exTex.bb1[0]=buf1;
        exTex.bb1[1]=buf1 + offu;
        exTex.bb1[2]=buf1 + offv;

        exTex.bb2[0]=buf2;
        exTex.bb2[1]=buf2 + offu;
        exTex.bb2[2]=buf2 + offv;

        exTex.bb3[0]=buf3;
        exTex.bb3[1]=buf3 + offu;
        exTex.bb3[2]=buf3 + offv;

        bindwidth = width;
        bindheight = height;
    }

    //updateExtra();
    return;
}


void RendererTdp::update(unsigned char* buf, int width, int height, const Vector3& ex_angle )
{
    update(buf, buf + width*height, buf + width*height + width*height/4, width, height, ex_angle);
    return;
}

void RendererTdp::update(unsigned char * bufy, unsigned char * bufu, unsigned char * bufv, int width, int height, const Vector3& ex_angle)
{
//    static int time = 0;
//    static int cur_w, cur_h;
    static clock_t t1, t2;

    if(width <= 2 || height <= 2){
        return;
    }

    //LOGE("update,%d,%d,%d, = %d,%d ", exTex.txid[0],exTex.txid[1],exTex.txid[2], width, height);
    t1 = clock();

    if(!exTex.isAssemble){
        exTex.isAssemble = true;
        switchExtex(true);
    }

    ///如果打开了数据拷贝， 则多执行一次 camera数据拷贝， 这个操作最好不执行
    ///可以保证数据 一致性，但是 消耗性能， 最好由外部摄像头驱动来保证数据一致性
    if(ctrl.forceCopyCamera){
    ///如果输入图像尺寸已经超过预设的最大尺寸， 则重新分配纹理内存
        if(max_bufwidth < width || max_bufheight < height){
            delete exTex.buf;
            exTex.buf = new unsigned char[width*height*3/2];
            if(exTex.buf == NULL){
                LOGE("jni_tdp alloc error.");
                return;
            }
            exTex.bb0[0] = exTex.buf;
            exTex.bb0[1] = exTex.bb0[0] + width*height;
            exTex.bb0[2] = exTex.bb0[1] + width*height/4;
            max_bufwidth = width;
            max_bufheight = height;
        }
        LOGE("memcpy %d,%d", width, height);
        memcpy(exTex.bb0[0], bufy, width*height);
        memcpy(exTex.bb0[1], bufu,  width*height/4);
        memcpy(exTex.bb0[2], bufv,  width*height/4);

    }
    else{
        exTex.bb0[0] = bufy;
        exTex.bb0[1] = bufu;
        exTex.bb0[2] = bufv;

        bindwidth = width;
        bindheight = height;
    }

    updateExtra();

    return;
}

void RendererTdp::updateExtra()
{
    int width = bindwidth;
    int height = bindheight;

    ///此次数据用于 绘图，执行色彩和亮度均衡操作
    if(opera.tmpCmd == 0){
       if(wbagent.isTableAvail())
        {
            if(width == wbagent.CAP_WIDTH && height == wbagent.CAP_HEIGHT){
                //int offset = width*height;
///FH 版本，关闭均衡                
#ifndef 	FUNC_CLIENT_FH			
            wbagent.calcI420Level(exTex.bb0[0],  exTex.bb0[1] , exTex.bb0[2] );
#else              
			wbagent.setDefault();
#endif
            }
            else{
    //            LOGE("wbagent parameter confilict\n");
            }
        }
    }
    ///此次数据 用来保存图像
    else if(opera.tmpCmd == 3){
        opera.tmpCmd = 0; 
        opera.isAutoCalib = true; 

        cv::Mat mat(height, width, CV_8UC3, cv::Scalar(0,0,0));

        imI420toRgb(exTex.bb0[0],  exTex.bb0[1] , exTex.bb0[2], mat.data, width, height);
        std::string ofn = strStoragePath + "/temp.jpg";
        cv::imwrite(ofn, mat);
    }
    ///此次数据用来 自动标定
    else if(opera.tmpCmd == 1){
        opera.tmpCmd = 0;      

        cv::Mat mat(height, width, CV_8UC3, cv::Scalar(0,0,0));

        imI420toRgb(exTex.bb0[0],  exTex.bb0[1] , exTex.bb0[2], mat.data, width, height);
        std::string ofn = strStoragePath + "/5.jpg";
        cv::imwrite(ofn, mat);

        CalibWrap wrap;
        wrap.setDirectory(strStoragePath);
        wrap.setBrpFile(strFileBrp);
        wrap.setCfgFile("c4m4.cfg");
        //wrap.test();
        wrap.do1pic("5.jpg");

        ifn = strStoragePath;
        mVs->loadAutoMergerData(ifn.append("/").append("c4m4.cfg").c_str());
        mVs->calcAutoMark();
        mVs->copyMdlMark();
        mVs->createUv();
    }
    ///使用预先保存的图片进行自动标定，而不是抓图
    else if(opera.tmpCmd == 2){
        opera.tmpCmd = 0;      

        CalibWrap wrap;
        wrap.setDirectory(strStoragePath);
        wrap.setBrpFile(strFileBrp);
        wrap.setCfgFile("c4m4.cfg");
        //wrap.test();
        wrap.do1pic("4.jpg");

        ifn = strStoragePath;
        mVs->loadAutoMergerData(ifn.append("/").append("c4m4.cfg").c_str());
        mVs->loadAutoMergerData(ifn.append("/").append("c4m4.cfg").c_str());
        mVs->calcAutoMark();
        mVs->copyMdlMark();
        mVs->createUv();
    }
    else{
    }

    return;
}

void RendererTdp::initialwb(int bufwidth, int bufheight)
{
    wbagent.setComposeCap(bufwidth, bufheight, bufwidth/2, bufheight/2);
    ARR4V2 quali;
    for(int camera = 0;camera < 4; camera++){
        mVs->getWbRegion(camera,0,quali);
        wbagent.setRegion(camera, 0, quali);
        mVs->getWbRegion(camera,1,quali);
        wbagent.setRegion(camera ,1, quali);
    }
    wbagent.initLookupTable();
    wbagent.setDefault();
}

void RendererTdp::updatewb(unsigned char* bufy,  unsigned char* bufu,  unsigned char* bufv,  int width, int height)
{
    static int time = 0;
    if(wbagent.isTableAvail())
    {
        if(width == wbagent.CAP_WIDTH && height == wbagent.CAP_HEIGHT){
            wbagent.calcI420Level(bufy,  bufu, bufv);// + offset ,buf + offset + offset/4 );
//            time ++;
//            if(time > 200){
//                time = 0;
//                wbagent.dbg();
//            }
        }
        else{
            LOGW("wbagent parameter conflict & wb skiped.\n");
        }
    }
    return;
}

void RendererTdp::resize(int width, int height){
    static bool isRectFirstUse = true;

    scrn.ratio = GLfloat(width) / height;
    scrn.w = width;
    scrn.h = height;
    scrn.scalew = scrn.w / 1280.0;
    scrn.scaleh = scrn.h / 720.0;

    if(scrn.w > scrn.h){
        scrn.isHorizontal = true;
        disMode = 0;
        ui_virtual = ui_p1;
        ui_p1->setHorizontal();
        process((int)TdpanoCmd::TUNE_ITEMNULL);

    }else{
        scrn.isHorizontal = false;
        disMode = 0;
        ui_virtual = ui_p1;
        ui_p1->setVertical();
        process((int)TdpanoCmd::TUNE_ITEMNULL);        
    }

    viewPortResize(width, height);

#ifdef FUNC_GENERAL
    cameraAdaption();
    camera->vpholder[1].pos.z = 24;
    viewPortChange(4);
#endif 

#ifdef FUNC_CLIENT_FH
    viewPortChange_client_fuhuang(0);
    cameraAdaption_client_fuhuang(0);
    ui_p1->forceHide(true);
#endif 

    return;
}


void RendererTdp::viewPortResize(int width, int height)
{
    //第一次调用，clear一下rect，因为数组设置有冗余，避免使用到错误的区域

    //显示模式0，全屏显示
    scrn.AW = scrn.w;
    scrn.AH = scrn.h;

    //显示模式1,  2分屏,屏幕分为BC 两个区域
    scrn.BW = 840*scrn.scalew;
    scrn.CW = 440*scrn.scalew;
    scrn.BH = 720*scrn.scaleh;

    //调试模式， 3分屏， 屏幕分为DEF 三个区域
    scrn.DW = 720*scrn.scalew;
    scrn.DH = 720*scrn.scaleh;
    scrn.EW = 560*scrn.scalew;
    scrn.EH = 320*scrn.scaleh;
    scrn.FW = 560*scrn.scalew;
    scrn.FH = 400*scrn.scaleh;


    rect_A = Vector4(0, 0, scrn.w  , scrn.h);// +  vuport_pad;
    // 正常显示界面，分成左右两块
    rect_B0 = Vector4(0, 0, scrn.BW, scrn.BH);// +  vuport_pad;//rectgap;
    rect_B1 = Vector4(scrn.BW, 0, scrn.CW , scrn.BH);// +  vuport_pad;
    //调试界面分三块，左边avm，右上org，右下按键
    rect_C0 = Vector4(0, 0, scrn.DW , scrn.DH);// +  vuport_pad;
    rect_C1 = Vector4(scrn.DW, scrn.FH, scrn.EW, scrn.EH);// +  vuport_pad;
    rect_C2 = Vector4(scrn.DW, scrn.EH, scrn.FW, scrn.FH);// +  vuport_pad;

    //用来滑动的几个窗口
    rect_mv00 = Vector4(0,0,0,0);
    rect_mv10 = Vector4(0,0,0,0);//rect_B0;
    rect_mv11 = Vector4(0,0,0,0);
    rect_mv12 = Vector4(0,0,0,0);//rect_B1;



//    painter[0][0].vuport = Vector4(0, 0, BW, BH) +  vuport_pad;
//    painter[0][1].vuport = Vector4(0, 0, BW, BH) +  vuport_pad;//rectgap;//rectgap;
//    painter[0][2].vuport = Vector4(0, 0, BW, BH) +  vuport_pad;//rectgap;
//    painter[0][3].vuport = Vector4(0, 0, BW, BH) +  vuport_pad;//rectgap;
//    painter[0][4].vuport = Vector4(0, 0, BW, BH) +  vuport_pad;//rectgap;
//    painter[0][5].vuport = Vector4(BW, 0, CW , BH) +  vuport_pad;//Vector4(0,4,-4,-8);

//    painter[0][6].vuport = Vector4(0, 0, scrn.w  , scrn.h) +  vuport_pad;

    painter[1][0].vuport = rect_C0 + vuport_pad;//Vector4(0, 0, scrn.DW , scrn.DH) +  vuport_pad;
    painter[1][1].vuport = rect_C1 + vuport_pad;//Vector4(scrn.DW, scrn.FH, scrn.EW, scrn.EH) +  vuport_pad;
    painter[1][2].vuport = rect_C2 + vuport_pad;//Vector4(scrn.DW, scrn.EH, scrn.FW, scrn.FH) +  vuport_pad;


    //生成边框
    for(int j=0; j<DIS_GRP; j++){
        for(int i=0; i< DIS_ITEM; i++){
        viewPort2vb(painter[j][i].vuport, &painter[j][i].frame);
        }
    }

    checkSlideAction = false;
    slideAction0 = false;
    slideAction2 = false;

    return;
}


void RendererTdp::viewPortChange_client_fuhuang(int item)
{
    Vector4 fh_rect_const00, fh_rect_const01;
    Vector4 fh_rect_const02, fh_rect_const03, fh_rect_const04;
    Vector4 fh_rect_const05, fh_rect_const06, fh_rect_const07;

    float fh_BW = 480*scrn.scalew;
    float fh_BH = 720*scrn.scaleh;
    float fh_CW = 800*scrn.scalew;

    float fh_R0 = fh_BH*0.4;
    float fh_R1 = fh_BH*0.6;
    float fh_C0 = fh_CW*0.5;
    float fh_C1 = fh_CW*0.5;


    static Vector4 fh_vuport_pad = Vector4(4,4,-8,-8);


    fh_rect_const00 = Vector4(0,0,fh_BW,fh_BH); //左侧全景
    fh_rect_const01 = Vector4(fh_BW,0,fh_CW,fh_BH); //右侧大图

    fh_rect_const02 = Vector4(fh_BW,fh_R1,fh_CW, fh_R0);
    fh_rect_const03 = Vector4(fh_BW, 0, fh_C0, fh_R1);
    fh_rect_const04 = Vector4(fh_BW + fh_C0, 0, fh_C1, fh_R1);

    fh_rect_const05 = Vector4(fh_BW, fh_R0, fh_C0, fh_R1);
    fh_rect_const06 = Vector4(fh_BW + fh_C0, fh_R0, fh_C1, fh_R1);
    fh_rect_const07 = Vector4(fh_BW, 0,fh_CW, fh_R0);

    painter[0][0].vuport = Vector4(0, 0, 0, 0);
    painter[0][1].vuport = Vector4(0, 0, 0, 0);
    painter[0][2].vuport = Vector4(0, 0, 0, 0);
    painter[0][3].vuport = Vector4(0, 0, 0, 0);
    painter[0][4].vuport = Vector4(0, 0, 0, 0);
    painter[0][5].vuport = Vector4(0, 0, 0, 0);
    painter[0][6].vuport = Vector4(0, 0, 0, 0);

//    LOGI("vp3dmax.z = %f\n",camera->vp3d_max.pos.z);
//    if(item == 0){
    painter[0][5].vuport = fh_rect_const00 + fh_vuport_pad;
    viewPort2vb(painter[0][5].vuport, &painter[0][5].frame);

//    }

    if(item == 0){
        painter[0][0].vuport = fh_rect_const02 + fh_vuport_pad;
        viewPort2vb(painter[0][0].vuport, &painter[0][0].frame);

        painter[0][2].vuport = fh_rect_const03 + fh_vuport_pad;
        viewPort2vb(painter[0][2].vuport, &painter[0][2].frame);

        painter[0][3].vuport = fh_rect_const04 + fh_vuport_pad;
        viewPort2vb(painter[0][3].vuport, &painter[0][3].frame);
    }
    else if(item == 1){
        painter[0][1].vuport = fh_rect_const07 + fh_vuport_pad;
        viewPort2vb(painter[0][1].vuport, &painter[0][1].frame);

        painter[0][2].vuport = fh_rect_const05 + fh_vuport_pad;
        viewPort2vb(painter[0][2].vuport, &painter[0][2].frame);

        painter[0][3].vuport = fh_rect_const06 + fh_vuport_pad;
        viewPort2vb(painter[0][3].vuport, &painter[0][3].frame);
    }
    else if(item == 2){
        painter[0][2].vuport = fh_rect_const01 + fh_vuport_pad;
        viewPort2vb(painter[0][2].vuport, &painter[0][2].frame);
    }
    else if(item == 3){
        painter[0][3].vuport = fh_rect_const01 + fh_vuport_pad;
        viewPort2vb(painter[0][3].vuport, &painter[0][3].frame);
    }
    else if(item == 4){
        painter[0][0].vuport = fh_rect_const02 + fh_vuport_pad;
        viewPort2vb(painter[0][0].vuport, &painter[0][0].frame);

        painter[0][2].vuport = fh_rect_const03 + fh_vuport_pad;
        viewPort2vb(painter[0][2].vuport, &painter[0][2].frame);

        painter[0][4].vuport = fh_rect_const04 + fh_vuport_pad;
        viewPort2vb(painter[0][4].vuport, &painter[0][4].frame);

    }
    else if(item == 5){
        painter[0][0].vuport = fh_rect_const02 + fh_vuport_pad;
        viewPort2vb(painter[0][0].vuport, &painter[0][0].frame);

        painter[0][4].vuport = fh_rect_const03 + fh_vuport_pad;
        viewPort2vb(painter[0][4].vuport, &painter[0][4].frame);

        painter[0][3].vuport = fh_rect_const04 + fh_vuport_pad;
        viewPort2vb(painter[0][3].vuport, &painter[0][3].frame);

    }
    else if(item == 6){
        painter[0][0].vuport = fh_rect_const01 + fh_vuport_pad;
        viewPort2vb(painter[0][0].vuport, &painter[0][0].frame);        
    }
    else if(item == 7){
        painter[0][1].vuport = fh_rect_const01 + fh_vuport_pad;
        viewPort2vb(painter[0][1].vuport, &painter[0][1].frame);
    }    
    else{

    }
    return;
}


void RendererTdp::cameraAdaption()
{
    float h =  mVs->meshPara.H_BLANK;
    float w = mVs->meshPara.W_BLANK;

    camera->vp2d_min.pos.z = h*4;
    camera->vp2d.pos.z = h*5;   
    camera->vp2d_max.pos.z = h*6;

    camera->vp3d_min.pos.z = h*1.5;
    camera->vp3d.pos.z = h*4;
    camera->vp3d_max.pos.z = h*5;

    camera->vpmir_min.pos.z = h*2;
    camera->vpmir.pos.z = h*4;
    camera->vpmir_max.pos.z = h*3.5;


    //2d画面垂直向下俯视的视角
    camera->vpholder[0].pos = { 0.0, 0.0, 24.0 };
    camera->vpholder[0].rot = { 0.0, 0.0, 0.0 };
    camera->vpholder[0].pos.z = h*5;

    //3d画面视角
    camera->vpholder[1].pos = { 0.0, 1.0, 16.0 };
    camera->vpholder[1].rot = { 60.0, 0.0, 0.0 };
    camera->vpholder[1].pos.z = h*2.5;

    //mirror模式的视角，此模式应伴随镜像
    camera->vpholder[2].pos = { 0.0, 1.0, 16.0 };
    camera->vpholder[2].rot = { 75.0, 0.0, 180.0 };
    camera->vpholder[2].pos.z = h*2.2;

    //竖屏模式，3D进入时的2D视角
    camera->vpholder[3].pos = { 0.0, 1.0, 28.0 };
    camera->vpholder[3].rot = { 0.0, 0.0, 0.0 };

    //竖屏模式，mirror模式的视角，此模式应伴随镜像
    camera->vpholder[4].pos = { 0.0, 1.0, 20.0 };
    camera->vpholder[4].rot = { 60.0, 0.0, 180.0 };

    //设置调试观测vp
    camera->vpholder[6].pos = { 4.0, 0.0, 8.0 };
    camera->vpholder[6].rot = { 0.0, 0.0, 0.0 };
    
    //前俯视角度
    camera->vpholder[7].pos = { 0.0, 0.0, 0.0 };
    camera->vpholder[7].rot = { 0.0, 0.0, 0.0 };
    camera->vpholder[7].pos.y = h*0.5;
    camera->vpholder[7].pos.z = h*2;

    //后俯视角度
    camera->vpholder[8].pos = { 0.0, 0.0, 0.0 };
    camera->vpholder[8].rot = { 0.0, 0.0, 0.0 };
    camera->vpholder[8].pos.y = -h*0.5;
    camera->vpholder[8].pos.z = h*2;

    camera->vpholder[9].pos = { 0.0, 2.4, 5.5 };
    camera->vpholder[9].rot = { 30.0, 0.0, 90.0 };

    camera->vpholder[10].pos = { 0.0, 2.4, 5.5 };
    camera->vpholder[10].rot = { 30.0, 0.0, 270.0};
    // if(item <= 3 )
    // {
    //     camera->vp3d_max.pos.z = mVs->meshPara.H_BLANK*5;
    // }
    // else if(item == 4){
    //     camera->vp3d.pos = Vector3(-mVs->meshPara.W_BLANK/2, mVs->meshPara.H_BLANK/2, mVs->meshPara.H_BLANK*2);
    //     //camera->vp3d.rot = Vector3(65,0,15);
    //     camera->vp3d.rot = Vector3(0,0,0);
    // }
    // else if(item == 5){
    //     camera->vp3d.pos = Vector3(mVs->meshPara.W_BLANK/2, mVs->meshPara.H_BLANK/2, mVs->meshPara.H_BLANK*2);
    //     //camera->vp3d.rot = Vector3(65,0,-15);
    //     camera->vp3d.rot = Vector3(0,0,0);
    // }
    // else if(item == 6){
    //     camera->vp3d.pos = Vector3(0, 0, mVs->meshPara.H_BLANK*4);
    //     //camera->vp3d.rot = Vector3(65,0,-15);
    //     camera->vp3d.rot = Vector3(0,0,0);
    // }
    return;
}

void RendererTdp::cameraAdaption_client_fuhuang(int item)
{
    camera->vp2d.pos.z = mVs->meshPara.H_BLANK*4.5;
    camera->vp3d_max.pos.z = mVs->meshPara.H_BLANK*5;

    if(item <= 3 )
    {
        camera->vp3d_max.pos.z = mVs->meshPara.H_BLANK*5;
    }
    else if(item == 4){
        camera->vp3d.pos = Vector3(-mVs->meshPara.W_BLANK/2, mVs->meshPara.H_BLANK/2, mVs->meshPara.H_BLANK*2);
        //camera->vp3d.rot = Vector3(65,0,15);
        camera->vp3d.rot = Vector3(0,0,0);
    }
    else if(item == 5){
        camera->vp3d.pos = Vector3(mVs->meshPara.W_BLANK/2, mVs->meshPara.H_BLANK/2, mVs->meshPara.H_BLANK*2);
        //camera->vp3d.rot = Vector3(65,0,-15);
        camera->vp3d.rot = Vector3(0,0,0);
    }
    else if(item == 6){
        camera->vp3d.pos = Vector3(0, 0, mVs->meshPara.H_BLANK*4);
        //camera->vp3d.rot = Vector3(65,0,-15);
        camera->vp3d.rot = Vector3(0,0,0);
    }
    return;
}


void RendererTdp::viewPortChange(int item, bool bResetCamera)
{
    disCam = item;

    painter[0][0].vuport = Vector4(0, 0, 0, 0);
    painter[0][1].vuport = Vector4(0, 0, 0, 0);
    painter[0][2].vuport = Vector4(0, 0, 0, 0);
    painter[0][3].vuport = Vector4(0, 0, 0, 0);
    painter[0][4].vuport = Vector4(0, 0, 0, 0);
    painter[0][5].vuport = Vector4(0, 0, 0, 0);
    painter[0][6].vuport = Vector4(0, 0, 0, 0);

    if(item >=0 && item <= 3){
        painter[0][item].vuport = rect_B0 +  vuport_pad;//rectgap;
        painter[0][5].vuport = rect_B1 +  vuport_pad;//Vector4(0,4,-4,-8);
        viewPort2vb(painter[0][item].vuport, &painter[0][item].frame);
        viewPort2vb(painter[0][5].vuport, &painter[0][5].frame);
        CurViewPort = item;
        //滑动窗复位，没有这个复位，滑动窗工作可能不正常。
        rect_mv00 = Vector4(0,0,0,0);
        rect_mv10 = rect_B0;
        rect_mv11 = Vector4(0,0,0,0);
        rect_mv12 = rect_B1;

        if(bResetCamera){
            camera->jump3dTo(0);
            camera->jumpMirTo(0);
        }

        }
    else if(item == 4){
        painter[0][4].vuport = rect_B0 +  vuport_pad;//rectgap;
        painter[0][5].vuport = rect_B1 +  vuport_pad;//Vector4(0,4,-4,-8);
        viewPort2vb(painter[0][4].vuport, &painter[0][4].frame);
        viewPort2vb(painter[0][5].vuport, &painter[0][5].frame);
        CurViewPort = 4;
        painter[0][4].item = 4;
        //滑动窗复位，没有这个复位，滑动窗工作可能不正常。
        rect_mv00 = Vector4(0,0,0,0);
        rect_mv10 = rect_B0;
        rect_mv11 = Vector4(0,0,0,0);
        rect_mv12 = rect_B1;

        if(bResetCamera){
            camera->jumpMirTo(0);
            camera->turn3dTo(1);
        }
    }
    else if(item == 6){
        painter[0][6].vuport = rect_B0 +  vuport_pad;//rectgap;
        painter[0][5].vuport = rect_B1 +  vuport_pad;//Vector4(0,4,-4,-8);
        viewPort2vb(painter[0][6].vuport, &painter[0][6].frame);
        viewPort2vb(painter[0][5].vuport, &painter[0][5].frame);
        CurViewPort = 6;
        painter[0][6].item = 6;
        //滑动窗复位，没有这个复位，滑动窗工作可能不正常。
        rect_mv00 = Vector4(0,0,0,0);
        rect_mv10 = rect_B0;
        rect_mv11 = Vector4(0,0,0,0);
        rect_mv12 = rect_B1;        
        // painter[0][6].vuport = rect_A +  vuport_pad;
        // viewPort2vb(painter[0][6].vuport, &painter[0][6].frame);
        // CurViewPort = 6;
        // painter[0][6].item = 6;
        // //滑动窗复位，没有这个复位，滑动窗工作可能不正常。
        // rect_mv00 = rect_A;
        // rect_mv10 = rect_B0;
        // rect_mv11 = Vector4(0,0,0,0);
        // rect_mv12 = rect_B1;

        if(bResetCamera){
            camera->jump3dTo(0);
            //camera->turnMirTo(2);
            camera->jumpMirTo(2);
        }
    }
    else if(item == 7 || item ==  8){
        painter[0][4].vuport = rect_B0 +  vuport_pad;//rectgap;
        painter[0][5].vuport = rect_B1 +  vuport_pad;//Vector4(0,4,-4,-8);
        viewPort2vb(painter[0][4].vuport, &painter[0][4].frame);
        viewPort2vb(painter[0][5].vuport, &painter[0][5].frame);
        CurViewPort = 4;
        painter[0][4].item = 4;
        //滑动窗复位，没有这个复位，滑动窗工作可能不正常。
        rect_mv00 = Vector4(0,0,0,0);
        rect_mv10 = rect_B0;
        rect_mv11 = Vector4(0,0,0,0);
        rect_mv12 = rect_B1;

        if(bResetCamera){
            //camera->jumpMirTo(0);
            camera->turn3dTo(item);
        }
    }
    else if(item == 9){
        painter[0][4].vuport = rect_A +  vuport_pad;
        viewPort2vb(painter[0][4].vuport, &painter[0][4].frame);
        CurViewPort = 9;
        painter[0][4].item = 4;
        //滑动窗复位，没有这个复位，滑动窗工作可能不正常。
        rect_mv00 = rect_A;
        rect_mv10 = rect_B0;
        rect_mv11 = Vector4(0,0,0,0);
        rect_mv12 = rect_B1;

        if(bResetCamera){
            camera->jumpMirTo(0);
            camera->turn3dTo(1);
        }        
    }
    else if(item == 10){
        painter[0][6].vuport = rect_A +  vuport_pad;
        viewPort2vb(painter[0][6].vuport, &painter[0][6].frame);
        CurViewPort = 10;
        painter[0][6].item = 6;
        //滑动窗复位，没有这个复位，滑动窗工作可能不正常。
        rect_mv00 = rect_A;
        rect_mv10 = rect_B0;
        rect_mv11 = Vector4(0,0,0,0);
        rect_mv12 = rect_B1;

        if(bResetCamera){
            camera->jump3dTo(0);
            camera->turnMirTo(2);
        }        
    }    
    else{}


    if(!ctrl.enAllbs && !ctrl.enAvm2d){
        painter[0][5].vuport = Vector4(0,0,0,0);
        viewPort2vb(painter[0][4].vuport, &painter[0][4].frame);
    }

    ui_virtual->act(item);

    return;
}


void RendererTdp::viewPortMove(float x, float y, bool check)
{
    static bool isMove = false;
    static bool isX = true;

    static unsigned int _targetVport;
    static unsigned int targetVport;

    float ux,uy;

    if(slideAction2){
        return;
    }

    if(!check){ // 正常的交互操作
        ux = x;
        uy = y;
    }
    else if(rect_mv10.x != 0){ // 程序自动完成滑动的后半部分
        if(rect_mv10.x <= -scrn.BW/2)
            ux = -scrn.BW -rect_mv10.x;
        else if(rect_mv10.x < 0)
            ux = -rect_mv10.x;
        else if(rect_mv10.x <= scrn.BW/2)
            ux = -rect_mv10.x;
        else
            ux = scrn.BW - rect_mv10.x;

        ux = ux/3;
    }
    else if(rect_mv10.y != 0){
        if(rect_mv10.y <= -scrn.BH/2 )
            uy = scrn.BH + rect_mv10.y;
        else if(rect_mv10.y < 0)
            uy = rect_mv10.y;
        else if(rect_mv10.y <= scrn.BH/2)
            uy = rect_mv10.y;
        else
            uy = -scrn.BH + rect_mv10.y;

        uy = uy/3;
    }

    if(!isMove){
        isMove=true;
    }

    //初始位置为（0，0）滑动动作启动，
    if(rect_mv10.x == 0 && rect_mv10.y == 0){
        if(fabs(ux) >= fabs(uy)){
            rect_mv10.x += ux;
        }
        else{
            rect_mv10.y -= uy;
        }
    }
    //已经在滑动过程中， 且滑动方向为 x 方向
    else if(rect_mv10.x && rect_mv10.y == 0){
        rect_mv10.x += ux;
    }
    //已经在滑动过程中， 且滑动方向为 y 方向
    else if(rect_mv10.x == 0 && rect_mv10.y){
        rect_mv10.y -= uy;
    }
    else{
    }

    //滑动钳位1. 首先确保滑动不超限
    if(rect_mv10.x > scrn.BW) rect_mv10.x = scrn.BW;
    if(rect_mv10.x < -scrn.BW) rect_mv10.x = -scrn.BW;
    if(rect_mv10.y > scrn.BH) rect_mv10.y = scrn.BH;
    if(rect_mv10.y < -scrn.BH) rect_mv10.y = -scrn.BH;

    //滑动钳位2，不能向自身方向滑动，比如当前是 cam0 窗口， 就不能再把cam0滑出来了
    //钳位之后，滑动窗可能还是在pos（0,0）
    if(CurViewPort == 0 && rect_mv10.y < 0)
        rect_mv10.y = 0;
    else if(CurViewPort == 1 && rect_mv10.y > 0)
        rect_mv10.y = 0;
    else if(CurViewPort == 2 && rect_mv10.x > 0)
        rect_mv10.x = 0;
    else if(CurViewPort == 3 && rect_mv10.x < 0)
        rect_mv10.x = 0;
    else{}

    //生成滑入窗口
    //滑动窗口卡位到当前位
    if(fabs(rect_mv10.x) <= 20 && fabs(rect_mv10.y) <= 20){
        viewPortChange(CurViewPort, false);
        slideAction0 = false;
        checkSlideAction = false;
        return;
    }
    //滑动窗口卡到其他位置
    else if(fabs(fabs(rect_mv10.x) - scrn.BW) <= 20 || fabs(fabs(rect_mv10.y) - scrn.BH) <= 20){
        viewPortChange(targetVport);
        slideAction0 = false;
        checkSlideAction = false;
        return;
    }
    //双窗口滑动中
    else if(rect_mv10.x > 0 && rect_mv10.y == 0){
        rect_mv11 = rect_mv10 - Vector4(scrn.BW, 0, 0, 0);
        targetVport = 2;
    }
    else if(rect_mv10.x < 0 && rect_mv10.y == 0){
        rect_mv11 = rect_mv10 + Vector4(scrn.BW, 0, 0, 0);
        targetVport = 3;
    }
    else if(rect_mv10.x == 0 && rect_mv10.y > 0){
        rect_mv11 = rect_mv10 - Vector4(0, scrn.BH, 0, 0);
        targetVport = 1;
    }
    else if(rect_mv10.x == 0 && rect_mv10.y < 0){
        rect_mv11 = rect_mv10 + Vector4(0, scrn.BH, 0, 0);
        targetVport = 0;
    }
    else{
        rect_mv11 = Vector4(0,0,0,0);
        targetVport = 7;
    }


    painter[0][CurViewPort].vuport = viewPortClamp(rect_mv10 + vuport_pad, rect_B0 + vuport_pad);
    painter[0][targetVport].vuport = viewPortClamp(rect_mv11 + vuport_pad, rect_B0 + vuport_pad);

    viewPort2vb(painter[0][CurViewPort].vuport, &painter[0][CurViewPort].frame);
    viewPort2vb(painter[0][targetVport].vuport, &painter[0][targetVport].frame);

    slideAction0 = true;

    return;
}


void RendererTdp::viewPortMove2(float x, float y, bool check)
{
    static unsigned int targetVport;
    static Vector4 _base = Vector4(0,0,0,0);

    float ux,uy;


    ux = 0;
    if(!check){ // 正常的交互操作
        uy = y;
    } // 程序自动完成滑动的后半部分
    else if(_base.y != 0){
        if(_base.y <= -scrn.BH/2 )
            uy = scrn.BH + _base.y;
        else if(_base.y < 0)
            uy = _base.y;
        else if(_base.y <= scrn.BH/2)
            uy = _base.y;
        else
            uy = -scrn.BH + _base.y;

        uy = uy/3;
    }

    //滑动
    _base.y -= uy;
    //钳位控制 滑动使能
    if(_base.y > 0) _base.y = 0; // 钳位，只向下滑动
//    if(!ctrl.slide3dOn && _base.y > 0) _base.y = 0; //如果没有使能3d滑动， 那就禁止上滑
//    if(!ctrl.slideMirrorOn && _base.y < 0) _base.y = 0; //如果没有使能 mir滑动， 那就禁止下滑

    //滑动钳位1. 首先确保滑动不超限
//    if(rect_mv10.x > BW) rect_mv10.x = BW;
//    if(rect_mv10.x < -BW) rect_mv10.x = -BW;
    if(_base.y > scrn.BH) _base.y = scrn.BH;
    if(_base.y < -scrn.BH) _base.y = -scrn.BH;

    //生成滑入窗口
    //滑动窗口卡位到当前位
    if(fabs(_base.x) <= 20 && fabs(_base.y) <= 20){
        viewPortChange(CurViewPort, false);
        _base = Vector4(0,0,0,0);
        slideAction2 = false;
        checkSlideAction = false;
        //DBG("start clamp");
        return;
    }
    //滑动窗口卡到其他位置
    else if(fabs(fabs(_base.x) - scrn.BW) <= 20 || fabs(fabs(_base.y) - scrn.BH) <= 20){
        viewPortChange(targetVport);
        _base = Vector4(0,0,0,0);
        slideAction2 = false;
        checkSlideAction = false;
        //DBG("slide clamp");
        return;
    }
    // //放弃了下边的上滑，下滑 模式， 因为上滑比较别扭， 修改为 下滑切换几个视角
    // //双窗口滑动中,如果是上滑，在 3D和Org之间切换
    // else if(_base.x == 0 && _base.y > 0){
    //     rect_mv10 = _base + rect_B0;
    //     rect_mv11 = rect_mv10 - Vector4(0, scrn.BH, 0, 0);
    //     //targetVport = 4;
    //     if(CurViewPort != 4)targetVport = 4;
    //     else targetVport = 1;

    //     painter[0][CurViewPort].vuport = viewPortClamp(rect_mv10 + vuport_pad, rect_B0 + vuport_pad);
    //     painter[0][5].vuport = viewPortClamp(rect_B1 + vuport_pad, rect_B1 + vuport_pad);
    //     painter[0][targetVport].vuport = viewPortClamp(rect_mv11 + vuport_pad, rect_B0 + vuport_pad);

    //     viewPort2vb(painter[0][CurViewPort].vuport, &painter[0][CurViewPort].frame);
    //     viewPort2vb(painter[0][5].vuport, &painter[0][5].frame);
    //     viewPort2vb(painter[0][targetVport].vuport, &painter[0][targetVport].frame);

    // }
    // //双窗口滑动中，如果是下滑， 在mirror 和Org之间切换
    // else if(_base.x == 0 && _base.y < 0){
    //     //targetVport = 1;
    //     if(CurViewPort != 6){
    //         targetVport = 6;
    //         rect_mv10 = _base + rect_B0;
    //         rect_mv11 = _base + rect_B1;
    //         rect_mv12 = _base + Vector4(0, scrn.BH, 0, 0) + rect_const00;
    //     }
    //     else{
    //         targetVport = 1;
    //         rect_mv10 = _base + rect_const00;
    //         rect_mv11 = _base + Vector4(0, scrn.BH, 0, 0) + rect_B1;
    //         rect_mv12 = _base + Vector4(0, scrn.BH, 0, 0) + rect_B0;
    //     }
    //     painter[0][CurViewPort].vuport = viewPortClamp(rect_mv10 + vuport_pad, rect_const00 + vuport_pad);
    //     painter[0][5].vuport = viewPortClamp(rect_mv11 + vuport_pad, rect_B1 + vuport_pad);
    //     painter[0][targetVport].vuport = viewPortClamp(rect_mv12 + vuport_pad, rect_const00 + vuport_pad);

    //     viewPort2vb(painter[0][CurViewPort].vuport, &painter[0][CurViewPort].frame);
    //     viewPort2vb(painter[0][5].vuport, &painter[0][5].frame);
    //     viewPort2vb(painter[0][targetVport].vuport, &painter[0][targetVport].frame);
    // }
    //// 讲上面的上下滑动修改为只向下滑动，滑动过程中切换几个视角  org》3d， mir》3d， 3d》mir；
    /// Org >> 3d
    else if(CurViewPort >= 0 && CurViewPort <= 3){
        targetVport = 4;   

        rect_mv10 = _base + rect_B0;
        rect_mv11 = rect_mv10 + Vector4(0, scrn.BH, 0, 0);

        // if(CurViewPort != 4)targetVport = 4;
        // else targetVport = 1;

        painter[0][CurViewPort].vuport = viewPortClamp(rect_mv10 + vuport_pad, rect_B0 + vuport_pad);
        painter[0][5].vuport = viewPortClamp(rect_B1 + vuport_pad, rect_B1 + vuport_pad);
        painter[0][targetVport].vuport = viewPortClamp(rect_mv11 + vuport_pad, rect_B0 + vuport_pad);

        viewPort2vb(painter[0][CurViewPort].vuport, &painter[0][CurViewPort].frame);
        viewPort2vb(painter[0][5].vuport, &painter[0][5].frame);
        viewPort2vb(painter[0][targetVport].vuport, &painter[0][targetVport].frame);
    }
    /// mir >> 3d    
    else if(CurViewPort == 6){
        targetVport = 4;

        // rect_mv10 = _base + rect_A;
        // rect_mv11 = _base + Vector4(0, scrn.BH, 0, 0) + rect_B1;
        // rect_mv12 = _base + Vector4(0, scrn.BH, 0, 0) + rect_B0;
        rect_mv10 = _base + rect_B0;
        rect_mv11 = rect_mv10 + Vector4(0, scrn.BH, 0, 0);

        painter[0][CurViewPort].vuport = viewPortClamp(rect_mv10 + vuport_pad, rect_A + vuport_pad);
        painter[0][5].vuport = viewPortClamp(rect_B1 + vuport_pad, rect_B1 + vuport_pad);
        painter[0][targetVport].vuport = viewPortClamp(rect_mv11 + vuport_pad, rect_B0 + vuport_pad);

        viewPort2vb(painter[0][CurViewPort].vuport, &painter[0][CurViewPort].frame);
        viewPort2vb(painter[0][5].vuport, &painter[0][5].frame);
        viewPort2vb(painter[0][targetVport].vuport, &painter[0][targetVport].frame);
    }
    /// 3d >> mir
    else if(CurViewPort == 4 && ctrl.slideMirrorOn){
        targetVport = 6;

        ///直接滑动到全屏Mir
        // rect_mv10 = _base + rect_B0;
        // rect_mv11 = _base + rect_B1;
        // rect_mv12 = _base + Vector4(0, scrn.BH, 0, 0) + rect_A;
        ///滑动到半屏Mir
        rect_mv10 = _base + rect_B0;
        rect_mv11 = rect_mv10 + Vector4(0, scrn.BH, 0, 0);

        painter[0][CurViewPort].vuport = viewPortClamp(rect_mv10 + vuport_pad, rect_A + vuport_pad);
        painter[0][5].vuport = viewPortClamp(rect_B1 + vuport_pad, rect_B1 + vuport_pad);
        painter[0][targetVport].vuport = viewPortClamp(rect_mv11 + vuport_pad, rect_B0 + vuport_pad);

        viewPort2vb(painter[0][CurViewPort].vuport, &painter[0][CurViewPort].frame);
        viewPort2vb(painter[0][5].vuport, &painter[0][5].frame);
        viewPort2vb(painter[0][targetVport].vuport, &painter[0][targetVport].frame);
    }
    ///slide_to_mirror关闭时， 3d >> org
    else if(CurViewPort == 4 && !ctrl.slideMirrorOn){
        targetVport = 1;

        rect_mv10 = _base + rect_B0;
        rect_mv11 = rect_mv10 + Vector4(0, scrn.BH, 0, 0);

        painter[0][CurViewPort].vuport = viewPortClamp(rect_mv10 + vuport_pad, rect_B0 + vuport_pad);
        painter[0][5].vuport = viewPortClamp(rect_B1 + vuport_pad, rect_B1 + vuport_pad);
        painter[0][targetVport].vuport = viewPortClamp(rect_mv11 + vuport_pad, rect_B0 + vuport_pad);

        viewPort2vb(painter[0][CurViewPort].vuport, &painter[0][CurViewPort].frame);
        viewPort2vb(painter[0][5].vuport, &painter[0][5].frame);
        viewPort2vb(painter[0][targetVport].vuport, &painter[0][targetVport].frame);
    }    
    else{
        rect_mv11 = Vector4(0,0,0,0);
        targetVport = CurViewPort;
    }

    slideAction2 = true;

    return;
}

//返回-1是没有选中，或者无效
//返回 0,1,2，3……则是有效值
int RendererTdp::viewPortPick(float x, float y)
{
    float ux,uy;
    int tx,ty,tt;
//    if(disMode == 0 && CurViewPort != 6){
    if(disMode == 0 && painter[0][5].vuport.z > 0 && painter[0][5].vuport.w > 0){    
        pressIn2D = false;
        if(x < rect_B1.x || x > (rect_B1.x + rect_B1.z)){
            return -1;
        }
        if(y < rect_B1.y || y > (rect_B1.y + rect_B1.w)){
            return -1;
        }
        pressIn2D = true;

        ux = x - rect_B1.x;
        uy = y;
        ux /= rect_B1.z;
        uy /= rect_B1.w;

        tx = ux*4;
        ty = uy*5;
        tt = ty*4 + tx;

//        DBG("%f, %f, %d,%d.\n",x, y, tx,ty);

        if(tt == 1 || tt == 2 ){
            return 0;
        }
        else if(tt == 17 || tt == 18){
            return 1;
        }
        else if(tt == 4 || tt == 8 || tt == 12){
            return 2;
        }
        else if(tt == 7 || tt == 11 || tt == 15){
            return 3;
        }
        else if(tt == 5 || tt == 6){
            return 7;
        }
        else if(tt == 9 || tt == 10){
            if(disCam == 4){
                return 6;
            }
            else{
                return 4;
            }
        }
        else if(tt == 13 || tt == 14){
            return 8;
        }
    }
    return -1;
}

void RendererTdp::viewPort2vb(const Vector4& rct, VertexBlock* vb)
{
    vb->seek(0);
    vb->posNext() = Vector3(rct.x, rct.y, -4.0);
    vb->posNext() = Vector3(rct.x, rct.y + rct.w, -4.0);
    vb->posNext() = Vector3(rct.x + rct.z, rct.y + rct.w, -4.0);
    vb->posNext() = Vector3(rct.x + rct.z, rct.y, -4.0);
    return;
}

Vector4 RendererTdp::viewPortClamp(const Vector4& rct,const Vector4& clp)
{
    Vector4 v0, v1;
    v0 = rct;
    v1 = clp;

    v0.z += v0.x;
    v0.w += v0.y;

    v1.z += v1.x;
    v1.w += v1.y;

    v0.x = v0.x < v1.x ? v1.x : v0.x;
    v0.x = v0.x > v1.z ? v1.z : v0.x;

    v0.z = v0.z < v1.x ? v1.x : v0.z;
    v0.z = v0.z > v1.z ? v1.z : v0.z;

    v0.y = v0.y < v1.y ? v1.y : v0.y;
    v0.y = v0.y > v1.w ? v1.w : v0.y;

    v0.w = v0.w < v1.y ? v1.y : v0.w;
    v0.w = v0.w > v1.w ? v1.w : v0.w;

    v0.z -= v0.x;
    v0.w -= v0.y;

    //rct = v0;
    return v0;
}



void RendererTdp::drawFrame()
{
        static clock_t t1, t2, t3, t4;

        static int t_CurItem;
        static int t_CurCam;
        static int t_CurMark;

        static bool im = false;

        //static int pre_bindwidth=0, pre_bindheight=0;
//        if(!im){
//            im = true;
//        }
//        else{
//            LOGE("reenter******************");
//            return;
//        }

        t1 = clock();

        ///如果使用内部临时纹理，则无需在bind视频了，已经一次性绑定了
        if(global.useInnerTexture){

        }
        ///如果纹理在外部绑定，update的是 texture id ，也不用绑定纹理
//        else if(){

//        }
        ///如果使用外部纹理，才持续刷新
        else{
            if(pre_bindwidth != bindwidth || pre_bindheight != bindheight || pre_bindwidth == 0 || pre_bindheight == 0){
                gleo::texBindLumi(exTex.txid0[0], exTex.bb0[0], bindwidth, bindheight);
                gleo::texBindLumi(exTex.txid0[1], exTex.bb0[1], bindwidth/2, bindheight/2);
                gleo::texBindLumi(exTex.txid0[2], exTex.bb0[2], bindwidth/2, bindheight/2);
                ///如果输入图像是分离的，那么一共要 绑定 12个纹理
                if(!exTex.isAssemble){
                    gleo::texBindLumi(exTex.txid1[0], exTex.bb1[0], bindwidth, bindheight);
                    gleo::texBindLumi(exTex.txid1[1], exTex.bb1[1], bindwidth/2, bindheight/2);
                    gleo::texBindLumi(exTex.txid1[2], exTex.bb1[2], bindwidth/2, bindheight/2);

                    gleo::texBindLumi(exTex.txid2[0], exTex.bb2[0], bindwidth, bindheight);
                    gleo::texBindLumi(exTex.txid2[1], exTex.bb2[1], bindwidth/2, bindheight/2);
                    gleo::texBindLumi(exTex.txid2[2], exTex.bb2[2], bindwidth/2, bindheight/2);

                    gleo::texBindLumi(exTex.txid3[0], exTex.bb3[0], bindwidth, bindheight);
                    gleo::texBindLumi(exTex.txid3[1], exTex.bb3[1], bindwidth/2, bindheight/2);
                    gleo::texBindLumi(exTex.txid3[2], exTex.bb3[2], bindwidth/2, bindheight/2);
                }
                LOGE("rebind texture (%d,%d) >> (%d,%d).", pre_bindwidth, pre_bindheight, bindwidth, bindheight);

                pre_bindwidth = bindwidth;
                pre_bindheight = bindheight;
            }
            else{
                gleo::texBindSubLumi(exTex.txid0[0], exTex.bb0[0], bindwidth, bindheight);
                gleo::texBindSubLumi(exTex.txid0[1], exTex.bb0[1], bindwidth/2, bindheight/2);
                gleo::texBindSubLumi(exTex.txid0[2], exTex.bb0[2], bindwidth/2, bindheight/2);
                ///如果输入图像是分离的，那么一共要绑定 12个纹理
                if(!exTex.isAssemble){
                    gleo::texBindSubLumi(exTex.txid1[0], exTex.bb1[0], bindwidth, bindheight);
                    gleo::texBindSubLumi(exTex.txid1[1], exTex.bb1[1], bindwidth/2, bindheight/2);
                    gleo::texBindSubLumi(exTex.txid1[2], exTex.bb1[2], bindwidth/2, bindheight/2);

                    gleo::texBindSubLumi(exTex.txid2[0], exTex.bb2[0], bindwidth, bindheight);
                    gleo::texBindSubLumi(exTex.txid2[1], exTex.bb2[1], bindwidth/2, bindheight/2);
                    gleo::texBindSubLumi(exTex.txid2[2], exTex.bb2[2], bindwidth/2, bindheight/2);

                    gleo::texBindSubLumi(exTex.txid3[0], exTex.bb3[0], bindwidth, bindheight);
                    gleo::texBindSubLumi(exTex.txid3[1], exTex.bb3[1], bindwidth/2, bindheight/2);
                    gleo::texBindSubLumi(exTex.txid3[2], exTex.bb3[2], bindwidth/2, bindheight/2);
                 }

            }
        }
         // printf("11\n");

        t2 = clock();
    //DBG("tex:%.3f ms\n", (t2 - t1)/1000.0);

        t_CurItem = mVs->getChkItem();
        t_CurCam = mVs->getChkCam();
        t_CurMark = mVs->getChkMark();

        t1 = clock();

        //updatebuf(inTex.i420Buf, inTex.capW, inTex.capH);
        //wbagent.calcI420Level(inTex.i420Buf, inTex.i420Buf+ inTex.capW*inTex.capH, inTex.i420Buf+ inTex.capW*inTex.capH + inTex.capW*inTex.capH/4);
        //wbagent.dbg();

        t2 = clock();

        glClearColor(0.1, 0.1, 0.1, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glCullFace(GL_BACK);
        glFrontFace(GL_CCW);
        glEnable(GL_CULL_FACE);
        glDepthFunc(GL_LEQUAL);
        
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);

        // 重要的控制变量
        // 此参数决定 shader 是否打开全局色彩均衡, 0.0:关闭  1.0:打开
        uni->avm.cambalance.blankAndCamera.w = 1.0;

        //██████████████████████//绘图区域【0】，绘制 3D画面 或者 原始视频
        //绘制Org图像

        Vector4 _viewport;
        int _item;
        //VertexBlock *_vb;

        int TOTAL;
        if(disMode == 0){TOTAL = 6;}
        else{TOTAL=0;}

        for(int loop = 0;loop<= TOTAL; loop++){
            if(painter[disMode][loop].vuport.z <= 0 || painter[disMode][loop].vuport.w <= 0){continue;}

            _viewport = painter[disMode][loop].vuport;
            _item = painter[disMode][loop].item;

            ///显示org画面
            if(_item >=0 && _item <= 3){
                glViewport(_viewport.x, _viewport.y, _viewport.z, _viewport.w);

                uni->projection.identity();
                uni->projection.setOrthoFrustum(0, 1280, 0, 720, -100, 100);
                uni->mv.identity();
                uni->mvp = uni->projection;// * uni->mv;

                drawOrg(ORG_VIEW_MODE + _item);

                //画倒车标尺线
                if(ctrl.lineRearOn){
                    if(_item == 1 ){
                        uni->shaderPC.use();
                        // mVs->createMarkVbIb(t_CurCam);
                        // gleo::draw(&mVs->tVbMark, &mVs->tIbMark, NULL, NULL, &shaderPC);
                        gleo::draw(&mVs->vtxBiaochi, &mVs->idxBiaochi, NULL, NULL, &uni->shaderPC, GL_LINES);
                    }
                }
            }
            //    break;
            ///平面2D全景或者雷达警告
//            else if(_item == 5 || _item == 7 || _item == 8){
//                glViewport(_viewport.x, _viewport.y, _viewport.z, _viewport.w);
//                uni->calcFrustum(camera->vp2d.pos, camera->vp2d.rot, _viewport.z/_viewport.w);


//            }
            else if(_item >= 4 && _item <= 10){
                if(_item == 4 || _item == 10){
                    glViewport(_viewport.x, _viewport.y, _viewport.z, _viewport.w);
                    uni->calcFrustum(camera->vp3d.pos, camera->vp3d.rot, _viewport.z/_viewport.w);
                }
                else if(_item == 5 || _item == 7 || _item == 8){
                    glViewport(_viewport.x, _viewport.y, _viewport.z, _viewport.w);
                    uni->calcFrustum(camera->vp2d.pos, camera->vp2d.rot, _viewport.z/_viewport.w);
                }
                else if(_item == 6 || _item == 9){
                    glViewport(_viewport.x, _viewport.y, _viewport.z, _viewport.w);
                    uni->calcFrustum(camera->vpmir.pos, camera->vpmir.rot, _viewport.z/_viewport.w);

                    Matrix4 _mir;
                    _mir.identity();
                    _mir[0] = -1.0;
                    uni->calc(_mir);


                    glCullFace(GL_FRONT);                   
                }
                // else if(_item == 7){
                //     glViewport(_viewport.x, _viewport.y, _viewport.z, _viewport.w);
                //     uni->calcFrustum(camera->vp3d.pos, camera->vp3d.rot, _viewport.z/_viewport.w);                    
                // }
                // else if(_item == 8){
                //     glViewport(_viewport.x, _viewport.y, _viewport.z, _viewport.w);
                //     uni->calcFrustum(camera->vp3d.pos, camera->vp3d.rot, _viewport.z/_viewport.w);  
                // }
                else {
                    continue;
//                    glViewport(_viewport.x, _viewport.y, _viewport.z, _viewport.w);
//                    uni->calcFrustum(camera->vp2d.pos, camera->vp2d.rot, _viewport.z/_viewport.w);
                }

                uni->avm.cambalance.blankAndCamera.w = 1.0;

                //============画全景================

                if(_item == 5){
                    if(ctrl.enAvm2d){
                        drawAvm();
                    }
                    if(ctrl.enAllbs){
                        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                        glEnable(GL_BLEND);
                        uni->shaderPC.use();
                        gleo::draw(&mdoabs.vb, &mdoabs.ib, NULL, NULL, &uni->shaderPC, GL_TRIANGLES);
                    }
                }
                else{
                    drawAvm();
                }


                //============画轨迹线==============
                if(ctrl.lineTrailOn){
                    //if(_item == 4 || _item == 5 || _item == 6 || _item == 9 || _item == 10){
                    mdotline.create(moveAngle, bAhead);
                    uni->shaderPC.use();
                    gleo::draw(&mdotline.vb, &mdotline.ib, NULL, NULL, &uni->shaderPC, GL_LINES);
                    //}
                }
                //=============画车==================
                drawCar((_item == 6 )? true : false);


                glCullFace(GL_BACK);
                //============画调试框================
                if(disMode == 1){
                    uni->shaderPC.use();
                    gleo::draw(&mdotrect.vb, &mdotrect.ib, NULL, NULL, &uni->shaderPC, GL_LINES);
                }
                //glFrontFace(GL_CCW);
            }
        }

        glDisable(GL_DEPTH_TEST);
        glDisable(GL_CULL_FACE);
        //glFrontFace(GL_CCW);
        //glCullFace(GL_BACK);

        //计算全局的变换矩阵
        if(disMode == 1){
            glViewport(painter[1][1].vuport.x, painter[1][1].vuport.y, painter[1][1].vuport.z, painter[1][1].vuport.w);
            uni->calcOrthFrustum(0,1280,0,720,-100,100);

            drawTune(t_CurItem, t_CurCam);
        }
        ////绘制按键
        glViewport(0,0, scrn.w, scrn.h);
        uni->calcOrthFrustum(0, ui_virtual->KBSIZE.x, 0, ui_virtual->KBSIZE.y, 10, -10);

        drawUi();

        uni->calcOrthFrustum(0, scrn.w, 0, scrn.h, 100, -100);
        //// 画边框
        if(disMode == 0){ // disMode == 0， 正常显示模式， 总共有7个viewport需要遍历
            for(int loop = 0;loop<= 6; loop++){
                if(painter[0][loop].vuport.z <= 0 || painter[0][loop].vuport.w <= 0){continue;}
                gleo::draw(&painter[0][loop].frame, &ibrect, NULL, NULL, &uni->shaderPC, GL_LINES);
            }
        }
        else if(disMode == 1){
            gleo::draw(&painter[1][0].frame, &ibrect, NULL, NULL, &uni->shaderPC, GL_LINES);
            if (t_CurItem == mVs->TUNING_ITEM_CAMPOS || t_CurItem == mVs->TUNING_ITEM_MARK || t_CurItem == mVs->TUNING_ITEM_CENTER){
                gleo::draw(&painter[1][1].frame, &ibrect, NULL, NULL, &uni->shaderPC, GL_LINES);
            }
        }

        glUseProgram(0);
        glBindTexture(GL_TEXTURE_2D, 0);


        t3 = clock();

        //DBG("tex:%.3f draw:%.3f fr:%.3f ms\n", (t2 - t1)/1000.0, (t3- t2)/1000.0, (t3-t4)/1000.0);

        camera->updateVp();
        t4 = clock();

    //opera.isDrawing = false;

    if(checkSlideAction && slideAction0){
        viewPortMove(0,0,true);
    }
    else if(checkSlideAction && slideAction2){
        viewPortMove2(0,0,true);
    }

    im = false;
    return;
}

void RendererTdp::drawOrg(int cam)
{
//    if(cam < 0 || cam > 3){
//        return;
//    }
//    static bool vbib_ok = false;

    uni->avm.cambalance.blankAndCamera.w = 0.0;
    uni->avm.cambalance.blankAndCamera.z = 4.0;

//    if(!vbib_ok){
//        mVs->createOrgVbIb(cam, false);
//        vbib_ok = true;
//    }

//    glDisable(GL_DEPTH_TEST);
//    glDisable(GL_BLEND);
//    glDisable(GL_CULL_FACE);

    uni->avm.uvAdpter = uni->avm.uvAdpterValue[1]; ///uvAdpterValue参数好像已经失效了，shader没用这个参数了
    gleo::draw(&mVs->tVbOrg[cam], &mVs->tIbOrg, NULL, pTxtrAvm[cam%4], uni->shaderAvm);
    return;
}


void RendererTdp::drawAvm()
{
    //glEnable(GL_MULTISAMPLE);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_BLEND);

    uni->avm.uvAdpter = Vector4(1.0, 0.0, 1.0, 0.0);

    if(ctrl.enDrawAvm){
        //画图--vs左右部分=========================================================
        uni->avm.uvAdpter = uni->avm.uvAdpterValue[2];
        uni->avm.cambalance.blankAndCamera.z = exTex.isAssemble ? 2.0 : 4.0;
        uni->avm.cambalance.coff0 = wbagent.camrgn[2][0].coff;
        uni->avm.cambalance.coff1 = wbagent.camrgn[2][1].coff;
        //------------------
        uni->shaderAvm->use();
        gleo::draw(mVs->vtxLeft, mVs->idxLeft, NULL,  pTxtrAvm[2], uni->shaderAvm);

        uni->avm.uvAdpter = uni->avm.uvAdpterValue[3];
        uni->avm.cambalance.blankAndCamera.z = exTex.isAssemble ? 3.0 : 4.0;
        uni->avm.cambalance.coff0 = wbagent.camrgn[3][1].coff;
        uni->avm.cambalance.coff1 = wbagent.camrgn[3][0].coff;
        //------------------
        uni->shaderAvm->use();//fillUniform();
        gleo::draw(mVs->vtxRight, mVs->idxRight, NULL, pTxtrAvm[3], uni->shaderAvm);

        glDisable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);

        //画图-vs前后部分============================================================
        uni->avm.uvAdpter = uni->avm.uvAdpterValue[0];
        uni->avm.cambalance.blankAndCamera.z =  exTex.isAssemble ? 0.0 : 4.0;
        uni->avm.cambalance.coff0 = wbagent.camrgn[0][0].coff;
        uni->avm.cambalance.coff1 = wbagent.camrgn[0][1].coff;
        //------------------
        uni->shaderAvm->use();//fillUniform();
        gleo::draw(mVs->vtxFront, mVs->idxFront,  NULL, pTxtrAvm[0],  uni->shaderAvm);

        uni->avm.uvAdpter = uni->avm.uvAdpterValue[1];
        uni->avm.cambalance.blankAndCamera.z =  exTex.isAssemble ? 1.0 : 4.0;
        uni->avm.cambalance.coff0 = wbagent.camrgn[1][1].coff;
        uni->avm.cambalance.coff1 = wbagent.camrgn[1][0].coff;
        //------------------
        uni->shaderAvm->use();//fillUniform();
        gleo::draw(mVs->vtxBack, mVs->idxBack,  NULL, pTxtrAvm[1],  uni->shaderAvm);
    }
    return;
}


void RendererTdp::drawCar(bool bTrans)
{

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_BLEND);

    //画小车=================================================================
    IndexBlock *tmpib;
    MaterialBlock *tmpmb;
    VertexBlock *tmpvb;

//    for (int iblksloop = 0; iblksloop < mycar->iblks.size(); iblksloop++){
//        tmpib = mycar->iblks[iblksloop];
//        tmpmb = mycar->mblks[mycar->iblks[iblksloop]->matId];
////        tmpvb = mycar->vblks[mycar->iblks[iblksloop]->vtxId];

//        gleo::updateMaterial(tmpmb, uni->materialDefault.ambient, uni->materialDefault.diffuse, uni->materialDefault.specular);
//        gleo::draw(mycar->vblks[0], tmpib, NULL, NULL , &shaderAdsg);
//    }
    if(bTrans){
        //====使用深度shader，把车体的深度绘制出来（不绘制车辆图像), 绘制深度的时候，屏蔽玻璃等半透明部件
        for (int iblksloop = 0; iblksloop < mycar->iblks.size(); iblksloop++){
            tmpib = mycar->iblks[iblksloop];
            tmpmb = mycar->mblks[mycar->iblks[iblksloop]->matId];
            tmpvb = mycar->vblks[mycar->iblks[iblksloop]->vtxId];
            if(tmpib->textureCount == 0 && tmpmb->transparency <= 0.1 ){
                gleo::draw(tmpvb, tmpib, NULL, NULL , &uni->shaderPDepth);
            }
        }
        //====绘制车辆，并且手工将所有材质修改为半透明，这样就能绘制出透明车体
        //====因为已经绘制过车辆的深度，所以也不会出现X光照射的效果
        for (int iblksloop = 0; iblksloop < mycar->iblks.size(); iblksloop++){
            tmpib = mycar->iblks[iblksloop];
            tmpmb = mycar->mblks[mycar->iblks[iblksloop]->matId];
            tmpvb = mycar->vblks[mycar->iblks[iblksloop]->vtxId];

            if(tmpib->textureCount == 0 && tmpmb->transparency <= 0.1 ){
                gleo::updateMaterial(tmpmb, uni->materialDefault.ambient, uni->materialDefault.diffuse, uni->materialDefault.specular);
                //uni->materialDefault.diffuse = Vector4(0.2, 0.5, 0.8, 0.6);
                uni->materialDefault.diffuse.w = 0.5;
                gleo::draw(tmpvb, tmpib, NULL, NULL , &uni->shaderAdsg);
            }
        }
        //====第三轮，绘制车牌。
        for (int iblksloop = 0; iblksloop < mycar->iblks.size(); iblksloop++){
            tmpib = mycar->iblks[iblksloop];
            tmpmb = mycar->mblks[mycar->iblks[iblksloop]->matId];
            tmpvb = mycar->vblks[mycar->iblks[iblksloop]->vtxId];

            if(tmpib->textureCount > 0){
                gleo::updateMaterial(tmpmb, uni->materialDefault.ambient, uni->materialDefault.diffuse, uni->materialDefault.specular);
                uni->materialDefault.diffuse.w = 0.4;
                gleo::draw(tmpvb, tmpib, NULL, tmpib->textureIds , &uni->shaderPU);
            }
        }
    }
    else{
        //====第一轮，绘制不透明部分
        for (int iblksloop = 0; iblksloop < mycar->iblks.size(); iblksloop++){
            tmpib = mycar->iblks[iblksloop];
            tmpmb = mycar->mblks[mycar->iblks[iblksloop]->matId];
            tmpvb = mycar->vblks[mycar->iblks[iblksloop]->vtxId];

            if(tmpib->textureCount == 0 && tmpmb->transparency <= 0.1 ){
                gleo::updateMaterial(tmpmb, uni->materialDefault.ambient, uni->materialDefault.diffuse, uni->materialDefault.specular);
                gleo::draw(tmpvb, tmpib, NULL, NULL , &uni->shaderAdsg);
            }
        }
        //====第二轮，绘制半透明的玻璃等部件
        for (int iblksloop = 0; iblksloop < mycar->iblks.size(); iblksloop++){
            tmpib = mycar->iblks[iblksloop];
            tmpmb = mycar->mblks[mycar->iblks[iblksloop]->matId];
            tmpvb = mycar->vblks[mycar->iblks[iblksloop]->vtxId];

            if(tmpib->textureCount == 0 && tmpmb->transparency > 0.1 ){
                tmpmb->transparency = 0.5;
                gleo::updateMaterial(tmpmb, uni->materialDefault.ambient, uni->materialDefault.diffuse, uni->materialDefault.specular);
                gleo::draw(tmpvb, tmpib, NULL, NULL , &uni->shaderAdsg);
            }
        }
        //====第三轮，绘制车牌。
        //shaderPU.use();
        for (int iblksloop = 0; iblksloop < mycar->iblks.size(); iblksloop++){
            tmpib = mycar->iblks[iblksloop];
            tmpmb = mycar->mblks[mycar->iblks[iblksloop]->matId];
            tmpvb = mycar->vblks[mycar->iblks[iblksloop]->vtxId];

            if(tmpib->textureCount > 0){
                gleo::updateMaterial(tmpmb, uni->materialDefault.ambient, uni->materialDefault.diffuse, uni->materialDefault.specular);
                gleo::draw(tmpvb, tmpib, NULL, tmpib->textureIds , &uni->shaderPU);
            }
        }

    }

    return;
}

void RendererTdp::drawTune(int item, int cam)
{
    int t_CurItem = item;
    int t_CurCam = cam;

    //设置SHADER
    //shaderCamAvm->use();

    //画图--Org背景图
    uni->avm.uvAdpter = uni->avm.uvAdpterValue[t_CurCam];
    uni->avm.cambalance.blankAndCamera.z = 4.0;

    //Org图像
    if (t_CurItem == mVs->TUNING_ITEM_CAMPOS || \
            t_CurItem == mVs->TUNING_ITEM_CENTER || \
            t_CurItem==mVs->TUNING_ITEM_MARK){
        gleo::draw(&mVs->tVbOrg[t_CurCam], &mVs->tIbOrg, NULL, pTxtrAvm[t_CurCam], uni->shaderAvm);
    }
    //POS网格
    if (t_CurItem == mVs->TUNING_ITEM_CAMPOS){
        uni->shaderP.use();
        gleo::draw(mVs->vtxmapblk[t_CurCam], mVs->idxblk[t_CurCam], NULL, NULL, &uni->shaderP, GL_LINES);
    }
    //Mark三角
    else if (t_CurItem == mVs->TUNING_ITEM_MARK){

        uni->shaderPC.use();
        mVs->createMarkCrossVbIb(t_CurCam);
        gleo::draw(&mVs->tVbMarkCross, &mVs->tIbMarkCross, NULL, NULL, &uni->shaderPC, GL_LINES);

        uni->shaderPUC.use();
        ui_mark->updateplace(mVs->getOrgMark(t_CurCam));
        gleo::draw(&ui_mark->vb, &ui_mark->ib, NULL, ui_mark->ib.textureIds, &uni->shaderPUC);
    }
    //中心点和圆
    else if (t_CurItem == mVs->TUNING_ITEM_CENTER){

        uni->shaderPC.use();
        if(mVs->createCenterVbIb(t_CurCam)){
            gleo::draw(&mVs->tVbCircle, &mVs->tIbCircle, NULL, NULL, &uni->shaderPC, GL_TRIANGLES);
        }
    }

    return;
}

void RendererTdp::drawUi()
{
    // 画按键界面===================================================================
    ui_virtual->update();

    uni->shaderPUC.use();
    if(disMode == 0){
        gleo::draw(&ui_p1->vb, &ui_p1->ib, NULL, ui_p1->ib.textureIds, &uni->shaderPUC);
    }
    else {
        gleo::draw(&ui_virtual->vb, &ui_virtual->ib, NULL, ui_virtual->ib.textureIds, &uni->shaderPUC);
    }
    return;
}

bool RendererTdp::config(int cmd)
{
    switch(cmd){
        case (int)TdpanoCmd::CONF_ORG_BUTTON_ON:    ui_p1->enOrgBtn(true);  break;
        case (int)TdpanoCmd::CONF_ORG_BUTTON_OFF:   ui_p1->enOrgBtn(false);  break;
        case (int)TdpanoCmd::CONF_3D_BUTTON_ON:     ui_p1->en3dBtn(true);   break;
        case (int)TdpanoCmd::CONF_3D_BUTTON_OFF:    ui_p1->en3dBtn(false);  break;
        case (int)TdpanoCmd::CONF_MIRROR_BUTTON_ON: ui_p1->enMirrorBtn(true);   break;
        case (int)TdpanoCmd::CONF_MIRROR_BUTTON_OFF:    ui_p1->enMirrorBtn(false);  break;
        case (int)TdpanoCmd::CONF_UI_OFF:           ui_p1->show();  break;
        case (int)TdpanoCmd::CONF_UI_ON:            ui_p1->hide();  break;
        case (int)TdpanoCmd::CONF_SLIDE_MIRROR_ON:      ctrl.slideMirrorOn = true; break;
        case (int)TdpanoCmd::CONF_SLIDE_MIRROR_OFF:     ctrl.slideMirrorOn = false; break;

        case (int)TdpanoCmd::CONF_LINE_TRAIL_ON:      ctrl.lineTrailOn = true; break;
        case (int)TdpanoCmd::CONF_LINE_TRAIL_OFF:     ctrl.lineTrailOn = false; break;
        case (int)TdpanoCmd::CONF_LINE_REAR_ON:      ctrl.lineRearOn = true; break;
        case (int)TdpanoCmd::CONF_LINE_REAR_OFF:     ctrl.lineRearOn = false; break;
        case (int)TdpanoCmd::CONF_LINE_RADAR_ON:      ctrl.lineRadarOn = true; break;
        case (int)TdpanoCmd::CONF_LINE_RADAR_OFF:     ctrl.lineRadarOn = false; break;

        default :break;
    }  
 
    return true;
}


void RendererTdp::turnCamera(int item, int cam)
{
     if (item == (int)TdpanoCmd::TUNE_ITEMCENTER || item == (int)TdpanoCmd::TUNE_ITEMMARK)
     {
         camera->turnTune(8 + 0);
     }
     else if (item == (int)TdpanoCmd::TUNE_ITEMCAMPOS)
     {
         camera->turnTune( 8 + 1 + item);
     }
     return;
}


bool RendererTdp::process(int cmd){
    std::string errorinfo;

    bool validPress = true;
    switch (cmd){
    case (int)TdpanoCmd::NULLCMD:
        validPress = false;
        break;

    case (int)TdpanoCmd::P2_RETURN:
#ifdef ANDROID
        system("sync");
#endif
        ui_virtual = ui_p1;
        //initial(errorinfo);
        reloadVs();
        disMode = 0;
        viewPortChange(4);
//		emit sendU3Cmd(CMD_U3_STARTLOOP);
        break;
    case (int)TdpanoCmd::P2_SET0:
        mVs->calcHandMark(1.5);
        mVs->recreateUvLever();
        ui_virtual = ui_tune;
        ui_tune->extraBlankSize(mVs->getBlankWidth(), mVs->getBlankHeight());
        break;
    case (int)TdpanoCmd::P2_SET1:
        ui_virtual = ui_auto;
        ui_auto->extraBlankSize(mVs->getBlankWidth(), mVs->getBlankHeight());
        //opera.tmpCmd = 1;
        break;
    case (int)TdpanoCmd::P2_SET2:
        //ui_virtual = ui_tune;
        //opera.isAutoCalib = true;
        //opera.tmpCmd = 2;   
        break;
    case (int)TdpanoCmd::P2_SET3:
        mVs->calcHandMark(1.5);
        mVs->recreateUvLever();
        mVs->updateUv();
        //ui_virtual = ui_tune;
        break;  
    case (int)TdpanoCmd::AUTO_RETURN:
        ui_virtual = ui_p2;
        break;   
    case (int)TdpanoCmd::AUTO_DO:
        opera.tmpCmd = 1; //启动自动拼接动作
        break; 
    // case (int)TdpanoCmd::AUTO_SAVE: //挪到后边跟 TUNE_SAVE 放到一起了
    //     //ui_virtual = ui_p2;
    //     break;                     
    case (int)TdpanoCmd::TUNE_RETURN:
        ui_virtual = ui_p2;
        break;
// 	case IDX_TUNING:
// 		break;
    case (int)TdpanoCmd::TUNE_CAM0:
        mVs->setChkCam(0);
        turnCamera(mVs->getChkItem(), mVs->getChkCam());//camera->turnTune(mVs->getChkItem(), mVs->getChkCam());
        break;
    case (int)TdpanoCmd::TUNE_CAM1:
        mVs->setChkCam(1);
        turnCamera(mVs->getChkItem(), mVs->getChkCam());//camera->turnTune(mVs->getChkItem(), mVs->getChkCam());
        break;
    case (int)TdpanoCmd::TUNE_CAM2:
        mVs->setChkCam(2);
        turnCamera(mVs->getChkItem(), mVs->getChkCam());//camera->turnTune(mVs->getChkItem(), mVs->getChkCam());
        break;
    case (int)TdpanoCmd::TUNE_CAM3:
        mVs->setChkCam(3);
        turnCamera(mVs->getChkItem(), mVs->getChkCam());//camera->turnTune(mVs->getChkItem(), mVs->getChkCam());
        break;
    case (int)TdpanoCmd::TUNE_ITEMCENTER:
        mVs->setChkItem(mVs->TUNING_ITEM_CENTER);
        mVs->setChkCam(0);
        turnCamera(mVs->getChkItem(), mVs->getChkCam());//camera->turnTune(mVs->getChkItem(), mVs->getChkCam());
        break;
    case (int)TdpanoCmd::TUNE_ITEMCAMPOS:
        mVs->setChkItem(mVs->TUNING_ITEM_CAMPOS);
        mVs->setChkCam(0);
        turnCamera(mVs->getChkItem(), mVs->getChkCam());//camera->turnTune(mVs->getChkItem(), mVs->getChkCam());
        break;
    case (int)TdpanoCmd::TUNE_ITEMMARK:
        mVs->setChkItem(mVs->TUNING_ITEM_MARK);
        mVs->setChkCam(0);
        turnCamera(mVs->getChkItem(), mVs->getChkCam());//camera->turnTune(mVs->getChkItem(), mVs->getChkCam());
        break;
    case (int)TdpanoCmd::TUNE_ITEMNULL:
        mVs->setChkItem(mVs->TUNING_ITEM_NULL);
        break;
    case (int)TdpanoCmd::TUNE_NEXTMARK:
        mVs->nextChkMark();
        break;
    case (int)TdpanoCmd::TUNE_DENSE:
        mVs->adjTuneDense();
        break;
    case (int)TdpanoCmd::TUNE_NEXTCAM:
        mVs->nextChkCam();
        turnCamera(mVs->getChkItem(), mVs->getChkCam());//camera->turnTune(mVs->getChkItem(), mVs->getChkCam());
        break;
    case (int)TdpanoCmd::TUNE_NEXTITEM:
        mVs->nextChkItem();// toTuneVp();
        break;
    case (int)TdpanoCmd::TUNE_CHANGEDIS:
        mVs->changeDis();
        break;
    case (int)TdpanoCmd::TUNE_XP:
        mVs->adjValue(0); mVs->updateUv(); break;
    case (int)TdpanoCmd::TUNE_XN:
        mVs->adjValue(1); mVs->updateUv(); break;
    case (int)TdpanoCmd::TUNE_YP:
        mVs->adjValue(2); mVs->updateUv(); break;
    case (int)TdpanoCmd::TUNE_YN:
        mVs->adjValue(3); mVs->updateUv(); break;
    case (int)TdpanoCmd::TUNE_ZP:
        mVs->adjValue(4); mVs->updateUv(); break;
    case (int)TdpanoCmd::TUNE_ZN:
        mVs->adjValue(5); mVs->updateUv(); break;
    case (int)TdpanoCmd::TUNE_WP3:
        mVs->adjBlankRegion(0, 0.2); 
        mVs->calcHandMark(1.5); 
        mVs->copyMdlMark(); 
        mVs->updateMesh();
        ui_tune->extraBlankSize(mVs->getBlankWidth(), mVs->getBlankHeight());
        ui_auto->extraBlankSize(mVs->getBlankWidth(), mVs->getBlankHeight());
        break;
    case (int)TdpanoCmd::TUNE_WP2:
        mVs->adjBlankRegion(0, 0.01);
        mVs->calcHandMark(1.5); 
        mVs->copyMdlMark(); 
        mVs->updateMesh();
        ui_tune->extraBlankSize(mVs->getBlankWidth(), mVs->getBlankHeight());
        ui_auto->extraBlankSize(mVs->getBlankWidth(), mVs->getBlankHeight());
        break;
    case (int)TdpanoCmd::TUNE_WP1:
        mVs->adjBlankRegion(1, 0.01);
        mVs->calcHandMark(1.5); 
        mVs->copyMdlMark(); 
        mVs->updateMesh();
        ui_tune->extraBlankSize(mVs->getBlankWidth(), mVs->getBlankHeight());
        ui_auto->extraBlankSize(mVs->getBlankWidth(), mVs->getBlankHeight());
        break;
    case (int)TdpanoCmd::TUNE_WP0:
        mVs->adjBlankRegion(1, 0.2); 
        mVs->calcHandMark(1.5); 
        mVs->copyMdlMark(); 
        mVs->updateMesh();
        ui_tune->extraBlankSize(mVs->getBlankWidth(), mVs->getBlankHeight());
        ui_auto->extraBlankSize(mVs->getBlankWidth(), mVs->getBlankHeight());
        break;
    case (int)TdpanoCmd::TUNE_HP3:
        mVs->adjBlankRegion(2, 0.2); 
        mVs->calcHandMark(1.5); 
        mVs->copyMdlMark(); 
        mVs->updateMesh();
        ui_tune->extraBlankSize(mVs->getBlankWidth(), mVs->getBlankHeight());
        ui_auto->extraBlankSize(mVs->getBlankWidth(), mVs->getBlankHeight());
        break;
    case (int)TdpanoCmd::TUNE_HP2:
        mVs->adjBlankRegion(2, 0.01); 
        mVs->calcHandMark(1.5); 
        mVs->copyMdlMark(); 
        mVs->updateMesh();
        ui_tune->extraBlankSize(mVs->getBlankWidth(), mVs->getBlankHeight());
        ui_auto->extraBlankSize(mVs->getBlankWidth(), mVs->getBlankHeight());
        break;
    case (int)TdpanoCmd::TUNE_HP1:
        mVs->adjBlankRegion(3, 0.01); 
        mVs->calcHandMark(1.5); 
        mVs->copyMdlMark(); 
        mVs->updateMesh();
        ui_tune->extraBlankSize(mVs->getBlankWidth(), mVs->getBlankHeight());
        ui_auto->extraBlankSize(mVs->getBlankWidth(), mVs->getBlankHeight());
        break;
    case (int)TdpanoCmd::TUNE_HP0:
        mVs->adjBlankRegion(3, 0.2); 
        mVs->calcHandMark(1.5); 
        mVs->copyMdlMark(); 
        mVs->updateMesh();
        ui_tune->extraBlankSize(mVs->getBlankWidth(), mVs->getBlankHeight());
        ui_auto->extraBlankSize(mVs->getBlankWidth(), mVs->getBlankHeight());
        break;
#ifdef FUNC_GENERAL        
    case (int)TdpanoCmd::DOCK_DIS0:
        viewPortChange(0);  break;
    case (int)TdpanoCmd::DOCK_DIS1:
        viewPortChange(1);  break;
    case (int)TdpanoCmd::DOCK_DIS2:
        viewPortChange(2);  break;
    case (int)TdpanoCmd::DOCK_DIS3:
        viewPortChange(3);  break;
    case (int)TdpanoCmd::DOCK_DIS4:
        viewPortChange(4);  break;
    case (int)TdpanoCmd::DOCK_DIS6:
        viewPortChange(6);  break;
    case (int)TdpanoCmd::DOCK_DIS7:
        viewPortChange(7);  break;
    case (int)TdpanoCmd::DOCK_DIS8:
        viewPortChange(8);  break;
    case (int)TdpanoCmd::DOCK_DIS9:
        viewPortChange(9);  break;  
    case (int)TdpanoCmd::DOCK_DIS10:
        viewPortChange(10);  break;                             
    case (int)TdpanoCmd::DOCK_SETTING:
#ifndef VERSION_MAL_FUNCTION    
        disMode = 1;
        CurViewPort = 4;
        ui_virtual = ui_p2;
#endif     
        break;   
#endif

#ifdef FUNC_CLIENT_FH
    case (int)TdpanoCmd::DOCK_DIS0:
        viewPortChange_client_fuhuang(0); cameraAdaption_client_fuhuang(0); break;
    case (int)TdpanoCmd::DOCK_DIS1:
        viewPortChange_client_fuhuang(1); cameraAdaption_client_fuhuang(1);break;
    case (int)TdpanoCmd::DOCK_DIS2:
        viewPortChange_client_fuhuang(2); cameraAdaption_client_fuhuang(2);break;
    case (int)TdpanoCmd::DOCK_DIS3:
        viewPortChange_client_fuhuang(3); cameraAdaption_client_fuhuang(3);break;
    case (int)TdpanoCmd::DOCK_DIS4:
        viewPortChange_client_fuhuang(4); cameraAdaption_client_fuhuang(4);break;
    case (int)TdpanoCmd::DOCK_DIS5:
        viewPortChange_client_fuhuang(5); cameraAdaption_client_fuhuang(5);break;
    case (int)TdpanoCmd::DOCK_SETTING:
#ifndef VERSION_MAL_FUNCTION    
        disMode = 1;
        cameraAdaption_client_fuhuang(6);
        CurViewPort = 4;
        ui_virtual = ui_p2;
#endif        
        break;
#endif // DEBUG
    case (int)TdpanoCmd::DOCK_SYSRETURN:
        switchTex();
//        if (bVideoOn){
//            emit startVideo();
//            bVideoOn = false;
//        }
//        else{
//            emit endVideo();
//            bVideoOn = true;
//        }
        break;
    case (int)TdpanoCmd::AUTO_SAVE:    
    case (int)TdpanoCmd::TUNE_SAVE:
        ofn = strStoragePath;
        mVs->saveMergerData(ofn.append("/").append(strFileMerger).c_str());
        ofn = strStoragePath;
        mVs->saveMountData(ofn.append("/").append(strFileMount).c_str());
        break;
    case (int)TdpanoCmd::TUNE_DONE:
        //DBG("CMD_TUNE_DONE");
        break;
    default:
        validPress = false;
        break;
    }
    return validPress;
}

void RendererTdp::keyPressEvent(char key){
        int mykey = (int)TdpanoCmd::NULLCMD;

        switch (key){
        case 'W':
            camera->vp3d.rotate(-2.0, 0, 0); break;
        case 'S':
            camera->vp3d.rotate(2.0, 0, 0);  break;
        case 'A':
            camera->vp3d.rotate(0, 0, 2.0);  break;
        case 'D':
            camera->vp3d.rotate(0, 0, -2.0); break;
        case 'Q':
            camera->vp3d.trans(0,0, 0.2);   break;
        case 'E':
            camera->vp3d.trans(0,0,-0.2);  break;
        case 'w':
            mykey = (int)TdpanoCmd::TUNE_YP; break;
        case 's':
            mykey = (int)TdpanoCmd::TUNE_YN; break;
        case 'a':
            mykey = (int)TdpanoCmd::TUNE_XN; break;
        case 'd':
            mykey = (int)TdpanoCmd::TUNE_XP; break;
        case 'q':
            mykey = (int)TdpanoCmd::TUNE_ZP; break;
        case 'e':
            mykey = (int)TdpanoCmd::TUNE_ZN; break;
        case 'o':
            mykey = (int)TdpanoCmd::TUNE_SAVE; break;
        case 'i':
            mykey = (int)TdpanoCmd::TUNE_LOAD; break;
        case 'h':
            mykey = (int)TdpanoCmd::TUNE_CHANGEDIS; break;
        case 'j':
            mykey = (int)TdpanoCmd::TUNE_NEXTITEM; break;
        case 'k':
            mykey = (int)TdpanoCmd::TUNE_NEXTCAM; break;
        case 'l':
            mykey = (int)TdpanoCmd::TUNE_NEXTMARK; break;
        case '0':
            mykey = (int)TdpanoCmd::DOCK_DIS0;break;
        case '1':
            mykey = (int)TdpanoCmd::DOCK_DIS1;break;
        case '2':
            mykey = (int)TdpanoCmd::DOCK_DIS2;break;
        case '3':
            mykey = (int)TdpanoCmd::DOCK_DIS3;break;
        case '4':
            mykey = (int)TdpanoCmd::DOCK_DIS4;break;
        case '5':
            mykey = (int)TdpanoCmd::DOCK_DIS5;break;

        case 'z':
            mykey = (int)TdpanoCmd::DOCK_SYSRETURN;break;
//        case 'x':
//        case 'c':
//        case 'v':
        case 'b':
            bAhead = !bAhead; break;
        case 'n':
            moveAngle -= 0.5; std::cout << "ange=" << moveAngle << std::endl; break;
        case 'm':
            moveAngle += 0.5; std::cout << "ange=" << moveAngle << std::endl; break;
        default:
            break;
        }

        process(mykey);
}

/// button 按下的时候并不处理实际的工作
/// 所有的处理工作都放到 button release的时候来处理， 否则键盘感受很差，一碰变了，缺乏按下弹起的感受
void RendererTdp::mouseReleaseEvent(int x,int y)
{
    ui_virtual->mouseReleaseEvent();

    if(WndRet != NULL){
        process(WndRet);
        WndRet = NULL;
    }

    if(VpRet != -1){
        viewPortChange(VpRet);
        VpRet = -1;
    }

    pressResponding = false;
    checkSlideAction = true;
    deepChanging = false;
    viewportChanging = false;
}

void RendererTdp::mousePressEvent(int x, int y)
{
    //int rt;
    lastx = x;
    lasty = y;
    startx = x;
    starty = y;

    WndRet = ui_virtual->mousePressEvent(float(x)/scrn.w, float(scrn.h - y)/scrn.h);
    if(WndRet != NULL){
        //process(WndRet);
        pressResponding = true;
        return;
    }
    if(ctrl.en2DPick){
        VpRet = viewPortPick((float)x, (float)y);
    }else{
        VpRet = -1;
    }

    if(VpRet != -1){
        pressResponding = true;
        return;
    }

    return;
}

//Qt:鼠标左键Move
//Android: 单指Move
void RendererTdp::mouseMoveEventLB(int x, int y){

    //if (ui_virtual->mouseResponding())return;
    if(pressResponding)return;
    GLfloat dx = GLfloat(x - lastx);// / scrn.w;
    GLfloat dy = GLfloat(y - lasty);// / scrn.h;

    Vector3 p;
    Vector3 r;

    if(disMode == 1){ //模式1，调试模式， 没有UI交互，单纯切换视角
        camera->vp3d.rotate(-180*dy/scrn.h, 0, -180*dx/scrn.w);
        //camera->clamp3d();
    }
    else if(CurViewPort <= 3){ //Org+2D视图模式，
        if(pressIn2D){ //滑动2D画面
            if(ctrl.slide2dOn){
                //camera->vp2d.customTrans2D(12*dx/scrn.w, 12*dy/scrn.h);
                camera->clamp2d();
            }
            // else if(ctrl.slide2dOnY){
            //     //camera->vp2d.customTrans2D(0, 12*dy/scrn.h);
            //     camera->clamp2d();
            // }
//            p = camera->vp2d.pos;
//            r = camera->vp2d.rot;
//            DBG("(%f,%f,%f):(%f,%f,%f)", p.x,p.y,p.z,  r.x, r.y, r.z);
        }
        else{ //切换Org 摄像头
            if(ctrl.slideOrgOn){
                viewPortMove(dx, dy);
            }
        }
    }
    else if(CurViewPort == 4 || CurViewPort == 9){
        camera->vp3d.rotate(-180*dy/scrn.h, 0, -180*dx/scrn.w);
        camera->clamp3d();
//        p = camera->vp3d.pos;
//        r = camera->vp3d.rot;
//        DBG("(%f,%f,%f):(%f,%f,%f)", p.x,p.y,p.z,  r.x, r.y, r.z);
    }
    else if(CurViewPort == 6 || CurViewPort == 10){
        camera->vpmir.rotate(-180*dy/scrn.h, 0, -180*dx/scrn.w);
        camera->clampmir();
//        p = camera->vpmir.pos;
//        r = camera->vpmir.rot;
//        DBG("(%f,%f,%f):(%f,%f,%f)", p.x,p.y,p.z,  r.x, r.y, r.z);
    }

    lastx = x;
    lasty = y;
}

//Qt:鼠标右键Move
//Android: 双指Move
void RendererTdp::mouseMoveEventRB(int x, int y){

    //if (ui_virtual->mouseResponding())return;
    if(pressResponding)return;
    //static

    GLfloat dx = GLfloat(x - lastx);// / scrn.w;
    GLfloat dy = GLfloat(y - lasty);// / scrn.h;

    if(fabs(dy) < fabs(dx)){
        if(!viewportChanging){
            deepChanging = true;
            Vector3 p;
            Vector3 r;
            if(CurViewPort <= 3){
                camera->vp2d.trans(0,0,-8*dx/scrn.w);
                //camera->vp2d.trans(0, -8*dy/scrn.h, -8*dx/scrn.w);
                camera->clamp2d();
//                p = camera->vp2d.pos;
//                r = camera->vp2d.rot;
//                DBG("(%f,%f,%f):(%f,%f,%f)", p.x,p.y,p.z,  r.x, r.y, r.z);
            }
            else if(CurViewPort == 4){
                camera->vp3d.trans(0, 0, -18*dx/scrn.w);//-18*dy, -18*dx);
                //显示模式为0， 需要对3D 钳位， 调试状态不钳位
                if(disMode == 0){
                    camera->clamp3d();
                }
//                p = camera->vp3d.pos;
//                r = camera->vp3d.rot;
//                DBG("(%f,%f,%f):(%f,%f,%f)", p.x,p.y,p.z,  r.x, r.y, r.z);
            }
            else if(CurViewPort == 6){
                camera->vpmir.trans(0, 0, -18*dx/scrn.w);//-18*dy, -18*dx);
                camera->clampmir();
//                p = camera->vpmir.pos;
//                r = camera->vpmir.rot;
//                DBG("(%f,%f,%f):(%f,%f,%f)", p.x,p.y,p.z,  r.x, r.y, r.z);
            }
        }
    }
    else{
        if(!deepChanging){
            if(ctrl.slide3dOn || ctrl.slideMirrorOn){
                viewportChanging = true;
                viewPortMove2(dx, dy);
            }
        }
    }

    lastx = x;
    lasty = y;
}

bool RendererTdp::checkMdoTexture(MdObject *ob)
{
    if(ob == NULL){
        return false;
    }

    string file;
    MaterialBlock *mb;
    Mat mat;
    Mat mat1;

    for(int i=0; i< ob->mblks.size();i++){
        mb = ob->mblks[i];
        //

        if(!mb->map_kd.empty() && mb->map_kd.size() > 5){

            file = strStoragePath;
            //file.append("/").append(mb->map_kd);
            file.append("/").append("licplate0.png");
            //强制修改车牌纹理文件，后边可能会出错。

            mat = cv::imread(file.c_str(), 1);


            if(!mat.data){
                LOGE("checkMdoTexture().read %s failed",file.c_str());
                continue;
            }
            else{
                LOGI("checkModTexture().read %s", file.c_str());
                //LOGE("load mod texture.\n");
            }

            for (int i = 0; i < mat.rows; ++i) {
                for (int j = 0; j < mat.cols; ++j) {
                    Vec3b& pix = mat.at<Vec3b>(i, j); //指针或引用
                    std::swap(pix[0], pix[2]);
                }
            }

            cv::flip(mat, mat1, 0);

            mb->textureid = gleo::createTexture2D();
            GLint _t = mb->textureid;
            gleo::texBindRgb(_t,  mat1.data, mat1.cols, mat1.rows);
        }
    }

    //LOGE("mb tst.\n");

    for(int i=0;i<ob->iblks.size();i++){
        int _matid = ob->iblks[i]->matId;
        if(!ob->mblks[_matid]->map_kd.empty() && ob->mblks[_matid]->textureid > 0){
            ob->iblks[i]->setTexture(ob->mblks[_matid]->textureid);
        }
    }

    return true;
}
