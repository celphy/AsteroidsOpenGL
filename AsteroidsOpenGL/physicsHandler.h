#pragma once
#include "main.h"
#include "gameObject.h"
#include "gameBoard.h"

#define screenCutOff 1.1

//Remove on lifetime end
typedef struct physicsObject {
	gameObject *object;//reference to gameObject
	Point impulse;
	float friction;
}physicsObject;

class physicsHandler
{
private:
	//List of all existing gameObjects with additional stuff
	vector<physicsObject*> physicsObjects;
	gameBoard* gameScreen;

public:
	//Register gameObject with physicsHandler
	void registerObject ( gameObject* gO, Point i, float f);
	void tick();
	void move();
	void deleteObjects();
	void collisionDetection();
	physicsHandler();
	~physicsHandler();
};

