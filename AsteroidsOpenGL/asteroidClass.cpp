#include "asteroidClass.h"

/// <summary>
/// Constructor that creates an asteroid according to the provided size.
/// Defines objectType and outline as well. Sets not to be destroyed.
/// </summary>
/// <param name="s">Size factor</param>
asteroidClass::asteroidClass(float s) {
	this->type = asteroidType;
	this->size = s;
	GLfloat outline[] = {
		-1.0f*size, 0.8f*size,
		-0.6f*size, 0.5f*size,
		0.7f*size, 0.8f*size,
		0.0f*size, 0.0f*size,
		0.6f*size, -0.5f*size,
		0.0f*size, -1.1f*size,
		-0.8f*size, -1.0f*size,
		-0.7f*size, -0.6f*size,
	};
	this->setOutline(8, outline);
	this->toBeDestroyed = false;
	
}

/// <summary>
/// Returns size factor
/// </summary>
/// <returns>size factor</returns>
float asteroidClass::getSize()
{
	return this->size;
}


/// <summary>
/// Standard Constructor, initializes objectType and sets up outline.
/// Sets not to be destroyed.
/// </summary>
asteroidClass::asteroidClass()
{
	this->type = asteroidType;
	size = 1.0;
	GLfloat outline[] = {
		-1.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, -1.0f,
		-1.0f, -1.0f,
	};
	this->setOutline(3, outline);
	this->toBeDestroyed = false;
}

/// <summary>
/// Destructor
/// </summary>
asteroidClass::~asteroidClass()
{
}
