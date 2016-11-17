#pragma once
#include "main.h"
#include "gameObject.h"


//Remove on lifetime end
typedef struct physicsObject {
	gameObject *object;//reference to gameObject
	Point impulse;
	float friction;
	physicsObject *next;
};

class physicsHandler
{
private:
	physicsObject *first;
	//List of all existing gameObjects
public:
	//Register gameObject with physicsHandler
	void registerObject ( gameObject* gO, Point i, float f);
	void tick();
	physicsHandler();
	~physicsHandler();
};

