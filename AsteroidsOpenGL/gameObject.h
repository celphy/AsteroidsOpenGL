#pragma once
#include "main.h"
#include "polygonClass.h"

class gameObject
{
protected:
	Point position;
	polygonClass outline;
public:
	bool setOutline(int num, GLfloat points[]);
	Point getPosition();
	void setPosition(Point p);
	gameObject();
	gameObject(Point p);
	~gameObject();
};

