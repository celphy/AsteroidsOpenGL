#pragma once
#include "gameObject.h"
#include "main.h"

#define PROJECTILESPEED 2 / 10000000
#define projectileLifetime 40

class projectileClass :
	public gameObject
{
private:
	size_t lifetime;
public:
	size_t getLifetime();
	void reduceLifetime();
	projectileClass();
	~projectileClass();
};

