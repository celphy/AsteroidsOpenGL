#pragma once
#include "main.h"

class gameObject
{
protected:
	Point position;
public:
	Point getPosition();
	void setPosition(Point p);
	gameObject();
	gameObject(Point p);
	~gameObject();
};

