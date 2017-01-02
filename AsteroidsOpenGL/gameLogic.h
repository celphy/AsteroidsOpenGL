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
#define timeBetweenSaucerTurns 40
#define asteroidScore 50
#define saucerScore 100


class gameLogic
{
private:
	renderer* r;
	physicsHandler* pH;
	physicsObject *activeSaucer;
	bool saucerActive;
	int playerScore;
	int playerLives;
	unsigned int asteroidCount;
	size_t shotCooldown;
	size_t saucerTurnCounter;
	bool playerHit;
public:
	void setupLevel();
	void addAsteroid(float s, Point impulse, Point position);
	void reg(void* renderptr, physicsHandler* pHptr);
	physicsObject* registerGameObject(gameObject * obj, Point origin, float friction);
	void addSaucer(Point impulse, Point position);
	void tick();
	void playerShoot(playerShip* player);
	void saucerTurn();
	void centerPlayer(gameObject* player);
	gameLogic();
	~gameLogic();
};

