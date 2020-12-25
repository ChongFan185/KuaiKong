//#pragma once
#ifndef _MDOBJECT_H_
#define _MDOBJECT_H_

#include "Matrices.h"
#include "Vectors.h"

#include <vector>
#include <fstream>
#include <string>

#include "common_leo.h"

using namespace std;

#ifndef GLfloat 
typedef float GLfloat;
#endif

#ifndef GLushort
typedef unsigned short GLushort;
#endif

#ifndef GLuint
typedef unsigned int GLuint;
#endif

#define BLOCK_NAME_SIZE_MAX 63

#define MAX_ITEM_NUM 65536
#define MAX_VB_ITEM (65536*16)
#define MAX_IB_ITEM (65536*64)


//////////////////    MaterialBlock    ////////////////////////////

class MaterialBlock{
public:
	MaterialBlock();
	~MaterialBlock();
    string info(bool bPrintNow = false);
	bool save(std::fstream& fo);
	bool load(std::fstream& fi);
public:
	char name[256];
    //char texfile[256];

    string map_ka;
    string map_kd;
    string map_ks;
    string map_d;
    string map_bump;

    Vector4 ambient;
	Vector4 diffuse;
	Vector4 specular;
    Vector4 emission; //自发光
    Vector4 Tf; //obj模型中叫渐进溶解度，但是没有用到过。

    //GLfloat shinness;
    //GLfloat transparency; //透明度
    GLfloat Ni; //obj格式中叫高光指数，好像也就是高光亮度
    GLfloat Ns; //Ns应该就是透明度， obj格式中，Ns+d = 1.0， d= alpha
    GLfloat d;  //obj格式中叫不透明度， 跟Ns相加等于1.0
    GLfloat transparency; //透明度，mdobject 中，统一使用 trans 来表示透明度， 透明度 ！= 0， 那就需要额外处理。

    int illum; //光照模型，通常=2，也就是打开高光。

    GLuint	textureid;
};

//////////////////    VertexBlock    ////////////////////////////


class VertexBlock{
public:

typedef struct _VertexType
    {
        enum Enum
        {
            PNULL,
            PNU,
            PNUC,
            PN2U,
            PN2UC,
            Count
        };
    }VertexType;

typedef struct _VertexAttrib
    {
        enum Enum
        {
            STRIDE,
            POS,
            NRML,
            UV,
            UV1,
            COLOR,
            Count
        };
    }VertexAttrib;

typedef struct _VertexOffset
    {
        unsigned int stride;
        unsigned int pos;
        unsigned int nrml;
        unsigned int uv;
        unsigned int uv1;
        unsigned int color;
    }VertexOffset;


class Iterator{
public:
    Iterator(VertexBlock *outer)
    {
        _outer = outer;
        _iter_prev_num = -1;
        _iter_prev_p = outer->data - outer->iv.stride; // Underflow
    }

    ~Iterator(){}

    bool seek(int location)
    {
        if(location < 0 || location >= _outer->size){
            LOGE("VBlock Iter overflow");
            return false;
        }

        if(location == 0){
            _iter_prev_num = -1;
            _iter_prev_p = _outer->data - _outer->iv.stride; //Underflow
        }else{
            _iter_prev_num = location - 1;
            _iter_prev_p = _outer->data + _iter_prev_num * _outer->iv.stride;
        }
        return true;
    }

    bool hasNext(){
        if(_iter_prev_num < (_outer->size - 1)){
            return true;
        }else{
            return false;
        }
    }

    //Below functions don't have overflow test,it's not memory safe;
    Vector3& nextPosition(){
        _iter_prev_p += _outer->iv.stride;
        return *((Vector3*)(_iter_prev_p + _outer->iv.pos));
    }

    Vector3& nextNormal(){
        _iter_prev_p += _outer->iv.stride;
        return *((Vector3*)(_iter_prev_p + _outer->iv.nrml));
    }

    Vector2& nextUv(){
        _iter_prev_p +=  _outer->iv.stride;
        return *((Vector2*)(_iter_prev_p +  _outer->iv.uv));
    }

    Vector2& nextUv1(){
        _iter_prev_p +=  _outer->iv.stride;
        return *((Vector2*)(_iter_prev_p +  _outer->iv.uv1));
    }

    int& nextColor(){
        _iter_prev_p +=  _outer->iv.stride;
        return *((int*)(_iter_prev_p +  _outer->iv.color));
    }

private:
    int _iter_prev_num;
    unsigned char *_iter_prev_p;
    VertexBlock *_outer;
};

public:
    VertexBlock(VertexType::Enum fmt = VertexType::PN2U);
    ~VertexBlock();
	bool mmalloc(int num);
	void mfree();
    bool initial(VertexType::Enum fmt, int num);
	bool save(std::fstream& fo);
	bool load(std::fstream& fi);
    string info(bool bPrintNow = false);
	bool append(VertexBlock* apdblk);
	void transfer(Vector3 vct);
	void scale(Vector3 vct);
	void rotate(Vector3 degree);
	bool measure(Vector3& min, Vector3& max);

private:
    bool _setFormat(VertexType::Enum fmt);

public:    //inline functions
    bool seek(int location)
    {
        if(location < 0 || location >= size){
            LOGE("VBlock Iter overflow");
            return false;
        }

        if(location == 0){
            m_iter_prev_num = -1;
            m_iter_prev_p = data - iv.stride; //Underflow
        }else{
            m_iter_prev_num = location - 1;
            m_iter_prev_p = data + m_iter_prev_num * iv.stride;
        }
        return true;
    }

