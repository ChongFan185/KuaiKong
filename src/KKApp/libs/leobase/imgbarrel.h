#ifndef _IMGBARREL_H_
#define _IMGBARREL_H_


#include "Vectors.h"
#include "imgdef.h"


#define PAR_DIM 8


struct ARR2V2{
    Vector2 v0;
    Vector2 v1;
    ARR2V2(){}
    ARR2V2(Vector2 vct0, Vector2 vct1){
        v0=vct0;v1=vct1;
    }
    Vector2& item(int i){
        int item;
        if(i<0) item=0;
        else if(i>1) item=1;
        else item = i;

        switch(item){
        case 0:return v0;
        case 1:return v1;
        default: return v0;
        }
    }
};

struct ARR2V3{
    Vector3 v0;
    Vector3 v1;
    ARR2V3(){}
    ARR2V3(Vector3 vct0, Vector3 vct1){
        v0=vct0;v1=vct1;
    }
    Vector3& item(int i){
        int item;
        if(i<0) item=0;
        else if(i>1) item=1;
        else item = i;

        switch(item){
        case 0:return v0;
        case 1:return v1;
            default: return v0;
        }
    }
};

struct ARR3V2{
    Vector2 v0;
    Vector2 v1;
    Vector2 v2;
    ARR3V2(){}
    ARR3V2(Vector2 vct0, Vector2 vct1, Vector2 vct2){
        v0=vct0;v1=vct1;v2=vct2;
    }
    Vector2& item(int i){
        int item;
        if(i<0) item=0;
        else if(i>2) item=2;
        else item = i;

        switch(item){
        case 0:return v0;
        case 1:return v1;
        case 2:return v2;
            default: return v0;
        }
    }
};

struct ARR3V3{
    Vector3 v0;
    Vector3 v1;
    Vector3 v2;
    ARR3V3(){}
    ARR3V3(Vector3 vct0, Vector3 vct1, Vector3 vct2){
        v0=vct0;v1=vct1;v2=vct2;
    }
    Vector3& item(int i){
        int item;
        if(i<0) item=0;
        else if(i>2) item=2;
        else item = i;

        switch(item){
        case 0:return v0;
        case 1:return v1;
        case 2:return v2;
            default: return v0;
        }
    }
};

struct ARR4V2{
    Vector2 v0;
    Vector2 v1;
    Vector2 v2;
    Vector2 v3;
    ARR4V2(){}
    ARR4V2(Vector2 vct0, Vector2 vct1, Vector2 vct2, Vector2 vct3){
        v0=vct0; v1=vct1; v2=vct2; v3=vct3;
    }
    Vector2& item(int i){
        int item;
        if(i<0) item=0;
        else if(i>3) item=3;
        else item = i;

        switch(item){
        case 0:return v0;
        case 1:return v1;
        case 2:return v2;
        case 3:return v3;
            default: return v0;
        }
    }
};

struct ARR4V3{
    Vector3 v0;
    Vector3 v1;
    Vector3 v2;
    Vector3 v3;

    ARR4V3() {}
    ARR4V3(Vector3 vct0, Vector3 vct1, Vector3 vct2, Vector3 vct3)
    {
        v0=vct0; v1=vct1; v2=vct2; v3=vct3;
    }
    Vector3& item(int i){
        int item;
        if(i<0) item=0;
        else if(i>3) item=3;
        else item = i;

        switch(item){
        case 0:return v0;
        case 1:return v1;
        case 2:return v2;
        case 3:return v3;
            default: return v0;
        }
    }
};

//typedef Vector2 ARR16V2[16];



class BarrelConverter
{
public:
	BarrelConverter();
	~BarrelConverter();

    bool LoadBrpDB(char* filename);
    bool loadBrp(char* filename);
    bool SaveBrp(char* filename);
    void SetCenter(float centerx, float centery);
    int PtToOrg(Vector2& barpnt, Vector2& orgpnt);
    int PxyToOrg(float xBar, float yBar, float& xOrg, float& yOrg);
    int PtToBar(Vector2& orgpnt, Vector2& barpnt);
    int PxyToBar(float xOrg, float yOrg, float& xBar, float& yBar);

    int PtToOrgTest(Vector2& barpnt, Vector2& orgpnt);
    int PtToBarTest(Vector2& orgpnt, Vector2& barpnt);

    int PxyToOrgTest(float xBar, float yBar, float& xOrg, float& yOrg);
    int PxyToBarTest(float xOrg, float yOrg, float& xBar, float& yBar);

//	void OrgToBarCvs(CANVAS *scvs, CANVAS *dcvs, int zoom, float offsetx, float offsety);
//	void OrgToBar(void *psrc, int srcw, int srch, void *pdes, int desw, int desh, int zoom, float offsetx, float offsety);
    void OrgToBar(const unsigned char *psrc, const int srcw, const int srch, const unsigned char *pdes, const int desw, const int desh, int zoom, float offsetx, float offsety);

public:

	float fOrgPrec;
	float fOrgMaxDist;
	float fOrgWidth;
	float fOrgHeight;
	float fOrgCtx;
	float fOrgCty;
	float *pfO2B;

	float fBarPrec;
	float fBarWidth;
	float fBarHeight;
	float fSrcImgYX;
	float fBarMaxDist;
	float *pfB2O;

    float asblVtable;
};


class ProjectConverter
{
public:
	ProjectConverter();
	~ProjectConverter();

	int prjguass(int n, double **a, double *b, double ep);
	int calcProjectPara(ARR4V2 src, ARR4V2 dest);
    void PtProject(Vector2& src, Vector2& des);
    void PxyProject(float x, float y, float& u, float& v);

public:
	float p[8];
};

//double innerProduct(Vector2 p1, Vector2 p2, Vector2 p0);

//double distancePt2Ln(ARR2V2* line, Vector2 point);

float getMinX(ARR4V2& quali);

float getMinY(ARR4V2& quali);

float getMaxX(ARR4V2& quali);

float getMaxY(ARR4V2& quali);

//int isInCvxPoly(int area[4][2], int x, int y);

bool isInRect(ARR2V2& rect, Vector2& pnt);

bool isInCvxPoly(ARR4V2& quali, Vector2& pnt);

//float CalcRptWidth(int upordown, ARR2V2* line, Vector2 point);

int calculateX(int x1, int y1, int x2, int y2, int y);

int calculateY(int x1, int y1, int x2, int y2, int x);




#endif 
