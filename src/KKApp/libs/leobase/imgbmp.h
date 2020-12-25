///  *.bmp 在windows上存储是，数据的顺序是 BGR,BGRA
/// qt，opengl还有其他一些地方，位图的数据顺序是 RGB，RGBA
/// 这个差异就会导致色调错误，注意一下这个顺序

/// *.bmp图片的数据格式是从下往上保存的。（以便匹配 左下角（0,0）的坐标系统）
/// linux和opengl的坐标系统是左上角坐标（0,0）

#ifndef BMPLSIMPLE_H
#define BMPLSIMPLE_H

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
//typedef unsigned long u64;

//位图文件头定义;
//其中不包含文件类型信息（由于结构体的内存结构决定，
//要是加了的话将不能正确读取文件信息）
typedef struct  tagLsBmpHead{ //12B
    //u16 bfType;//文件类型，必须是0x424D，即字符“BM”
    u32 bfSize;//文件大小
    u16 bfReserved1;//保留字
    u16 bfReserved2;//保留字
    u32 bfOffBits;//从文件头到实际位图数据的偏移字节数
}LsBmpHead;

typedef struct tagLsBmpInfo{ //40B
    u32 biSize;//信息头大小
    u32 biWidth;//图像宽度
    u32 biHeight;//图像高度
    u16 biPlanes;//位平面数，必须为1
    u16 biBitCount;//每像素位数
    u32  biCompression; //压缩类型
    u32  biSizeImage; //压缩图像大小字节数
    u32  biXPelsPerMeter; //水平分辨率
    u32  biYPelsPerMeter; //垂直分辨率
    u32  biClrUsed; //位图实际用到的色彩数
    u32  biClrImportant; //本位图中重要的色彩数
}LsBmpInfo; //位图信息头定义

typedef struct tagLsRgbQuad{
    u8 rgbBlue; //该颜色的蓝色分量
    u8 rgbGreen; //该颜色的绿色分量
    u8 rgbRed; //该颜色的红色分量
    u8 rgbReserved; //保留值
}LsBmpRgbQuad;//调色板定义

//像素信息
typedef struct tagLsBmpData
{
    u8 blue;
    //u8 green;
    //u8 red;
}LsBmpData;


class BmpLsimple{
public:
    BmpLsimple();
    //BmpLsimple(const char* filename);
    ~BmpLsimple();

    //暂时只保存RGB格式，并且不考虑行对齐（user确保每行像素数为4的倍数）
    bool init(int width, int height);
    bool load(const char* filename);
    bool save(const char* filename);
    //暂时只保存RGB格式，并且不考虑行对齐（user确保每行像素数为4的倍数）
    static bool save(const char* filename, unsigned char* buf, int width, int height);

    void showHead(LsBmpHead pBmpHead);
    void showHead();
    void showInfo(LsBmpInfo pBmpInforHead);
    void showInfo();

    int width();
    int height();
    int pixelBytes();
    unsigned char* bits();
    int size();

    bool exchangeRB();
    bool reverse();
    bool convertToRgba();
    bool convertToRgb888();

private:
    LsBmpHead head;
    LsBmpInfo info;
    u8 *bmpdata;
};


//void showBmpHead(LsBmpHead pBmpHead);
//void showBmpInforHead(LsBmpInfo pBmpInforHead);
//bool ReadBMP(const char* strFileName);


#endif // BMPLSIMPLE_H
