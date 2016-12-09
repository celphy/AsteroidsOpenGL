#include "polygonClass.h"

bool polygonClass::collidesWith(polygonClass other) { //TODO
	vector<VectorClass> ours, theirs;
	//Generate all vectors that represent us
	for (int i = 0; i < (this->n)-2; i++) {
		ours.push_back(VectorClass(this->getPolygonPoint(i), this->getPolygonPoint(i+1)));
	}
	ours.push_back(VectorClass(this->getPolygonPoint(n-1), this->getPolygonPoint(0)));

	//Generate all vectors that represent them
	for (int i = 0; i < (other.getNumber()-2); i++) {
		theirs.push_back(VectorClass(other.getPolygonPoint(i), other.getPolygonPoint(i + 1)));
	}
	theirs.push_back(VectorClass(other.getPolygonPoint(other.getNumber() - 1), other.getPolygonPoint(0)));

	//Now check all of ours vs all of theirs

	for (auto& us : ours) {
		for (auto& them : theirs) {
			if (us.getIntersection(them) != nullptr) //If we have one collision, thats enough!
				return true;
		}
	}
	return false;
}

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

bool polygonClass::setPolygonPoint(int pos, Point pNew) {
	return this->setPolygonPoint(pos, pNew.x, pNew.y);
}

bool polygonClass::setPolygonPoint(int pos, GLfloat x, GLfloat y) {
	//Error handling
	if (pos < 0 || pos >= this->n)
		return false;
	//Pos 0 -> 0, 1 || Pos 1 -> 2, 3 || Pos 2 -> 4, 5 || Pos n -> 2n, 2n+1
	this->outline[2 * pos] = x;
	this->outline[(2 * pos) + 1] = y; //#works?
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
