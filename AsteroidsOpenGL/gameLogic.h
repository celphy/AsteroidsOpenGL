#pragma once
#include "main.h"
#include "renderer.h"
#include "physicsHandler.h"
#include "playerShip.h"
#include "asteroidClass.h"
#include "VectorClass.h"
#include "projectileClass.h"

#define playerShotCooldown 20


class gameLogic
{
private:
	renderer* r;
	physicsHandler* pH;
	int playerScore;
	int playerLives;
	unsigned int asteroidCount;
	size_t shotCooldown;
public:
	void setupLevel();
	void addAsteroid(float s, Point impulse, Point position);
	void reg(void* renderptr, physicsHandler* pHptr);
	void registerGameObject(gameObject * obj, Point origin, float friction);
	void tick();
	void playerShoot(playerShip* player);
	gameLogic();
	~gameLogic();
};

