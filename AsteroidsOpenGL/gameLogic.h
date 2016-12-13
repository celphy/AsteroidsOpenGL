#pragma once
#include "main.h"
#include "renderer.h"
#include "physicsHandler.h"


class gameLogic
{
private:
	renderer* r;
	physicsHandler* pH;
public:
	void reg(void* renderptr, physicsHandler* pHptr);
	gameLogic();
	~gameLogic();
};

