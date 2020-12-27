
#include "qopenglwidgettdp.h"

#include "renderer/tdpanocmd.h"

#include "leobase/gleocamera.h"
#include "leobase/imgbmp.h"
#include "leobase/gleo.h"
#include "leobase/common_leo.h"

//#include <iostream>
//#include <sstream>
#include <iomanip>
#include <math.h>
#include <cmath>
#include <algorithm>
#include <string>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <QTimer>
#include <QPoint>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QPainter>
#include <QMap>



#include "opencv2/opencv.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
//#include <opencv2/xfeatures2d/nonfree.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/imgproc/types_c.h>
//#include "libuart/sixaxis.h"


#ifdef OLD_OPENCV3X

#else
#define CV_CAP_PROP_FRAME_WIDTH CAP_PROP_FRAME_WIDTH
#define CV_CAP_PROP_FRAME_HEIGHT CAP_PROP_FRAME_HEIGHT
#define CV_CAP_PROP_FOURCC  CAP_PROP_FOURCC
#endif

using namespace cv;

Mat capyuv[4];
Mat capOrg;
//Mat capI420;//(1080, 1920, CV_8UC1);
Mat cap420[4] ={
    Mat(1080,1280,CV_8UC1),
    Mat(1080,1280,CV_8UC1),
    Mat(1080,1280,CV_8UC1),
    Mat(1080,1280,CV_8UC1)
} ;

//Mat capIm420(1080, 1280, CV_8UC1);
//Mat capIm421(1080, 1280, CV_8UC1);
//Mat capIm422(1080, 1280, CV_8UC1);
//Mat capIm423(1080, 1280, CV_8UC1);
Mat capIm4ex(1080, 1280, CV_8UC1);

Rect capRoi(0,0,960,540);

//SixAxis sa;
string devname = "/dev/ttyUSB0";
int fd = -1;
//SAFRAME sadif;


QOpenGLWidgetTdp::QOpenGLWidgetTdp(QWidget *parent)
    : QOpenGLWidget(parent)
{

    bTimerOn = false;
    //mytimer = new QTimer;
    mytimer.setInterval(30);
    mytimer.start();
    bTimerOn = true;
    bVideoOn = false;

    initKeyMap();
    LOGI("wd ini 1\n");
#ifdef linux
   mrender.modiDirectory("/home/tdpano.data");
#endif
    mrender.modiModelFile("truck1.tdo");
    mrender.modiBrpFile("lens-8296-r554.brp");

    if(!mrender.loadBrpFile()){
        LOGE("brp load failed\n");
    }
    if(!mrender.loadMergerFile()){
        LOGE("merger load failed\n");
    }
    if(!mrender.loadMountFile()){
        LOGE("Mount load failed\n");
    }
    if(!mrender.loadModelFile()){
        LOGE("car load failed\n");
    }


    std::string error;
    if(!mrender.initial( error)){
        LOGE("renderer initial error.\n");
    }
    LOGI("wd ini 2\n");

#ifdef linux
   Mat ttemp;
   Mat ttempx(540,960,CV_8UC3);
   ttemp = imread("/home/tdpano.data/pic-1080p-default.jpg", 1);
   cv::resize(ttemp(Rect(0,0,960,540)), ttempx, Size(1280,720));
   cvtColor(ttempx, cap420[0], CV_BGR2YUV_I420);
   cv::resize(ttemp(Rect(960,0,960,540)), ttempx, Size(1280,720));
   cvtColor(ttempx, cap420[1], CV_BGR2YUV_I420);
   cv::resize(ttemp(Rect(0,540,960,540)), ttempx, Size(1280,720));
   cvtColor(ttempx, cap420[2], CV_BGR2YUV_I420);
   cv::resize(ttemp(Rect(960,540,960,540)), ttempx, Size(1280,720));
   cvtColor(ttempx, cap420[3], CV_BGR2YUV_I420);

#endif
}


QOpenGLWidgetTdp::~QOpenGLWidgetTdp()
{ 
    //delete mytimer;
    //delete LastPos;
}

