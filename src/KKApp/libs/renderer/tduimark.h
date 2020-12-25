//#pragma once
#ifndef _TDUIMARK_H_
#define _TDUIMARK_H_

#include "tdbutton.h"
#include "leobase/Matrices.h"
#include "leobase/Vectors.h"
#include "leobase/imgbarrel.h"


////////////////////////////////////////
//////界面1
////////////////////////////////////////


class TduiMark :public Tdui     //定制的一个操作按键界面
{
public:
	TduiMark();
	~TduiMark();
public:
    Tdbutton *btn0, *btn1, *btn2, *btn3; 

	int mDisMode;
	bool bForceHide;
	// bool enSetting;
	// bool en3D;
	// bool enMirror;
	// bool enBtn;
public:
	void updateplace(ARR4V2 quali);
public:
	virtual void act(int i);
private:
	virtual	int retCmd();
	virtual void updateKey();




};


#endif



