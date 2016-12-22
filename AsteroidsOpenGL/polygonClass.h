#pragma once
#include "main.h"
#include "point.h"
#include "vectorClass.h"


class polygonClass
{
	int n; //n-gon Hexagon etc
	//GLfloat outline[n]; //Here we need malloc from sdtlib but I'm not sure we are allowed to use it
	GLfloat *outline;
public:
	bool setPolygonPoint(int pos, GLfloat x, GLfloat y);
	bool setPolygonPoint(int pos, Point pNew);
	bool collidesWith(Point positionUs, polygonClass other, Point positionTheirs);
	Point getPolygonPoint(int n);
	bool containsPoint(Point p);
	int getNumber();
	polygonClass();
	polygonClass(int num);
	~polygonClass();
};

