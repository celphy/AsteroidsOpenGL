#include "projectileClass.h"

/// <summary>
/// Reduces lifetime and potentially flags as to be destroyed.
/// </summary>
void projectileClass::reduceLifetime() {
	this->lifetime--;
	if (lifetime == 0) {
		this->toBeDestroyed = true;
	}
}

/// <summary>
/// Returns remaining lifetime.
/// </summary>
/// <returns>Remaining lifetime</returns>
size_t projectileClass::getLifetime() {
	return lifetime;
}

/// <summary>
/// Constructor that does set objectType and lifetime.
/// </summary>
projectileClass::projectileClass()
{
	this->type = projectileType;
	lifetime = projectileLifetime;
	this->outline = new polygonClass();
}

/// <summary>
/// Destructor
/// </summary>
projectileClass::~projectileClass()
{
	delete this->outline;
}
