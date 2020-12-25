#ifndef GLEOSHADER_H
#define GLEOSHADER_H

#include "common_leo.h"

#include "Vectors.h"
#include "Matrices.h"
//#include "cameraspl.h"
#include "mdobject.h"

#include <string>
#include <vector>

#ifdef QT
#include <QOpenGLFunctions>
#else
#include <GLES2/gl2.h>
#endif

#define SHADER_NAME_LEN_MAX  63

namespace gleo{

struct UniformType{
    enum Enum
    {
//        UNINULL,
        INT1,  // used for samplers only
        INT1V,
        VEC3,  // 3float vector
        VEC4,  // 4float vector
        MAT3,  // 3x3 matrix
        MAT4,  // 4x4 matrix
        Count
    };
};

class Uniform{
public:
    Uniform();

    Uniform(UniformType::Enum tp, char *name, int freqency, int nvalue);
    Uniform(UniformType::Enum tp, char *name, int freqency, float fvalue);
    Uniform(UniformType::Enum tp, char *name, int freqency, int* pint);
    Uniform(UniformType::Enum tp, char *name, int freqency, float* pfloat);

    ~Uniform();

public:
    char name[SHADER_NAME_LEN_MAX + 1];
    UniformType::Enum type;
    int loc;
    int freq; // 0, 不再设置， 1，设置1次， 2，多次设置
    union{
        int n;
        float f;
        int *pn;
        float *pf;
    };

};


class Shader
#ifdef QT
    : public QOpenGLFunctions
#endif
{
public:
    Shader();
    ~Shader();

    void setName(char *name);
    void iniAttribute();
    bool _extendUniformCap();
    bool addUniformArray(Uniform list[], int listSize);
    bool addUniform(Uniform item);
    void fillUniform();
    std::string info(bool bPrintNow = true);
    void use(){
        if(id != currentShader){
            glUseProgram(id);
            currentShader = id;
        }
        fillUniform();
        return;
    }
    void setTextureCount(int n);
    int getTextureCount();

//public:
//    void draw(MdObject &usrobj, LeUni* uni);
//    void draw(VertexBlock *vblock, IndexBlock *iblock, MaterialBlock *mblock, bool hasTex, LeUni *uni);

private:
    static int currentShader;

public:
    char name[SHADER_NAME_LEN_MAX + 1];
    GLuint id;
    GLuint locPosition;
    GLuint locNormal;
    GLuint locUv;
    GLuint locUv1;
    GLuint locColor;
    GLenum textureType;
    int    textureCount;

    Uniform * uniList;
    int uniListSize;
    int _uniListCap;
    const int _uniListDefaultSize = 8;

//    std::vector<GlsUniformItem> uniVector;
//    std::vector<GlsUniformItem> stableUni;
//    std::vector<GlsUniformItem> unstableUni;


//    UNI_DESCRIPTOR *descriptor;
//    int descriptor_length;

};

} // namespace gleo

#endif // GLEOSHADER_H
