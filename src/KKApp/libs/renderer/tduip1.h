//#pragma once
#ifndef _TDKB1P_H_
#define _TDKB1P_H_

#include "tdbutton.h"
#include "leobase/Matrices.h"
#include "leobase/Vectors.h"


////////////////////////////////////////
//////界面1
////////////////////////////////////////

typedef struct _UvCoord{
	Vector4 uv0;
	Vector4 uv1;
}UvCoord;

class TduiP1 :public Tdui     //定制的一个操作按键界面
{
public:
	TduiP1();
	~TduiP1();
public:
	UvCoord uv3d, uvmir, uvcam0, uvcam1, uvcam2, uvcam3;
	UvCoord uv3dfnt, uv3drear, uv23fnt, uv23rear;
    UvCoord uvsetting;

    Tdbutton *btn0, *btn1, *btn2, *btn3 , *btn4, *btn6;//, *btn7, *btn8;
//	Tdbutton *btnb0, *btnb6;//*btnb1, *btnb2, *btnb3, *btnb4, *btnb6;

    Tdbutton *btnsetting, *btnsysreturn;

	int mDisMode;
	bool bForceHide;
	// bool enSetting;
	// bool en3D;
	// bool enMirror;
	// bool enBtn;
public:
	void setHorizontal();
	void setVertical();

	void ensysBtn(bool b);
	void enSettingBtn(bool b);
	void enMirrorBtn(bool b);
	void en3dBtn(bool b);
	void enOrgBtn(bool b);
//	void enBigBtn(int 

	void hide();
	void show();
	void forceHide(bool b);


public:
	virtual void act(int i);
private:
	virtual	int retCmd();
	virtual void updateKey();




};


#endif



