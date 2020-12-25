//#pragma once
#ifndef _TDUIAUTO_H_
#define _TDUIAUTO_H_

#include "tdbutton.h"
#include "leobase/Matrices.h"
#include "leobase/Vectors.h"

////////////////////////////////////////
//////微调操作时的界面
////////////////////////////////////////

class TduiAuto:public Tdui     //定制的一个操作按键界面
{
public:
	TduiAuto();
	~TduiAuto();

    void extraBlankSize(float w, float h);

public:
	Tdbutton *tbsave, *tbreturn, *tbautocalib;

    Tdbutton  *tbwp0,*tbwp1, *tbwp2, *tbwp3; 
	Tdbutton  *tbhp0,*tbhp1, *tbhp2, *tbhp3;

    Tdbutton *tbw3, *tbw2, *tbw1, *tbw0;
    Tdbutton *tbh3, *tbh2, *tbh1, *tbh0;

    // Tdbutton *tbhidewp, *tbhidewn, *tbhidehp, *tbhidehn;
    // Tdbutton *tbhidew3, *tbhidew2, *tbhidew1, *tbhidew0;
    // Tdbutton *tbhideh3, *tbhideh2, *tbhideh1, *tbhideh0;

	int mItem;
	int mCam;
    bool mDense;

private:
	virtual	int retCmd();
	virtual void updateKey();
	virtual void act(int i);
	// void hideFunc(bool b);
	// void hideBlank(bool b);

};



#endif

