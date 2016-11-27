#include "gameObject.h"
#include "point.h"

void gameObject::setOutline(int num, GLfloat points[]) {
	this->outline = new polygonClass(num);
	for (int i = 0; i < num; i++) {
		if(!this->outline->setPolygonPoint(i/2, points[i], points[i + 1]))
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
	this->position = new Point;
	this->setPosition(p);
}


gameObject::~gameObject()
{
}
