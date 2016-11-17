#include "projectileClass.h"

size_t projectileClass::getLifetime() {
	return lifetime;
}

projectileClass::projectileClass()
{
	lifetime = projectileLifetime;
}


projectileClass::~projectileClass()
{
}
