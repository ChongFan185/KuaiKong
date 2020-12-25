#ifndef PREDEF_H
#define PREDEF_H

// #include <fstream>
// #include <opencv2/opencv.hpp>
// #include <vector>

//#include "IcarDataStruct.h"

#include "leobase/common_leo.h"

#define FILE_CARINFO	"config/carinfo.cfg"
#define SHOWIMAGE 1


#ifdef OLD_OPENCV3X

#else

#define CV_FONT_HERSHEY_DUPLEX  FONT_HERSHEY_DUPLEX
#define CV_INTER_LINEAR     INTER_LINEAR

#endif

// #define  LOGI(fmt,args...)  do{printf("I/:%s " fmt, __FUNCTION__, ##args);std::cout.flush();}while(0)
// #define  LOGE(fmt,args...)  do{printf("E/:%s " fmt, __FUNCTION__, ##args);std::cout.flush();}while(0)


// using namespace cv;
// using namespace std;



#endif
