#ifndef _TDPANOWND_H_
#define _TDPANOWND_H_

//#include "ogl/Matrices.h"
//#include "ogl/Vectors.h"
//#include "ogl/tdobject.h"

#include <string>
//#include <map>


#include <QtOpenGL/QGLWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLContext>

#include <QMap>
#include <QTimer>
#include <QPoint>

#include "rendererex/rdrrpano.h"
//#include "rdrrcam/rdrrcam.h"

#include <opencv2/opencv.hpp>


using namespace std;

struct Vector2;
struct Vector3;
class Matrix4;



class QOpenGLWidgetTdp : public QOpenGLWidget , public QOpenGLFunctions
{
	Q_OBJECT

public:
    QOpenGLWidgetTdp(QWidget *parent = NULL);
    ~QOpenGLWidgetTdp();

private:
    void initKeyMap();

	void initializeGL();
	void resizeGL(int width, int height);
	void paintGL();

	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void keyPressEvent(QKeyEvent *event);
	void mouseDoubleClickEvent(QMouseEvent *event);

	void drawText(int xpos,int ypos, char* str);

signals:
	void sendKey(int key);
	void startVideo();
	void endVideo();

public slots :
    void readframe();
    void showPic(const void* bufaddr, int width, int height);
    void tex4CamUpdate(unsigned char* buf0, unsigned char* buf1, unsigned char* buf2, unsigned char* buf3);
	void onTimerOut();

	// void extSingleTextureId(GLuint id);
	void setCameraTexId(int id0, int id1, int id2, int id3);
	void cameraTexUpdated();

	void setSourceMode(int mode);
	void setSourceRtsp(int n, string s);

private:
//	需要外部传递值进行修改的部分
    bool bTimerOn;
    bool bVideoOn;

    QMap<int, char> mKeyMap;

// 代码中需要用到的Qt变量
//    QPoint LastPos;
    QTimer mytimer;
//    QImage *tmptex[4];
//    RendererCam  mrender;
    RendererTdp mrender;

    int inputMode = 0;
    cv::VideoCapture cap[4];

};




#endif // TEST1_H
