#pragma once
#include "gameObject.h"

class fontBuilder
{
private:
	fontBuilder() {}
public:
	gameObject* makeToText(Point p, float size);
	fontBuilder(fontBuilder const&) = delete;
	void operator=(fontBuilder const&) = delete;
	static fontBuilder& getInstance() {
		static fontBuilder instance;
		return instance;
	}
};

