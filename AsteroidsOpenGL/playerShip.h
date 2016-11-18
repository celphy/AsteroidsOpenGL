#pragma once
#include "main.h"
#include "gameObject.h"

class playerShip : public gameObject
{
private:
	float angle;
public:
	void turnLeft();
	void turnRight();
	playerShip();
	~playerShip();
};

