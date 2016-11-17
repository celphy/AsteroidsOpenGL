#include "VectorClass.h"

VectorClass VectorClass::getIntersection(VectorClass v){
	Point startl1, endl1; //Line 1
	Point startl2, endl2; //Line 2

	startl1.x = this->origin.x;
	startl1.y = this->origin.y;
	endl1.x = this->origin.x + this->direction.x;
	endl2.y = this->origin.y + this->direction.y;

	startl2.x = v.getOrigin().x;
	startl2.y = v.getOrigin().y;
	endl2.x = v.getOrigin().x + v.getDirection().x;
	endl2.y = v.getOrigin().y + v.getDirection().y;

	//Check for zero
	float resultCheck = ((startl1.x - endl1.x)*(startl2.y - endl2.y) - (startl1.y - endl1.y)(startl2.x - endl2.x));
	if(resultCheck == 0.0){
		vector empty;
		empty.x = 0.0f;
		empty.y = 0.0f;
		VectorClass r = VectorClass(empty, empty);
		return r;
	}
	//TODO: Not-zero logic
	return *this;

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

VectorClass::VectorClass(void)
{
}


VectorClass::~VectorClass(void)
{
}
