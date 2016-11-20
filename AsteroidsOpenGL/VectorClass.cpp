#include "VectorClass.h"

Point* VectorClass::getIntersection(VectorClass v){
	float x1 = this->getOrigin().x, x2 = this->getDirection().x, x3 = v.getOrigin().x, x4 = v.getDirection().x;
	float y1 = this->getOrigin().y, y2 = this->getDirection().y, y3 = v.getOrigin().y, y4 = v.getDirection().y;

	float d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
	// Parallel?
	if (d == 0) return nullptr;
	// Deckungsgleich?
	if (d == 1) return nullptr;

	// X und Y des Schnittpunkts - danke Wikipedia
	float pre = (x1*y2 - y1*x2), post = (x3*y4 - y3*x4);
	float x = (pre * (x3 - x4) - (x1 - x2) * post) / d;
	float y = (pre * (y3 - y4) - (y1 - y2) * post) / d;

	// Ist der Schnittpunkt innerhalb der Linien?
	if (x < min(x1, x2) || x > max(x1, x2) ||
		x < min(x3, x4) || x > max(x3, x4)) return nullptr;
	if (y < min(y1, y2) || y > max(y1, y2) ||
		y < min(y3, y4) || y > max(y3, y4)) return nullptr;

	// Schnittpunkt
	Point* r = new Point();
	r->x = x;
	r->y = y;
	return r;
}



void VectorClass::multVector(float factor){
	this->direction.x *= factor;
	this->direction.y *= factor;
} 


void VectorClass::addVector(vector v){
	this->direction.x += v.x;
	this->direction.y += v.y;
}

void VectorClass::subVector(vector v){
	this->direction.x -= v.x;
	this->direction.y -= v.y;
}

vector VectorClass::getOrigin(){
	return this->origin;
}

vector VectorClass::getDirection(){
	return this->direction;
}

void VectorClass::setOrigin(vector oArg){
	this->origin = oArg;
}

void VectorClass::setDirection(vector dArg){
	this->direction = dArg;
}

VectorClass::VectorClass(vector oArg, vector dArg){
	this->origin = oArg;
	this->direction = dArg;
}

VectorClass::VectorClass(Point one, Point two) {
	this->origin.x = one.x;
	this->origin.y = one.y;
	this->direction.x = two.x;
	this->direction.y = two.y;
}

VectorClass::VectorClass(void)
{
}


VectorClass::~VectorClass(void)
{
}
