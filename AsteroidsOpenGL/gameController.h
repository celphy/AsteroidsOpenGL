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
//Change project to use a polygonClass that handles raycasting collision themselves
//Make renderer and move stuff out of main.cpp
//User input
//Render player ship
//Use gameBoard
//Move the player ship
//Collision
//Asteroids destroying
//Make font class that creates scalable objects from string + position
//Text, lifes, points, highscore
//Cleanup, DEFINES!