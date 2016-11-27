#include "polygonClass.h"

int polygonClass::getNumber() {
	return n;
}

bool polygonClass::containsPoint(Point p) {
	//TODO use point that refers to actual gameBoard cutoff
	Point outside;
	outside.x = -2.0;
	outside.y = -2.0;
	VectorClass *testVector = new VectorClass(outside, p);
	int numberOfCollisions = 0;
	for (int i = 0; i < this->n; i++) {
		Point sideOne, sideTwo;
		if (i == 0) {
			sideOne = this->getPolygonPoint(n - 1);
		}
		else {
			sideOne = this->getPolygonPoint(i - 1);
		}
		sideTwo = this->getPolygonPoint(i);
		VectorClass *sideVector = new VectorClass(sideOne, sideTwo);
		if (sideVector->getIntersection(*testVector) != nullptr)
			numberOfCollisions++;
	}
	if (numberOfCollisions % 2)
		return true;
	return false;
}

Point polygonClass::getPolygonPoint(int n) {
	Point r;
	r.x = this->outline[2 * n];
	r.y = this->outline[(2 * n) + 1];
	return r;
}

bool polygonClass::setPolygonPoint(int pos, GLfloat x, GLfloat y) {
	//Error handling
	if (pos < 0 || pos >= this->n)
		return false;
	//Pos 0 -> 0, 1 || Pos 1 -> 2, 3 || Pos 2 -> 4, 5 || Pos n -> 2n, 2n+1
	this->outline[2 * n] = x;
	this->outline[(2 * n) + 1] = y; //#works?
	return true;
}

polygonClass::polygonClass(int num) { //Should we set GLfloat attribute for constructor?
	//outline = (GLfloat*)malloc(sizeof(GLfloat)*num*2); //Need double the size because 2 coords required
	this->n = num;
	this->outline = new GLfloat[num * 2];
}

polygonClass::polygonClass()
{
}


polygonClass::~polygonClass()
{
	//delete this->outline;
	//this->outline = nullptr;
}
