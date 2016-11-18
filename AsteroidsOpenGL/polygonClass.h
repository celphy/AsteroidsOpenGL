#pragma once
#include <stdlib.h>
#include "main.h"


class polygonClass
{
	int n; //n-gon Hexagon etc
	//GLfloat outline[n]; //Here we need malloc from sdtlib but I'm not sure we are allowed to use it
	GLfloat *outline;
public:
	bool setPolygonPoint(int n, GLfloat x, GLfloat y);
	bool containsPoint(Point p);
	polygonClass();
	polygonClass(int num);
	~polygonClass();
};

