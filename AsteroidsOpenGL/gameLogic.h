#pragma once
#include "main.h"
#include "renderer.h"
#include "physicsHandler.h"
#include "playerShip.h"
#include "asteroidClass.h"



class gameLogic
{
private:
	renderer* r;
	physicsHandler* pH;
	int playerScore;
	int playerLives;
public:
	void setupLevel();
	void reg(void* renderptr, physicsHandler* pHptr);
	void registerGameObject(gameObject * obj, Point origin, float friction);
	void tick();
	gameLogic();
	~gameLogic();
};
