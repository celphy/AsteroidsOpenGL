#pragma once
#include "main.h"
#include "gameObject.h"
#include "gameBoard.h"
#include "asteroidClass.h"
#include "projectileClass.h"

#define screenCutOff 1.05

/// <summary>
/// Object information for physics engine.
/// </summary>
typedef struct physicsObject {
	gameObject *object;//reference to gameObject
	Point impulse;
	float friction;
}physicsObject;

/// <summary>
/// Tupel for collision recording.
/// </summary>
typedef struct collisionStruct {
	physicsObject* active;
	physicsObject* passive;
}collisionStruct;

/// <summary>
/// Physics engine supporting impulse and friction. Simple collision detection.
/// </summary>
class physicsHandler
{
private:
	//List of all existing gameObjects with additional stuff
	vector<physicsObject*> physicsObjects;
	gameBoard* gameScreen;
	vector<collisionStruct> lastCollisions;
	
public:
	//Register gameObject with physicsHandler
	physicsObject* registerObject ( gameObject* gO, Point i, float f);
	vector<collisionStruct> getLastCollisions();
	void tick();
	void move();
	void deleteObjects();
	void collisionDetection();
	physicsHandler();
	~physicsHandler();
};

