#pragma once
#include "main.h"
#include "gameObject.h"

#define turnSpeed 0.03f

class playerShip : public gameObject
{
private:
	float angle;
	float radius; //Radius of the circle on which the points will move
	//Because we rotate the ship we will need to store a relative angle for all points
	float pointAngles[3];
	
public:
	void rotate(); //Should be private
	void turnLeft();
	void turnRight();
	playerShip();
	~playerShip();
};

