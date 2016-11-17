#pragma once
#include "main.h"

class gameObject
{
protected:
	Point position;
	GLfloat outline[];
public:
	Point getPosition();
	void setPosition(Point p);
	gameObject();
	gameObject(Point p);
	~gameObject();
};

