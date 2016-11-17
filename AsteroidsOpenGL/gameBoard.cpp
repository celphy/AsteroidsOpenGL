#include "gameBoard.h"

Point gameBoard::translate(Point position) {
	Point temp = position;
	while (temp.x > cutOff.x) {
		temp.x -= cutOff.x;
	}
	while (temp.x < ((-1)*cutOff.x)) {
		temp.x += cutOff.x;
	}
	while (temp.y > cutOff.y) {
		temp.y -= cutOff.y;
	}
	while (temp.y < ((-1)*cutOff.y)) {
		temp.y += cutOff.y;
	}
}

Point gameBoard::getCutOff() {
	return cutOff;
}

gameBoard::gameBoard()
{
}

gameBoard::gameBoard(Point cO) {
	this->cutOff.x = cO.x;
	this->cutOff.y = cO.y;
}

gameBoard::~gameBoard()
{
}
