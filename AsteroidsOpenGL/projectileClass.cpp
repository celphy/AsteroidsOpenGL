#include "projectileClass.h"

size_t projectileClass::getLifetime() {
	return lifetime;
}

projectileClass::projectileClass()
{
	this->type = projectileType;
	lifetime = projectileLifetime;
}


projectileClass::~projectileClass()
{
}
