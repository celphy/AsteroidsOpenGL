#include "polygonClass.h"

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
	outline = (GLfloat*)malloc(sizeof(GLfloat)*num*2); //Need double the size because 2 coords required
}

polygonClass::polygonClass()
{
}


polygonClass::~polygonClass()
{
}
