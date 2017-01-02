#pragma once
#include "main.h"
#include "renderer.h"
#include "physicsHandler.h"
#include "playerShip.h"
#include "asteroidClass.h"
#include "VectorClass.h"
#include "projectileClass.h"
#include "saucerClass.h"

#define playerShotCooldown 20
#define asteroidScore 50
#define saucerScore 100


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
	void addSaucer(Point impulse, Point position);
	void tick();
	void playerShoot(playerShip* player);
	gameLogic();
	~gameLogic();
};

