#ifndef _IMGCONVERT_H_
#define _IMGCONVERT_H_


#include "imgdef.h"

///
/// \brief tYvyu2Yuv
/// \param src_yvyu
/// \param des_rgb
/// \param width
/// \param height
///
void imYuv422to444(unsigned char *src_yvyu, unsigned char* des_yuv, int pixelcount);

void imYuv422toRgb(unsigned char* src_yvyu, unsigned char* des_rgb, int width, int height);

void imYuv422toRgb_d2(unsigned char *src_yvyu, unsigned char *des_rgb, int width, int height, int blankpixel);

void imYuv444toRgb(unsigned char * src_yuv, unsigned char *des_rgb, int width, int height);

void imYuv444toRgb(unsigned char * src_yuv, int width, int height);

void imRgbto565(unsigned char * src_rgb, unsigned char *des_565, int width, int height);

void imRgbtoYuv422(unsigned char *src_rgb, unsigned char *des_yuv, int width, int height, bool trueForRgbAndFalseForBgr);

void imRgbtoYuv422(unsigned char *src_rgb, int width, int height);

void imRgbtoYuv444(unsigned char *src_rgb, unsigned char *des_yuv, int width, int height);

void imYuv444toI420(unsigned char *src_yuv, unsigned char *des_i420, int width, int height);

void imYuv422toI420(unsigned char *src_yuv, unsigned char *des_i420, int width, int height);

void imI420toRgb(unsigned char *src_y, unsigned char *src_u, unsigned char *src_v, unsigned char *des_rgb, int width, int height);

void imI420toRgb(unsigned char *src_i420, unsigned char *des_rgb, int width, int height);

//OpenGL texture compression

void tcRgbEnc(unsigned char *rgbbuf, unsigned char *compressd, int width, int height, bool isDisplayTest, bool isRgb888);

void tcRgb64bDec(unsigned  char *compressed, unsigned char *rgb565buf, int width, int height);

void tcRgb80bDec(unsigned  char *compressed, unsigned char *rgb565buf, int width, int height);


unsigned short tcPixRgb2565(unsigned char *rgb3B);

void tcPix5652Rgb(unsigned short rgb2B, unsigned char *rgb3B);

void tcPixDXT1Color(Pix3UB *pp3b);

// 从实际测试的结果来看，类似 ETC1 的纹理压缩方式，有两个缺陷
// 1. 查找标准化颜色的时候，需要考虑溢出的问题，（因为RGB三个颜色的差值平均了，很有可能导致加减差值之后，某个颜色分量的颜色值会大于255或者小于0），而且运算量增加了
// 2. 三个颜色RGB的差值平均化了，使得颜色误差增加，在输出图像上，马赛克效果更加明显（特别是鲜艳色块的边缘（因为颜色鲜艳的地方，RGB的值就越不均匀））。
unsigned int tcPixPesudoETC1Color(Pix3UB *pp3b);

void tcGetPesudoETC1Color(unsigned int n1, Pix3UB *pp3b);

#endif // LECAPWORK_H