void QOpenGLWidgetTdp::initializeGL()
{
    QSurfaceFormat fmt;
    fmt.setDepthBufferSize(24);
    fmt.setStencilBufferSize(8);
    fmt.setSwapBehavior(fmt.DoubleBuffer);
    setFormat(fmt);
// 	QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
// 	f->glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	initializeOpenGLFunctions();
    glClearColor(0.4f, 0.4f, 0.2f, 0.0f);

    mrender.ctrl.enButton =true;
//    mrender.ctrl.enAllbs = true;
    mrender.ctrl.enAvm2d = true;

    mrender.initGL();

    mrender.setTextureAssemble(false);


    mrender.setTextureIsBuf(false);

    mrender.setTextureType(3);

    mrender.switchInnerDemo(false);


    //connect(&mytimer, SIGNAL(timeout()), this, SLOT(update()), Qt::QueuedConnection);
    connect(&mytimer, SIGNAL(timeout()), this, SLOT(readframe()), Qt::QueuedConnection);

//    fd = sa.saopen(devname.c_str(), 115200,0,8,1,(int)'N'); //打开串口，返回文件描述符
//    if(fd<=0)
//    {
//        printf("%s open failed. stop\n",devname.c_str());
//    }
//    else{
//        printf("%s open ok.\n", devname.c_str());
//    }
//    sa.bgd();

}

void QOpenGLWidgetTdp::readframe()
{
    
    static int loop = 0;
    unsigned char * ddd;
    unsigned char * sss;
    int nLenY;
    int nLenU;

    static bool capstate[4]={true,true,true,true};
    //printf("ok2\n");

    if(loop <= 100000){
        loop ++;

        for(int capcnt=0;capcnt<4;capcnt++){
            if(cap[capcnt].isOpened()){

                ////YUV
                cap[capcnt] >> capyuv[capcnt];
                if(cap420[capcnt].rows == 720 || cap420[capcnt].cols == 1280){
                    capstate[capcnt]=true;
                }
                else{   
                    capstate[capcnt]=false;
                    continue;
                }

                if(loop<4){printf("rtsp[%d]]: %d, %d, %d %d\n", capcnt, capyuv[capcnt].rows, capyuv[capcnt].cols, capyuv[capcnt].channels(), loop);}
                
                                /// YUY2转I420
                nLenY = capyuv[capcnt].rows * capyuv[capcnt].cols ;
                ddd = cap420[capcnt].data;
                sss = capyuv[capcnt].data;

                unsigned char *y,*u,*v;
                y = ddd;
                u = ddd + nLenY;
                v = ddd + nLenY + nLenY/4;

                for (int i = 0; i < capyuv[capcnt].rows / 2; i++){
                    for(int j=0; j < capyuv[capcnt].cols /2; j++){

                        *y++ = *sss++;
                        *u++ = *sss++;
                        *y++ = *sss++;
                        *v++ = *sss++;
                    }
                    for(int j=0; j < capyuv[capcnt].cols /2; j++){

                        *y++ = *sss++;
                        sss++;
                        *y++ = *sss++;
                        sss++;
                    }
                }

                ////NV12
                //cap[capcnt] >> cap420[capcnt];
                
                // if(cap420[capcnt].rows == 1080 || cap420[capcnt].cols == 1280)
                //     {capstate[capcnt]=true;}
                // else
                // {   capstate[capcnt]=false;}

               //if(loop<4){printf("rtsp[%d]]: %d, %d, %d %d\n", capcnt, cap420[capcnt].rows, cap420[capcnt].cols, cap420[capcnt].channels(), loop);}
                
                /// NV12转I420
                // nLenY = cap420[capcnt].rows * cap420[capcnt].cols * 2/3;
                // nLenU = nLenY / 4;

                // memcpy(capIm4ex.data, cap420[capcnt].data + nLenY, nLenU * 2);
                // ddd = cap420[capcnt].data + nLenY;
                // sss = capIm4ex.data;

                // for (int i = 0; i < nLenU; i++){
                //     *(ddd + i) = *(sss+2*i);                    // U
                //     *(ddd + nLenU + i) = *(sss + 2*i + 1);        // V
                // }


            }
        }

//         cvtColor(capIm0 , capIm420,  CV_BGR2YUV_I420);//CV_BGR2YUV_I420);
//         cvtColor(capIm1 , capIm421,  CV_BGR2YUV_I420);//CV_BGR2YUV_I420);

         Vector3 sa_angle = Vector3(0,0,0);//Vector3(sadif.ag[0], sadif.ag[1], sadif、.ag[2]);
         //mrender.update(capI420.data, 1920, 1080, sa_angle);
       mrender.update(capstate[0] ? cap420[0].data : capIm4ex.data,\
                      capstate[1] ? cap420[1].data : capIm4ex.data,\
                      capstate[2] ? cap420[2].data : capIm4ex.data,\
                      capstate[3] ? cap420[3].data : capIm4ex.data,\
                                                     1280, 720, sa_angle);

    }

    update();

}

