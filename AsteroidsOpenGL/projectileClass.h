#pragma once
#include "gameObject.h"
#include "main.h"

#define PROJECTILESPEED 0.001

class projectileClass :
	public gameObject
{
private:
	size_t lifetime;
public:
	size_t getLifetime();
	projectileClass();
	~projectileClass();
};

