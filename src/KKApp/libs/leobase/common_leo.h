#ifndef __COMMON_LEO_H__
#define __COMMON_LEO_H__

//////////////////////////////////////////////////
///// USER SETTING START
///////////////////////////////////////////////////

#define COMMON_LEO

#define LOG_INFO
#define LOG_VERBOSE
#define LOG_WARNING
#define LOG_ERROR
#define LOG_DEBUG

/// choice one in two candidates
//#ifndef ANDROID
//#define ANDROID
//#endif
 #ifndef QT
 #define QT
 #endif

/// camera configure
//#define AHD_4CAM_IN_1080P
//#define AHD_HALF_720P

//////////////////////////////////////////////////
///// USER SETTING END
///////////////////////////////////////////////////


#define  LOG_TAG    "TDP"

/////@ brief Output to std::cout
// #define LOG(lvl, args...)   LOG_##lvl(args)
//
//template<typename Stream, typename First>void print(Stream& s, First f)
//{
//    s << f << std::endl;
//}

//template<typename Stream, typename First, typename... Last>void print(Stream& s, First f, Last... l)
//{
//    s << f;
//    print(s, l...);
//}

#ifdef ANDROID
#include <android/log.h>

#ifdef LOG_INFO
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#else
#define LOGI(...)
#endif

#ifdef LOG_VERBOSE
#define  LOGV(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#else
#define  LOGV(...)
#endif

#ifdef LOG_WARNING
#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
#else
#define LOGW(...)
#endif

#ifdef LOG_ERROR
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#else
#define LOGE(...)
#endif

#ifdef LOG_DEBUG
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define  DBG(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#else
#define LOGD(...)
#define DBG(...)
#endif


#else

#ifdef QT

#include <iostream>

#ifdef LOG_INFO
#define  LOGI(fmt,args...)  do{printf("I/%s:%s " fmt, LOG_TAG, __FUNCTION__, ##args);std::cout.flush();}while(0)
#else
#define LOGI(fmt,args...)
#endif

#ifdef LOG_VERBOSE
#define  LOGV(fmt,args...)  do{printf("V/%s:%s " fmt, LOG_TAG, __FUNCTION__, ##args);std::cout.flush();}while(0)
#else
#define  LOGV(fmt,args...)
#endif

#ifdef LOG_WARNING
#define  LOGW(fmt,args...)  do{printf("W/%s:%s " fmt, LOG_TAG, __FUNCTION__, ##args);std::cout.flush();}while(0)
#else
#define  LOGW(fmt,args...)
#endif

#ifdef LOG_ERROR
#define LOGE(fmt,args...) do{printf("E/%s:%s " fmt, LOG_TAG, __FUNCTION__, ##args);std::cout.flush();}while(0)
#else
#define LOGE(fmt,args...)
#endif

#ifdef LOG_DEBUG
#define LOGE(fmt,args...) do{printf("E/%s:%s " fmt, LOG_TAG, __FUNCTION__, ##args);std::cout.flush();}while(0)
#define DBG(fmt,args...) do{printf("D/%s %d: " fmt,  __FUNCTION__ , __LINE__ , ##args);std::cout.flush();}while(0)	
#else
#define LOGE(fmt,args...)
#define DBG(fmt,args...)
#endif


#else

#ifdef LOG_INFO
#define  LOGI(fmt,args...)  do{printf("I/%s:%s " fmt, LOG_TAG, __FUNCTION__, ##args);}while(0)
#else
#define LOGI(fmt,args...)
#endif

#ifdef LOG_VERBOSE
#define  LOGV(fmt,args...)  do{printf("V/%s:%s " fmt, LOG_TAG, __FUNCTION__, ##args);}while(0)
#else
#define  LOGV(fmt,args...)
#endif

#ifdef LOG_WARNING
#define  LOGW(fmt,args...)  do{printf("W/%s:%s " fmt, LOG_TAG, __FUNCTION__, ##args);}while(0)
#else
#define  LOGW(fmt,args...)
#endif

#ifdef LOG_ERROR
#define LOGE(fmt,args...) do{printf("E/%s:%s " fmt, LOG_TAG, __FUNCTION__, ##args);}while(0)
#else
#define LOGE(fmt,args...)
#endif

#ifdef LOG_DEBUG
#define LOGD(fmt,args...)  do{printf("D/%s %d: " fmt,  __FUNCTION__ , __LINE__ , ##args);}while(0)
#define DBG(fmt,args...) do{printf("D/%s %d: " fmt,  __FUNCTION__ , __LINE__ , ##args);}while(0)
#else
#define LOGD(...)
#define DBG(fmt,args...)
#endif


#endif

#endif


#define CLAMP2UB(x) (x= x<0? 0: x>255? 255:x)
#define MEMORY_FREE(x)  {if(x!=NULL){free(x);x=NULL;}}
#define WIDTHBYTES(bits)    (((bits) + 31) / 32 * 4)

#define S_FREE(x)  {if(x!=NULL){free(x);x=NULL;}}
#define S_DELETE(x) {if(x!=NULL){delete(x);x=NULL;}}
#ifndef PI
#define PI 3.1415926
#endif

#define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))


#define STD_RESET   "\033[0m"
#define STD_BLACK   "\033[30m"      /* Black */
#define STD_RED     "\033[31m"      /* Red */
#define STD_GREEN   "\033[32m"      /* Green */
#define STD_YELLOW  "\033[33m"      /* Yellow */
#define STD_BLUE    "\033[34m"      /* Blue */
#define STD_MAGENTA "\033[35m"      /* Magenta */
#define STD_CYAN    "\033[36m"      /* Cyan */
#define STD_WHITE   "\033[37m"      /* White */
#define STD_BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define STD_BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define STD_BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define STD_BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define STD_BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define STD_BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define STD_BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define STD_BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

#endif //_COMMON_LEO_H_
