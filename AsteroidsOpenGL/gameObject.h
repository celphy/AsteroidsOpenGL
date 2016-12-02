#pragma once
#include "main.h"
#include "polygonClass.h"

enum objectType { asteroid, player, saucer, projectile }; //We need this to differentiate between objects for collision handling

class gameObject
{
protected:
	objectType type;
	Point* position;
	polygonClass* outline;
public:
	void setOutline(int num, GLfloat points[]);
	Point getPosition();
	objectType getType();
	polygonClass getOutline();
	Point getRenderPoint(int num);
	void setPosition(Point p);
	gameObject();
	gameObject(Point p);
	~gameObject();
};

