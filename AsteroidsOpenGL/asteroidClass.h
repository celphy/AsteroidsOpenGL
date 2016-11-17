#pragma once
#include "gameObject.h"

class asteroidClass :
	public gameObject
{
private:
	GLfloat outline[10];
	float size;
public:
	asteroidClass();
	asteroidClass(float s);
	~asteroidClass();
};

