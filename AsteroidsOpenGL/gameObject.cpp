#include "gameObject.h"
#include "point.h"

void gameObject::markToDestroy() {
	this->toBeDestroyed = true;
}

bool gameObject::getDestroyed() {
	return this->toBeDestroyed;
}

void gameObject::deleteOutline() {
	delete this->outline;
}
objectType gameObject::getType() {
	return this->type;
}

Point gameObject::getRenderPoint(int num) {
	Point p;
	p.x = this->outline->getPolygonPoint(num).x + this->position->x;
	p.y = this->outline->getPolygonPoint(num).y + this->position->y;
	return p;
}

void gameObject::setOutline(int num, GLfloat points[]) {
	this->outline = new polygonClass(num);
	for (int i = 0; i < num; i++) {
		if(!this->outline->setPolygonPoint(i, points[2*i], points[(2*i) + 1]))
 			cout << "Major issue setting polygonPoints" << endl;
	} //Might work after all by setting i/2 as number
}

Point gameObject::getPosition() {
	return *position;
}

polygonClass gameObject::getOutline() {
	return *this->outline;
}

void gameObject::setPosition(Point p) {
	this->position->x = p.x;
	this->position->y = p.y;
}

gameObject::gameObject()
{
	this->position = new Point;
}

gameObject::gameObject(Point p) {
	this->toBeDestroyed = false;
	this->position = new Point;
	this->setPosition(p);
}


gameObject::~gameObject()
{
}
