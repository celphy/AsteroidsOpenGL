#include "projectileClass.h"

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
