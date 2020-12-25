//#pragma once
#ifndef _TDPANOKEY_H_
#define	_TDPANOKEY_H_

#include "leobase/mdobject.h"
#include "leobase/Matrices.h"
#include "leobase/Vectors.h"



class Tdbutton{
public:
	Vector3 _p;
	Vector2 _s;

	Vector3 pos[4];

    unsigned int clrNormal;
	unsigned int clrPress;
    unsigned int clrDown;

    unsigned int clrHide;

	Vector2 uvNormal[4];	//纹理
	Vector2 uvPress[4];		//附加纹理1
	Vector2 uvDown[4];		//附加纹理2

	Vector2 uvStart;    // 字符纹理起点
	Vector2 uvStride;   // 字符纹理跨度
	Vector2 uvIndex;	// 字符纹理位置

	//bool 	mIsText;

	bool 	mDisable;	//标志位， Key是否被启用
	bool	mHiding;   //标志位，Key是否被隐藏
	bool	mDown;     //标志位，Key是否保持按下状态
	bool	mPressed;  //标志位，Key是否被按下
	bool	mDull;     //标志位，如果true，则Key不响应点击
	bool 	mHighlight; //标志位，正常是false，如果是true，表示按键的亮暗逻辑是反的。
	bool 	mTwouv;

	int KeyCmd;
	int KeyNum;

	bool mHasText;
	char text[32];

	float _padx;
	float _pady;

	float mz;

public:
	Tdbutton();

	~Tdbutton();

	// void setTextUv(Vector2 start, Vector2 stride);
	// void setTextUvIndex(Vector2 index);
	void setPad(float gap_x, float gap_y);

//	void show();
	Tdbutton& setPosZ(float z);

	Tdbutton& setPos(float min_x, float min_y, float w, float h);
	Tdbutton& setPos(Vector3 startpnt, Vector2 rectsize);
	Tdbutton& setPos(Vector3 startpnt, Vector3 rectsize);
    void setClr(unsigned int color);
    void setClr1(unsigned int color);
	void setClr2(unsigned int color);

	void setUv(Vector2 startpnt, Vector2 rectsize, Vector2 rectoffset, int texnum);
	void setText(char* str);

	// void setUv(int x0, int y0);
	// void setUv2(int x0, int y0, int x1, int y1);
	// void setUv(float block_x, float block_y, int x_len, int y_len, int x0, int y0);
	// void setUv2(float block_x, float block_y, int x_len, int y_len, int x0 ,int y0, int x1, int y1);

//	Tdbutton& setUv(float tl_x, float tl_y, float w, float h);
	Tdbutton& setUv0(float tl_x, float tl_y, float w, float h);
	Tdbutton& setUv1(float tl_x, float tl_y, float w, float h);
	Tdbutton& setUv0(Vector4& v);
	Tdbutton& setUv1(Vector4& v);
	Tdbutton& setUv(Vector4& v0, Vector4& v1);

	void setHide(bool h);
	void setDisable(bool b);
	void setDown(bool d);
	void setDull(bool b);
	void setHighlight(bool b);
	bool hasPnt(float x, float y);

//	void toExtBuf(VertexPNUC *extbuf);
    void toExtBuf(unsigned char *databuf);
};



class Tdui      //定制的一个操作按键界面
{
public:
	Tdui();
	~Tdui();
	void setPosition(float normal_lowlft_x, float normal_lowlft_y, float normal_width, float normal_height);
	void setTdSize(float w, float h);
	void setTextureId(unsigned int TextureId);

	void update();

	bool mouseResponding();
	int mousePressEvent(float normal_xpos, float normal_ypos);
	int mouseReleaseEvent();

	void initial();
	void movein(Tdbutton *key);
	Tdbutton* addBtn();
	// void xput(Tdbutton *key, const Vector2& size);
	// void yput(Tdbutton *key, const Vector2& size);
	Tdui& xput(Tdbutton *key, float w, float h);
	Tdui& yput(Tdbutton *key, float w, float h);
	Tdui& xput(Tdbutton *btn);
	Tdui& yput(Tdbutton *btn);
	// void put(Tdbutton *btn, const Vector2& size);
	Tdui& put(Tdbutton *btn, float w, float h);
	Tdui& put(Tdbutton *btn);
	Tdui& move(float x, float y);
	Tdui& moveto(const Vector3& m);
	Tdui& setRect(const Vector2& rect);
	Tdui& setRect(float w, float h);
	Tdui& setUvBlock(float w, float h);

	Tdui& setUv0(Tdbutton* btn, int sx, int sy, int lenx, int leny);
	Tdui& setUv0(Tdbutton* btn, int sx, int sy);
	Tdui& setUv1(Tdbutton* btn, int sx, int sy, int lenx, int leny);
	Tdui& setUv1(Tdbutton* btn, int sx, int sy);
	Tdui& setUv(Tdbutton* btn, int sx0, int sy0, int sx1, int sy1, int lenx, int leny);
	Tdui& setUv(Tdbutton* btn, int sx0, int sy0, int sx1, int sy1);

//private:
	virtual	int retCmd();    
	virtual void updateKey();
	virtual void act(int i);

public:
	Vector2 WND_LOWLFT = { 0.0, 0.0 };       //键盘在窗口上显示范围的左下角坐标
	Vector2 WND_REGION = { 1.0, 1.0 }; //键盘在窗口上显示范围的右上角坐标
    Vector2 KBSIZE = { 1280.0, 720.0 };		    //键盘在3D 空间中的尺寸,键盘是按照1280/720的尺寸设计的，如果openGL画图
    //时的显示区域不是这个比例，则KEY的形状将不是正方形。会有拉伸，形变
	float KBYDIVX = KBSIZE.y / KBSIZE.x;

public:
	bool mEnable;
	bool mResponding;
	int mCurKeyNum; 
	int mCurCmd;

	Vector3 _pt;
	Vector2 _tmpSize;
	Vector2 _uvblock;
//	int mKeycnt;  //在构造函数中需要赋值，表示Key的数量
	unsigned int mKeyTexture;
//	Tdbutton *mpKeyArr = NULL;  //在构造函数中创建一个数组，并将数组地址赋给此变量，数组元素为mKeycnt个。
	Tdbutton *mpPressedKey = NULL;  //用来指向当前被点击的key，以便于在mouseRelease函数中修改属性
	std::vector<Tdbutton*> arrKey;
    VertexBlock vb;
	IndexBlock ib;
};



#endif

