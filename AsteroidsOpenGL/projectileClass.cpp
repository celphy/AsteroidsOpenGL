#include "projectileClass.h"

size_t projectileClass::getLifetime() {
	return lifetime;
}

projectileClass::projectileClass()
{
	this->type = projectile;
	lifetime = projectileLifetime;
}


projectileClass::~projectileClass()
{
}
