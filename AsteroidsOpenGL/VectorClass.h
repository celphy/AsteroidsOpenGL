#pragma once
#include <cmath>
#include "main.h"
#include "point.h"

//Vector == Point but improves readability
typedef struct vectorStruct {
	float x;
	float y;
}vectorStruct;


class VectorClass
{
private:
	vectorStruct origin;
	vectorStruct direction;
	
public:
	Point* getIntersection(VectorClass vector); //Result can be 0, Point or Vector
	void addVector(vectorStruct v);
	void subVector(vectorStruct v);
	void multVector(float factor);
	void normVector(void);
	double sizeOf(void);
	vectorStruct getOrigin(void);
	vectorStruct getDirection(void);
	void setOrigin(vectorStruct oArg);
	void setDirection(vectorStruct dArg);
	VectorClass(void);
	VectorClass(vectorStruct oArg, vectorStruct dArg);
	VectorClass(Point one, Point two);
	~VectorClass(void);
};

