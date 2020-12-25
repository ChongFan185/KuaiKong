//#pragma once
#ifndef _TDUIP2_H_
#define _TDUIP2_H_

#include "tdbutton.h"
#include "leobase/Matrices.h"
#include "leobase/Vectors.h"


////////////////////////////////////////
//////界面2
////////////////////////////////////////


class TduiP2 :public Tdui     //定制的一个操作按键界面
{
public:
	TduiP2();
	~TduiP2();

public:
    Tdbutton *btn0; //手动拼接按键
    Tdbutton *btn1; //自动拼接按键
    //Tdbutton *btn2；
    //Tdbutton *btn3;
    Tdbutton *btnreturn;

	// Tdbutton *tbsetview0, *tbsetview1, *tbsetview2, *tbsetview3, *tbsavepara;
	
private:
	virtual	int retCmd();
	virtual void updateKey();
	virtual void act(int i);

};



#endif

