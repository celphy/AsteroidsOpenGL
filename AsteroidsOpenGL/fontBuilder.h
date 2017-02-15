#pragma once
#include "gameObject.h"


class fontBuilder
{
private:
	
	Point* segments;

	fontBuilder() {

		segments = nullptr;

		Point lt, rt, lm, rm, bl, br;
		lt.x = 0.01;
		lt.y = -0.01;
		rt.x = 0.3;
		rt.y = -0.01;
		lm.x = 0.01;
		lm.x = -0.15;
		rm.x = 0.3;
		rm.y = -0.15;
		bl.x = 0.01;
		bl.y = -0.3;
		br.x = 0.3;
		br.y = -0.3;

		segments = new Point[6];
		segments[0] = lt;
		segments[1] = rt;
		segments[2] = lm;
		segments[3] = rm;
		segments[4] = bl;
		segments[5] = br;
	}

	~fontBuilder() {
		delete segments;
	}
	

public:
	gameObject* makeToText(int number, Point p, float size);

	fontBuilder(fontBuilder const&) = delete;
	void operator=(fontBuilder const&) = delete;
	static fontBuilder& getInstance() {
		static fontBuilder instance;
		return instance;
	}
};

