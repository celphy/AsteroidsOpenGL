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
	playerShip *player;
	gameState state;
	int tickRatePS;
	int maxShots;
	double lastTick;
	physicsHandler *pH;
	double PCFreq = 0.0;
	__int64 CounterStart;
	void StartPerformanceCounter();
	double GetPerformanceCounter();
	bool rotateLeft, rotateRight, boost;
	int playerScore;

public:
	enum gameState getGameState();
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
	void raiseScore(int amount);
	void playerCollision();
	void togglePause();
	void end();
	void run();
	void setPhysicsHandler(physicsHandler* ptr);
	void setPlayerShip(playerShip *ptr);
	gameController();
	~gameController();
};


//TODO
//Collision
//Asteroids destroying
//Add saucer
//Make font class that creates scalable objects from string + position
//Text, lifes, points, highscore
//Cleanup, DEFINES!