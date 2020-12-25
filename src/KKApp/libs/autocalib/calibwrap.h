#ifndef _CALIBWRAP_H_
#define _CALIBWRAP_H_

#include <stdlib.h>
#include <iostream>
#include <string>

#include <math.h>
#include <fstream>
#include <vector>
#include <time.h>

#include "IcarRegulator.h"
//#include <opencv2/opencv.hpp>

class CalibWrap
{
public:
    CalibWrap();
    // CalibWrap(CalibWrap &&) = default;
    // CalibWrap(const CalibWrap &) = default;
    // CalibWrap &operator=(CalibWrap &&) = default;
    // CalibWrap &operator=(const CalibWrap &) = default;
    ~CalibWrap();

    bool do4pic();
    bool do1pic(std::string filename);

    bool doCalibFile(int idx, const char* flag, std::string imagefile);
    bool doCalibMat(int idx, const char* flag, Mat mat);
    void writeResult(int idx, char* flag);
    void writeAllReuslt();

    void test();

    void setDirectory(std::string dir){userPath = dir; return;}
    void setBrpFile(std::string filename){brpFilename = filename; return;}
    void setCfgFile(std::string filename){cfgFilename = filename; return;}
    void setCenterFile(std::string filename){centerFilename = filename; return;}
    void setMarkFile(std::string filename){markFilename = filename; return;}
    void setImageFIle(int idx, std::string filename)
    {
        _pic[idx % 4] = filename; return;
    }

//    void setImageFile(std::string filename);

public:
    std::string userPath;
    std::string brpFilename;
    std::string cfgFilename;
    std::string centerFilename;
    std::string markFilename;
 	std::string _pic[4];

    IcarRegulator regular;
};


#endif
