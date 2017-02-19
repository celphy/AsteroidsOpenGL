#include "saucerClass.h"



saucerClass::saucerClass()
{
	this->type = saucerType;
	float size = 0.5;
	GLfloat outline[] = {
		0.0f * size, 0.03f * size,
		-0.05f * size, -0.05f * size,
		-0.15f * size, -0.10f * size,
		0.0f * size, -0.15f * size,
		0.15f * size, -0.1f * size,
		0.05f * size, -0.05f * size,
		0.0f * size, 0.03f * size,
		-0.05f * size, -0.05f * size,
		0.0f * size, -0.06f * size,
		0.05f * size, -0.05f * size,
	};
	this->setOutline(10, outline);
	this->toBeDestroyed = false;
}


saucerClass::~saucerClass()
{
}
