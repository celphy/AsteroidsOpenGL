#pragma once
#include "main.h"
#include "physicsHandler.h"

//QueryPerformanceCounter

enum gameState {
	gameRunning, gamePause, gameEnd
};

class gameController
{
private:
	//Register player ship object
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
	gameController();
	~gameController();
};


//TODO
//Create class for player ship
//Register player ship with gameController
//User input
//Render player ship
//Use gameBoard
//Move the player ship
//Create class for asteroids
//Create projectile with lifetime
//Collision
//Asteroids destroying
//Text, lifes, points, highscore