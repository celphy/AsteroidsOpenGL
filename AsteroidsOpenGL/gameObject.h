#pragma once
#include "main.h"
#include "polygonClass.h"

class gameObject
{
protected:
	Point position;
	polygonClass outline;
public:
	void setOutline(int num, GLfloat points[]);
	Point getPosition();
	polygonClass getOutline();
	void setPosition(Point p);
	gameObject();
	gameObject(Point p);
	~gameObject();
};

