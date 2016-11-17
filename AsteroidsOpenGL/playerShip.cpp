#include "playerShip.h"

void playerShip::turnRight() {
	angle += 0.1;
}

void playerShip::turnLeft() {
	angle -= 0.1;
}

playerShip::playerShip()
{
}


playerShip::~playerShip()
{
}
