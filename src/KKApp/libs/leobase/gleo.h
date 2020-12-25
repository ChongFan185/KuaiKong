#ifndef GLEO_H
#define GLEO_H

#include "common_leo.h"
#include "mdobject.h"
#include "gleoshader.h"

//#include <GLES2/gl2.h>

#include <string.h>
#include <string>

#ifdef QT
#include <QOpenGLFunctions>
#else
#include <GLES2/gl2.h>
#endif

using namespace std;

//class GlsHelper
//#ifdef QT
//        : public QOpenGLFunctions
//#endif

namespace gleo
//#ifdef QT
//    : public QOpenGLFunctions
//#endif
{
    void initGL();

    int createTexture2D();
#ifdef ANDROID
    int createTextureOes();
#endif

    int getFileLenght(const char *filename);
    bool readFile(const char *filename, string &shaderstr);
    bool readVertShader(const char *filename, string &shaderstr);
    bool readFragShader(const char *filename, string &shaderstr);

    int createProgram(const char* vshader, const char* fshader);
    int createProgramFile(const char *filename);
    int createProgramFile(const char *vsfilename, const char *fsfilename);

//    void rendererBindVb(Vertex4cBlock *vblock);
    void bindVb(VertexBlock *vblock);
    void bindIb(IndexBlock *iblock);

    void texBindPara();
//    void glBindTexture(GLenum target, GLuint texture);
    void texBindRgbFromBmp(GLint& texid, const char* file);
//    void texBindVYUYFromBmp(GLint& texid, const char* file);
//    void texBindYuvFromBmp(GLint& texid, const char* file);

    void texBindLumi(GLint tidy, unsigned char* graybuf, int width, int height);
    void texBindSubLumi(GLint tidy, unsigned char* graybuf, int width, int height);

    void texBindI420(GLint& tidy, GLint& tidu, GLint& tidv, unsigned char* i420buf, int width, int height);
    void texBindRgb(GLint& texid, unsigned char* buf, int width, int height);
    void texBindRgba(GLint& texid, unsigned char* buf, int width, int height);    
    void texBindUYVY(GLint& texid, unsigned char* buf, int width, int height);

    // void glsShaderAdsg(MdObject *usrobj, GLint shaderId);

    void updateMaterial(MaterialBlock *mblock, Vector4& am, Vector4& df, Vector4& sp);
    void draw(VertexBlock *vblock, IndexBlock *iblock, MaterialBlock *mblock, int* texIds , Shader *shader, GLenum mode = GL_TRIANGLES);


}

#endif // GLEO_H
