#include "playerShip.h"

void playerShip::turnRight() {
	angle += 0.1f;
}

void playerShip::turnLeft() {
	angle -= 0.1f;
}

playerShip::playerShip()
{
	Point p;
	p.x = 1.0f;
	p.y = 1.0f;

	GLfloat outline[] = {
		0.0f,  0.2f,
		0.1f, -0.1f,
		-0.1f, -0.1f,
	}; //Fuck, do we need to add Z-position in 2d? maybe we can use a filler later in draw code
	this->setOutline(3, outline);

}


playerShip::~playerShip()
{
}
