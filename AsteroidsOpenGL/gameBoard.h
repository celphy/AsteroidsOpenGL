#pragma once
#include "main.h"

class gameBoard
{
private:
	Point cutOff;
public:
	Point getCutOff();
	Point translate(Point position);
	gameBoard();
	gameBoard(Point cO);
	~gameBoard();
};

