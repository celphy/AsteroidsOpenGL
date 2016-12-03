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
	bool toBeDestroyed;
public:
	void setOutline(int num, GLfloat points[]);
	bool getDestroyed();
	void markToDestroy();
	Point getPosition();
	objectType getType();
	polygonClass getOutline();
	void deleteOutline();
	Point getRenderPoint(int num);
	void setPosition(Point p);
	gameObject();
	gameObject(Point p);
	~gameObject();
};

