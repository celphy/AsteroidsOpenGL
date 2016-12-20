#pragma once
#include "main.h"
#include "gameObject.h"
#include "vectorClass.h"
#include "physicsHandler.h"

#define turnSpeed 0.04f
#define playerSize 0.09f

class playerShip : public gameObject
{
private:
	float angle;
	float radius; //Radius of the circle on which the points will move
	//Because we rotate the ship we will need to store a relative angle for all points
	float pointAngles[3];
	physicsObject* self;
	
public:
	vectorClass getProjectileVector();
	void playerBoost();
	void rotate(); //Should be private
	void turnLeft();
	void turnRight();
	void setSelf(physicsObject* ptr);
	playerShip();
	~playerShip();
};

