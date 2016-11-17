#pragma once
#include "gameObject.h"

class playerShip : public gameObject
{
private:
	GLfloat outline[3];
	float angle;
public:
	void turnLeft();
	void turnRight();
	playerShip();
	~playerShip();
};

