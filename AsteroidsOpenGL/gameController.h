#pragma once
#include "main.h"
#include "physicsHandler.h"
#include "playerShip.h"

//QueryPerformanceCounter

enum gameState {
	gameRunning, gamePause, gameEnd
};

class gameController
{
private:
	//Register player ship object
	playerShip *player;
	gameState state;
	int tickRatePS;
	int maxShots;
	physicsHandler *pH;
	double PCFreq = 0.0;
	__int64 CounterStart;
	void StartPerformanceCounter();
	double GetPerformanceCounter();

public:
	//Score keeping
	//User input
	void run();
	void setPhysicsHandler(physicsHandler* ptr);
	void setPlayerShip(playerShip *ptr);
	gameController();
	~gameController();
};


//TODO
//User input
//Render player ship
//Use gameBoard
//Move the player ship
//Collision
//Asteroids destroying
//Text, lifes, points, highscore
//Cleanup, DEFINES!