    bool hasNext(){
        if(m_iter_prev_num < size - 1 ){
            return true;
        }else{
            return false;
        }
    }

    //Below functions don't have overflow test,it's not memory safe;
    Vector3& posNext(){
        m_iter_prev_p += iv.stride;
        return *((Vector3*)(m_iter_prev_p + iv.pos));
    }

    Vector3& nrmlNext(){
        m_iter_prev_p += iv.stride;
        return *((Vector3*)(m_iter_prev_p + iv.nrml));
    }

    Vector2& uvNext(){
        m_iter_prev_p += iv.stride;
        return *((Vector2*)(m_iter_prev_p + iv.uv));
    }

    Vector2& uv1Next(){
        m_iter_prev_p += iv.stride;
        return *((Vector2*)(m_iter_prev_p + iv.uv1));
    }

    int& clrNext(){
        m_iter_prev_p += iv.stride;
        return *((int*)(m_iter_prev_p + iv.color));
    }

    Vector3& posAt(int i)
    {
        return *((Vector3*)(data + (i % size)*iv.stride + iv.pos));
    }

    Vector3& nrmlAt(int i)
    {
        return *((Vector3*)(data + (i % size)*iv.stride + iv.nrml));
    }

    Vector2& uvAt(int i)
    {
        return *((Vector2*)(data + (i % size)*iv.stride + iv.uv));
    }

    Vector2& uv1At(int i)
    {
        return *((Vector2*)(data + (i % size)*iv.stride + iv.uv1));
    }

    int& clrAt(int i)
    {
        return *((int*)(data + (i % size)*iv.stride + iv.color));
    }

public:
    char name[256];  //save
    VertexType::Enum format;  //save
    int size;  //save
    VertexOffset iv;

	GLuint vbo;
    unsigned char *data;  //save

    struct temp_data{
        int matcnt;
        int matid[256];
    }_t;

private:
    int m_iter_prev_num;
    unsigned char* m_iter_prev_p;

};


//////////////////    IndexBlock    ////////////////////////////

class IndexBlock{
public:
	IndexBlock();
	~IndexBlock();
	bool mmalloc(int num);
	void mfree();
	bool save(std::fstream& fo);
	bool load(std::fstream& fi);
    string info(bool bPrintNow = false);
	bool indexShift(GLuint num);
	bool useIntData();
	bool useShortData();
	bool append(IndexBlock* apdblk);
    void setTextureCount(int n);

    void setTexture(int tid0);
    void setTexture(int tid0, int tid1);
    void setTexture(int tid0, int tid1, int tid2);
    void setTexture(int tid0, int tid1, int tid2, int tid3);
    void setTexture(int cnt, int *tid);

public:
    char name[256];
    int isint;
	int size;
    int vtxId;
    int	matId;
    struct{
        char matName[256];
        char vtxName[256];
        int textureIds[32];
        int textureCount;
        GLuint vbo;
        GLuint ibo;
    };
    GLushort* sdata;  //save
    GLuint* ndata;  //save
};

//////////////////    通用模型数据结构    ////////////////////////////

class MdObject
{
public:
    MdObject();
    ~MdObject();

//	void draw();
    string info(bool bPrintNow = false);

    string infom();
    string infov();
    string infoi();

    bool save(const char* filename);
    bool load(const char* filename);

    //compare iblks[ibid0] with iblks[ibid1],if they have same vtxId, matId, size and data, then return true.
    bool  ibEqual(int ibid0, int ibid1);
    // Append vblks[vbid1].data to the end of vblks[vbid0].data, and delete vblks[vbid1]
    bool mrgVb(int vbid0, int vbid1);

    bool mrgVbAuto();

    bool mrgVbMass();
    // Append iblks[ibid1].data to the end of iblks[ibid0].data, and delete iblks[ibid1]
    bool mrgIb(int ibid0, int ibid1);
    // Merger all iblks in Tdo
    void mrgAllIb();
    // Merger iblks in specified VertexBlock
    void mrgPartIb(int vbid);
    // compare iblks[ibid0] with iblks[ibid1], if matId and vtxId are equal, then return true.
    bool ibMrgrable(int ibid0, int ibid1);
    // Delete specified iblock
    bool delIb(int ibid);
	// Search the iblks redundance
    void scanReduIb();
	// Delete redundance iblock;
    int delReduIb();
	// Statistic Tdo Size
	bool measure(Vector3& min, Vector3& max);
	// Display the model's size
	void infoSize();
	// Modify Tdo data's xyz, to change the model's size
    void scale(Vector3 vct);
    // 平移
	void transfer(Vector3 vct);
    // Z旋转
	void rotateZ(float degree);
    // 命令行输入
	bool cli(std::string cmdstring);


public:
	std::vector<MaterialBlock*> mblks;
    std::vector<VertexBlock*> vblks;
	std::vector<IndexBlock*> iblks;

};


std::vector<std::string> splite(std::string line);


#endif
