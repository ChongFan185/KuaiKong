/*
 * Created in 2018.
 * This .h file provides a interface class named IcarRegulator 
 * which used to implement APIs for splicing and adjusting parts of the algorithm.
 */

#ifndef ICARREGULATOR_H
#define ICARREGULATOR_H

#include "IcarDataStruct.h"
#include <opencv2/opencv.hpp>
#include "PreDef.h"

using namespace std;
using namespace cv;

class IcarRegulator
{
private:
	int x, y, p, q;					//unknow parameter
	int resolution_x, resolution_y;			//image resolution
	int RealCarW, RealCarL, RealCarH;		//real width, length and height data of the vehicle
	Quadrilateral marks[MAX_CHL_NUM];		//mark points array
	Quadrilateral chess_marks[MAX_CHL_NUM];       	//mark points array
	IcarPoint centers[MAX_CHL_NUM];			//center points array

public:
	static const int BRP_FILE_NUM = 4;
	std::string usrBrpFile[BRP_FILE_NUM];

	ImageInfo canvas0;
	ImageInfo canvas1;
public:
	//construct an object without parameter
	IcarRegulator();
	
	//destruct an object
	~IcarRegulator();


	void setBrpFile(int n, std::string filename);

	//calibrate and splice the image of a camera (just in memory, not write to a file)
	void splice_Images(cv::Mat src, enum image_index index);

 	//only calibrate the center and splice the image of a camera (just in memory,not write to a file)
	void splice_Images_Center(cv::Mat src, enum image_index index);

	//only calibrate the mark and splice the image of a camera (just in memory,not write to a file)
	void splice_Images_Mark(cv::Mat src, enum image_index index);
	//adjust the four mark points of a camera (just in memory, not write to a file)
	void adjust_Marks(enum ui_operation opt, enum mark_index mark, enum image_index index);

	//adjust the center point of a camera (just in memory, not write to a file)
	void adjust_Centers(enum ui_operation opt, enum image_index index);

	//set the four mark points of a camera (just in memory, not write to a file)
	void set_Marks(Quadrilateral mark, enum image_index index);

	//set the center point of a camera (just in memory, not write to a file)
	void set_Centers(IcarPoint center, enum image_index index);

	//set the real width, length and height data of the vehicle (just in memory, not write to a file)
	void set_RealCarInfo(int width, int length, int height);

	//get the four mark points of a camera from memory
	Quadrilateral get_Mark(enum image_index index);

	//get the center point of a camera from memory
	IcarPoint get_Center(enum image_index index);
	
	//get the real width data of the vehicle from memory
	int get_RealCarW();

	//get the real length data of the vehicle from memory
	int get_RealCarL();

	//get the real height data of the vehicle from memory
	int get_RealCarH();

	//write the four mark points of four camera to a file
	void write_Marks(const char* filename);
	
	//write the four mark points of one camera to a file
	int write_Single_Marks(int id, const char *filename);

	//write the center point of four camera to a file
	void write_Centers(const char* filename);

	//write the center point of one camera to a file
    int write_Single_Centers(int id,const char *filename);

	//write the real width, length and height data of the vehicle to a file
	void write_RealCarInfo();

	bool write_CenterMark(const char* filename);

private:
	//adjust the specific mark point of a camera (just in memory, not write to a file)
	void adjust_LT(enum ui_operation opt, enum image_index index);
	void adjust_RT(enum ui_operation opt, enum image_index index);
	void adjust_LB(enum ui_operation opt, enum image_index index);
	void adjust_RB(enum ui_operation opt, enum image_index index);

	//read all mark points of four cameras mounted on the vehicle from a file
	void read_Marks(char* filename);
	
	//read all center point of four cameras mounted on the vehicle from a file
	void read_Centers(char* filename);

	//read the real width, length and height data of the vehicle from a file
	void read_RealCarInfo();
};

#endif
