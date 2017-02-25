#include "projectileClass.h"

/// <summary>
/// Sets the projectile to player friendly or the opposite.
/// </summary>
/// <param name="newFlag">New friendly flag</param>
void projectileClass::setFriendlyFlag(bool newFlag) {
	this->friendly = newFlag;
	if (!this->friendly) {
		friendly;
	}
}

/// <summary>
/// Returns if this projectile is friendly to the player.
/// </summary>
/// <returns>Friendly flag</returns>
bool projectileClass::getFriendlyFlag() {
	return this->friendly;
}

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
