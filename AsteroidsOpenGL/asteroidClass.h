#pragma once
#include "gameObject.h"

class asteroidClass :
	public gameObject
{
private:
	float size; //Scale of our asteroid
public:
	float getSize();
	asteroidClass();
	asteroidClass(float s);
	~asteroidClass();
};
