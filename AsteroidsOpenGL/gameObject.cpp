#include "gameObject.h"
#include "point.h"

Point gameObject::getPosition() {
	return this->position;
}

void gameObject::setPosition(Point p) {
	this->position.x = p.x;
	this->position.y = p.y;
}

gameObject::gameObject()
{
}

gameObject::gameObject(Point p) {
	this->setPosition(p);
}


gameObject::~gameObject()
{
}
