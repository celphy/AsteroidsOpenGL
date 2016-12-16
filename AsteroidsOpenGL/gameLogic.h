#pragma once
#include "main.h"
#include "renderer.h"
#include "physicsHandler.h"
#include <tuple>



class gameLogic
{
private:
	renderer* r;
	physicsHandler* pH;
	int playerScore;
	//vector<physicsObject*, physicsObject*> currentCollisions;
public:
	void reg(void* renderptr, physicsHandler* pHptr);
	void registerGameObject(gameObject * obj, Point origin, float friction);
	void tick();
	void reportCollision(physicsObject* first, physicsObject* second);
	gameLogic();
	~gameLogic();
};

