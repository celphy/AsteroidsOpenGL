#pragma once
#include "main.h"
#include "physicsHandler.h"
#include "playerShip.h"
//#include "renderer.h"
#include "gameLogic.h"

//QueryPerformanceCounter

enum gameState {
	gameRunning, gamePause, gameEnd
};

class gameController
{
private:
	playerShip *player;
	physicsHandler *pH;
	//renderer* r;
	gameLogic* logic;
	gameState state;
	int tickRatePS;
	int maxShots;
	double lastTick;
	double PCFreq = 0.0;
	__int64 CounterStart;
	void StartPerformanceCounter();
	double GetPerformanceCounter();
	bool rotateLeft, rotateRight, boost;

public:
	enum gameState getGameState();
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
	void togglePause();
	void end();
	void run();
	void setHandlers(void* renderer, physicsHandler* ptr);
	void setPlayerShip(playerShip *ptr);
	gameController();
	~gameController();
};


//TODO
//Collision & gameLogic
//Asteroids destroying
//Add saucer
//Make font class that creates scalable objects from string + position
//Text, lifes, points, highscore
//Cleanup, DEFINES!