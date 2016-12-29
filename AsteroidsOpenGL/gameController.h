#pragma once
#include "main.h"
#include "physicsHandler.h"
#include "playerShip.h"
//#include "renderer.h"
#include "gameLogic.h"

#define TickRatePS 60

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
	int maxShots;
	LARGE_INTEGER lastTick, Frequency, tickThreshold;
	void StartPerformanceCounter();
	bool rotateLeft, rotateRight, boost, firstStart;
	

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
//Invincible period for player
//Add saucer
//Make font class that creates scalable objects from string + position
//Text, lifes, points, highscore
//Cleanup, DEFINES!