void QOpenGLWidgetTdp::resizeGL(int width,int height){
    mrender.resize(width,height);
}

void QOpenGLWidgetTdp::paintGL(){
   mrender.drawFrame();
//   emit startVideo();
}

void QOpenGLWidgetTdp::keyPressEvent(QKeyEvent *event)
{
	int keyValue = event->key();
	int keyModi = event->modifiers();
//	int direction = 100;
//    int mykey = (int)TdpanoCmd::NULLCMD;

    char charkey;

    QMap<int, char>::const_iterator it = mKeyMap.find(keyValue);
    if(it == mKeyMap.constEnd()){
        DBG("invalid key\n");
        return;
    }

    if(keyModi == Qt::ShiftModifier){
        charkey = it.value();
    }else{
        charkey = tolower(it.value());
    }

    DBG("%c/0x%2x\n",charkey,charkey);

    if(charkey == 0x6b){
        emit startVideo();
    }

    mrender.keyPressEvent(charkey);

}

void QOpenGLWidgetTdp::mousePressEvent(QMouseEvent *event)
{
    mrender.mousePressEvent(event->x(), event->y());
//    update();
}

void QOpenGLWidgetTdp::mouseReleaseEvent(QMouseEvent *event)
{
    mrender.mouseReleaseEvent(event->x(), event->y());
//    update();
}

void QOpenGLWidgetTdp::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        mrender.mouseMoveEventLB(event->x(),event->y());
    }
    else if(event->buttons() & Qt::RightButton)
    {
        mrender.mouseMoveEventRB(event->x(),event->y());
    }

//    update();
}

void QOpenGLWidgetTdp::mouseDoubleClickEvent(QMouseEvent *event)
{
    mousePressEvent(event);
    //emit startVideo();
    return;
}


void QOpenGLWidgetTdp::setSourceMode(int mode)
{
    inputMode = mode;
    return;
}

void QOpenGLWidgetTdp::setSourceRtsp(int n, string s)
{
    switch(n){
        case 0:
            cap[0].open(s, CAP_GSTREAMER);
            break;
        case 1:
            cap[1].open(s, CAP_GSTREAMER);
            break;
        case 2:
            cap[2].open(s, CAP_GSTREAMER);
            break;
        case 3:
            cap[3].open(s, CAP_GSTREAMER);
            break;
        default:
            break;
    }
    return;
}

void QOpenGLWidgetTdp::showPic(const void *bufaddr, int width, int height){

}

void QOpenGLWidgetTdp::tex4CamUpdate(unsigned char* buf0, unsigned char* buf1, unsigned char* buf2, unsigned char* buf3)
{
	return;
}

void QOpenGLWidgetTdp::onTimerOut()
{
    static clock_t tp,tn;

    tp = clock();
    DBG("%3.3f ms\n", (tp - tn)/1000.0);
    tn = clock();
//	vpMove();
//	update();

}

void QOpenGLWidgetTdp::drawText(int xpos, int ypos, char* str)
{
//	QPainter painter(this);
//	QString mystr = QString(str);
//	painter.setPen(Qt::white);
//	painter.setFont(QFont("Helvetica", 8));
////	painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
//	painter.drawText(xpos, ypos, mystr); // z = pointT4.z + distOverOp / 4
//	painter.end();
}

void QOpenGLWidgetTdp::setCameraTexId(int id0, int id1, int id2, int id3)
{
    //mrender.setTexId2Mesh((GLuint)id0, (GLuint)id1, (GLuint)id2, (GLuint)id3);
//    update();
 }

void QOpenGLWidgetTdp::cameraTexUpdated()
{
//    update();
}

