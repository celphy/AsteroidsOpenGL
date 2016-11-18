#include "gameObject.h"
#include "point.h"

bool gameObject::setOutline(int num, GLfloat points[]) {
	for (int i = 0; i < num; i++) {
		this->outline.setPolygonPoint(i/2, points[i], points[i + 1]);
	} //Might work after all by setting i/2 as number
}

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
