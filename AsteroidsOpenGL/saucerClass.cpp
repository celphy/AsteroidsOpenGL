#include "saucerClass.h"



saucerClass::saucerClass()
{
	this->type = saucerType;
	GLfloat outline[] = {
		0.0f, 0.03f,
		-0.05f, -0.05f,
		-0.15f, -0.10f,
		0.0f, -0.15f,
		0.15f, -0.1f,
		0.05f, -0.05f,
		0.0f, 0.03f,
		-0.05f, -0.05f,
		0.0f, -0.06f,
		0.05f, -0.05f,
	};
	this->setOutline(10, outline);
	this->toBeDestroyed = false;
}


saucerClass::~saucerClass()
{
}