void QOpenGLWidgetTdp::initKeyMap()
{
        mKeyMap.insert(Qt::Key_Left,0x25);
        mKeyMap.insert(Qt::Key_Up,0x26);
        mKeyMap.insert(Qt::Key_Right,0x27);
        mKeyMap.insert(Qt::Key_Down,0x28);
        mKeyMap.insert(Qt::Key_Backspace,0x08);
        mKeyMap.insert(Qt::Key_Tab,0x09);
        mKeyMap.insert(Qt::Key_Clear,0x0C);
        mKeyMap.insert(Qt::Key_Return,0x0D);
        mKeyMap.insert(Qt::Key_Enter,0x0D);
        mKeyMap.insert(Qt::Key_Shift,0x10);
        mKeyMap.insert(Qt::Key_Control,0x11);
        mKeyMap.insert(Qt::Key_Alt,0x12);
        mKeyMap.insert(Qt::Key_Pause,0x13);
        mKeyMap.insert(Qt::Key_CapsLock,0x14);
        mKeyMap.insert(Qt::Key_Escape,0x1B);
        mKeyMap.insert(Qt::Key_Space,0x20);
        mKeyMap.insert(Qt::Key_PageUp,0x21);
        mKeyMap.insert(Qt::Key_PageDown,0x22);
        mKeyMap.insert(Qt::Key_End,0x23);
        mKeyMap.insert(Qt::Key_Home,0x24);
        mKeyMap.insert(Qt::Key_Select,0x29);
        mKeyMap.insert(Qt::Key_Print,0x2A);
        mKeyMap.insert(Qt::Key_Execute,0x2B);
        mKeyMap.insert(Qt::Key_Printer,0x2C);
        mKeyMap.insert(Qt::Key_Insert,0x2D);
        mKeyMap.insert(Qt::Key_Delete,0x2E);
        mKeyMap.insert(Qt::Key_Help,0x2F);
        mKeyMap.insert(Qt::Key_0,0x30);
        mKeyMap.insert(Qt::Key_ParenRight,0x30); // )
        mKeyMap.insert(Qt::Key_1,0x31);
        mKeyMap.insert(Qt::Key_Exclam,0x31); // !
        mKeyMap.insert(Qt::Key_2,0x32);
        mKeyMap.insert(Qt::Key_At,0x32); // @
        mKeyMap.insert(Qt::Key_3,0x33);
        mKeyMap.insert(Qt::Key_NumberSign,0x33); // #
        mKeyMap.insert(Qt::Key_4,0x34);
        mKeyMap.insert(Qt::Key_Dollar,0x34); // $
        mKeyMap.insert(Qt::Key_5,0x35);
        mKeyMap.insert(Qt::Key_Percent,0x35); // %
        mKeyMap.insert(Qt::Key_6,0x36);
        mKeyMap.insert(Qt::Key_AsciiCircum,0x36); // ^
        mKeyMap.insert(Qt::Key_7,0x37);
        mKeyMap.insert(Qt::Key_Ampersand,0x37); // &
        mKeyMap.insert(Qt::Key_8,0x38);
        mKeyMap.insert(Qt::Key_Asterisk,0x38); // *
        mKeyMap.insert(Qt::Key_9,0x39);
        mKeyMap.insert(Qt::Key_ParenLeft,0x39); // (
        mKeyMap.insert(Qt::Key_A,0x41);
        mKeyMap.insert(Qt::Key_B,0x42);
        mKeyMap.insert(Qt::Key_C,0x43);
        mKeyMap.insert(Qt::Key_D,0x44);
        mKeyMap.insert(Qt::Key_E,0x45);
        mKeyMap.insert(Qt::Key_F,0x46);
        mKeyMap.insert(Qt::Key_G,0x47);
        mKeyMap.insert(Qt::Key_H,0x48);
        mKeyMap.insert(Qt::Key_I,0x49);
        mKeyMap.insert(Qt::Key_J,0x4A);
        mKeyMap.insert(Qt::Key_K,0x4B);
        mKeyMap.insert(Qt::Key_L,0x4C);
        mKeyMap.insert(Qt::Key_M,0x4D);
        mKeyMap.insert(Qt::Key_N,0x4E);
        mKeyMap.insert(Qt::Key_O,0x4F);
        mKeyMap.insert(Qt::Key_P,0x50);
        mKeyMap.insert(Qt::Key_Q,0x51);
        mKeyMap.insert(Qt::Key_R,0x52);
        mKeyMap.insert(Qt::Key_S,0x53);
        mKeyMap.insert(Qt::Key_T,0x54);
        mKeyMap.insert(Qt::Key_U,0x55);
        mKeyMap.insert(Qt::Key_V,0x56);
        mKeyMap.insert(Qt::Key_W,0x57);
        mKeyMap.insert(Qt::Key_X,0x58);
        mKeyMap.insert(Qt::Key_Y,0x59);
        mKeyMap.insert(Qt::Key_Z,0x5A);
        mKeyMap.insert(Qt::Key_multiply,0x6A);
        mKeyMap.insert(Qt::Key_F1,0x70);
        mKeyMap.insert(Qt::Key_F2,0x71);
        mKeyMap.insert(Qt::Key_F3,0x72);
        mKeyMap.insert(Qt::Key_F4,0x73);
        mKeyMap.insert(Qt::Key_F5,0x74);
        mKeyMap.insert(Qt::Key_F6,0x75);
        mKeyMap.insert(Qt::Key_F7,0x76);
        mKeyMap.insert(Qt::Key_F8,0x77);
        mKeyMap.insert(Qt::Key_F9,0x78);
        mKeyMap.insert(Qt::Key_F10,0x79);
        mKeyMap.insert(Qt::Key_F11,0x7A);
        mKeyMap.insert(Qt::Key_F12,0x7B);
        mKeyMap.insert(Qt::Key_F13,0x7C);
        mKeyMap.insert(Qt::Key_F14,0x7D);
        mKeyMap.insert(Qt::Key_F15,0x7E);
        mKeyMap.insert(Qt::Key_F16,0x7F);
        mKeyMap.insert(Qt::Key_F17,0x80);
        mKeyMap.insert(Qt::Key_F18,0x81);
        mKeyMap.insert(Qt::Key_F19,0x82);
        mKeyMap.insert(Qt::Key_F20,0x83);
        mKeyMap.insert(Qt::Key_F21,0x84);
        mKeyMap.insert(Qt::Key_F22,0x85);
        mKeyMap.insert(Qt::Key_F23,0x86);
        mKeyMap.insert(Qt::Key_F24,0x87);
        mKeyMap.insert(Qt::Key_NumLock,0x90);
        mKeyMap.insert(Qt::Key_ScrollLock,0x91);
        mKeyMap.insert(Qt::Key_VolumeDown,0xAE);
        mKeyMap.insert(Qt::Key_VolumeUp,0xAF);
        mKeyMap.insert(Qt::Key_VolumeMute,0xAD);
        mKeyMap.insert(Qt::Key_MediaStop,0xB2);
        mKeyMap.insert(Qt::Key_MediaPlay,0xB3);
        mKeyMap.insert(Qt::Key_Plus,0xBB); // +
        mKeyMap.insert(Qt::Key_Minus,0xBD); // -
        mKeyMap.insert(Qt::Key_Underscore,0xBD); // _
        mKeyMap.insert(Qt::Key_Equal,0xBB); // =
        mKeyMap.insert(Qt::Key_Semicolon,0xBA); // ;
        mKeyMap.insert(Qt::Key_Colon,0xBA); // :
        mKeyMap.insert(Qt::Key_Comma,0xBC); // ,
        mKeyMap.insert(Qt::Key_Less,0xBC); // <
        mKeyMap.insert(Qt::Key_Period,0xBE); // .
        mKeyMap.insert(Qt::Key_Greater,0xBE); // >
        mKeyMap.insert(Qt::Key_Slash,0xBF);  // /
        mKeyMap.insert(Qt::Key_Question,0xBF); // ?
        mKeyMap.insert(Qt::Key_BracketLeft,0xDB); // [
        mKeyMap.insert(Qt::Key_BraceLeft,0xDB); // {
        mKeyMap.insert(Qt::Key_BracketRight,0xDD); // ]
        mKeyMap.insert(Qt::Key_BraceRight,0xDD); // }
        mKeyMap.insert(Qt::Key_Bar,0xDC); // |
        mKeyMap.insert(Qt::Key_Backslash,0xDC); // \\
        mKeyMap.insert(Qt::Key_Apostrophe,0xDE); // '
        mKeyMap.insert(Qt::Key_QuoteDbl,0xDE); // "
        mKeyMap.insert(Qt::Key_QuoteLeft,0xC0); // `
        mKeyMap.insert(Qt::Key_AsciiTilde,0xC0); // ~

//        DBG("key count is %d\n", mKeyMap.count());
//        QMap<int,char>::iterator it = mKeyMap.find(Qt::Key_B);
//        char c = it.value();
//        c = tolower(c);
//        DBG("key test b : %c\n",c);
}
