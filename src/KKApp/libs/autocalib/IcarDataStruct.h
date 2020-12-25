/*
* Created in 2018.
* This .h file lists all macro definitions and data structures
* that you need to use while you invoking the algorithm of this module.
*/

#ifndef ICARDATASTRUCT_H
#define ICARDATASTRUCT_H

#include <fstream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>
#include <vector>

using namespace std;
using namespace cv;

#define MAX_IMAGE_WIDTH 1280	//maximum width of the image
#define MAX_IMAGE_HEIGHT 720	//maximum height of the image
#define MAX_CHL_NUM  4		//the number of the cameras


//���̸����ж���
#define BOARDSIZE_ROW 6			//���̸��д�С��������������������
#define BOARDSIZE_COL 4			//���̸��д�С��������������������

#define DELTW 30			//���ӱ߳�
#define PAR_DIM 8

#define FILTER_THR 1300	//������ֵ

#define FILTER_ANGLE_1 25		//���˽Ƕ�1
#define FILTER_ANGLE_2 35		//���˽Ƕ�2
#define FILTER_RADIUS 10		//���˰뾶


//Image type identification
//used to distinguish which camera the image comes from
enum image_index
{
	IMAGE_FRONT,
	IMAGE_BACK,
	IMAGE_LEFT,
	IMAGE_RIGHT
};

//Operation type identification
//used to distinguish the operation UI sends to ALG
enum ui_operation
{
	UI_CLICK_KEY_W,	
	UI_CLICK_KEY_S,
	UI_CLICK_KEY_A,
	UI_CLICK_KEY_D
};

//Mark point position identification
//used to distinguish the position of mark points
enum mark_index
{
	MARK_LT,
	MARK_RT,
	MARK_LB,
	MARK_RB
};

//四边形 struct
//用来保存mark点信息
typedef struct
{
	float left_top_x;
	float left_top_y;
	float right_top_x;
	float right_top_y;
	float left_bottom_x;
	float left_bottom_y;
	float right_bottom_x;
	float right_bottom_y;
}Quadrilateral;


//Center point struct
//used to store coordinate and radius of a camera
typedef struct
{
	float x;
	float y;
	float r;
}IcarPoint;


//保存opencv处理过程中的图像数据
typedef struct imageInfo_struct{

	Mat mat;			//图像mat
	image_index index;		//枚举变量， 指明 图像是哪个方向

}ImageInfo;


//�ǵ���Ϣ�ṹ�壨���ǵ�ģ��ʹ�ã�
typedef struct cornersInfo_struct
{
public:
	vector<Point2f> p;
	vector<Point2f> v1;
	vector<Point2f> v2;
	vector<float> score;
}CornersInfo;


//��ͷͶӰ�����ṹ�壨��ͶӰģ��ʹ�ã�
typedef struct tagSBarParam
{
	float dWidthBar;
	float dHeightBar;
	float dSrcImgYX;
	float dMaxBarDist;
	float dBarPrec;
	float *pdBarToOrgPar;
	float dMaxOrgDist;
	float dOrgPrec;
	float *pdOrgToBarPar;

}SBarParam;


//ͶӰ�任��������ͶӰģ��ʹ�ã�
typedef struct
{
	double PAR_A;
	double PAR_B;
	double PAR_C;
	double PAR_D;
	double PAR_E;
	double PAR_F;
	double PAR_G;
	double PAR_H;

}PARAMETERS;


//�ڿ�ƥ���������ͶӰ�кڿ�ģ��ʹ�ã�
typedef struct _MatchParm
{
	double MatchRate;
	int id;
}MatchParm;

//ɸѡ�㼯
typedef struct
{
	Point2f point;
	double cUp;
	double cDown;
	double cLeft;
	double cRight;
}FilterPoint;

//ͶӰ���
typedef struct
{
	Point2f center;
	Quadrilateral mark;
	Quadrilateral chess;
	int r;
}AffineResult;

#endif
