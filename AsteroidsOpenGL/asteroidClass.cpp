#include "asteroidClass.h"

asteroidClass::asteroidClass(float s) {
	this->type = asteroid;
	this->size = s;
	GLfloat outline[] = {
		-1.0f*size, 1.0f*size,
		1.0f*size, 1.0f*size,
		1.0f*size, -1.0f*size,
		-1.0f*size, -1.0f*size,
	};
	this->setOutline(4, outline);
	
}

asteroidClass::asteroidClass()
{
	this->type = asteroid;
	size = 1.0;
	GLfloat outline[] = {
		-1.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, -1.0f,
		-1.0f, -1.0f,
	};//Fuck, do we need to add Z-position in 2d? maybe we can use a filler later in draw code
	this->setOutline(3, outline);
}


asteroidClass::~asteroidClass()
{
}
