#ifndef _IMGCOMMON_H_
#define _IMGCOMMON_H_

#include <iostream>



typedef struct{
	float x;
	float y;
}FPOINT;

typedef struct{
	int nx;
	int ny;
}NPOINT;

typedef struct{
	FPOINT stapnt;
	FPOINT endpnt;
}FRECT;

typedef struct{
	NPOINT stp;
	NPOINT edp;
}NRECT;


typedef struct {
	int w;
	int h;
    unsigned char *bmp;
	NRECT rgn;

}CANVAS;


struct Pix3UB{ 
	unsigned char r;
	unsigned char g;
	unsigned char b;
	inline void add(const Pix3UB& p3ub)
	{
		r += p3ub.r;
		g += p3ub.g;
		b += p3ub.b;
	}
	inline void dec(const Pix3UB& p3ub)
	{
		r -= p3ub.r;
		g -= p3ub.g;
		b -= p3ub.b;
	}
	inline void mul(const int factor)
	{
		r *= factor;
		g *= factor;
		b *= factor;
	}
	inline void div(const int factor)
	{
		r /= factor;
		g /= factor;
		b /= factor;
	}
	Pix3UB operator+(const Pix3UB& rhs) const
	{
        return{ (unsigned char)(r + rhs.r), (unsigned char)(g + rhs.g), (unsigned char)(b + rhs.b) };
	}
	Pix3UB operator-(const Pix3UB& rhs) const
	{
        return{ (unsigned char)(r - rhs.r), (unsigned char)(g - rhs.g), (unsigned char)(b - rhs.b) };
	}
	Pix3UB operator*(const int factor) const
	{
        return{ (unsigned char)(r*factor), (unsigned char)(g*factor), (unsigned char)(b*factor) };
	}
	Pix3UB operator/(const int factor) const
	{
        return{ (unsigned char)(r / factor), (unsigned char)(g / factor), (unsigned char)(b / factor) };
	}
	friend std::ostream& operator<<(std::ostream& os, const Pix3UB& p3ub){
		os << std::dec << "(" << (int)p3ub.r << "," << (int)p3ub.g << "," << (int)p3ub.b << ") ";
		return os;
	}

};


#endif
