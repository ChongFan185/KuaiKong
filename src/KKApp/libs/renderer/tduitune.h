//#pragma once
#ifndef __TDUITUNE_H_
#define __TDUITUNE_H_

#include "tdbutton.h"
#include "leobase/Matrices.h"
#include "leobase/Vectors.h"

////////////////////////////////////////
//////微调操作时的界面
////////////////////////////////////////

class TduiTune:public Tdui     //定制的一个操作按键界面
{
public:
	TduiTune();
	~TduiTune();

    void extraBlankSize(float w, float h);

public:
	Tdbutton *tbcam0, *tbcam1, *tbcam2, *tbcam3;
    Tdbutton *tbcenter, *tbcampos, *tbmark, *tbexchange, *tbdense, *tbblanksize;
	Tdbutton *tbxp, *tbxn, *tbyp, *tbyn, *tbzp, *tbzn, *tbdone;
	Tdbutton *tbsave, *tbreturn, *tbenter;

    //Tdbutton *tbwp, *tbwn, *tbhp, *tbhn, *tbwidth, *tbheight;
    Tdbutton *tbwp3, *tbwp2, *tbwp1, *tbwp0;
    Tdbutton *tbhp3, *tbhp2, *tbhp1, *tbhp0;

    Tdbutton *tbw3, *tbw2, *tbw1, *tbw0;
    Tdbutton *tbh3, *tbh2, *tbh1, *tbh0;

    Tdbutton *tbhidewp, *tbhidewn, *tbhidehp, *tbhidehn;
    Tdbutton *tbhidew3, *tbhidew2, *tbhidew1, *tbhidew0;
    Tdbutton *tbhideh3, *tbhideh2, *tbhideh1, *tbhideh0;

    //本来打算加入独立的摄像头半径参数和调节功能， 认真考虑后，觉得此功能不必要了。
//    Tdbutton *tbrdp, *tbrdn, *tbrd3, *tbrd2, *tbrd1, *tbrd0;

	int mItem;
	int mCam;
    bool mDense;

private:
	virtual	int retCmd();
	virtual void updateKey();
	// virtual void act(int i);

	void hidez(bool b);
	void hidexy(bool b);
	void hideDone(bool b);
	void hideExchange(bool b);
    void hideDense(bool b);
	void hideCam(bool b);
	void hideFunc(bool b);
	void hideBlank(bool b);

};



#endif

