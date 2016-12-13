#include "gameLogic.h"

void gameLogic::reg(void* renderptr, physicsHandler* pHptr) {
	this->r = static_cast<renderer*>(renderptr);
	this->pH = pHptr;
}

gameLogic::gameLogic()
{
}


gameLogic::~gameLogic()
{
}
