#include "gameBoard.h"


/// <summary>
/// Translates a given position to a point on the gameBoard.
/// </summary>
/// <param name="position">Provided position</param>
/// <returns>Position on the gameBoard</returns>
Point gameBoard::translate(Point position) {
	Point temp = position;
	while (temp.x > cutOff.x) {
		temp.x = (-1) * cutOff.x;
	}
	while (temp.x < ((-1)*cutOff.x)) {
		temp.x = cutOff.x;
	}
	while (temp.y > cutOff.y) {
		temp.y = (-1) * cutOff.y;
	}
	while (temp.y < ((-1)*cutOff.y)) {
		temp.y = cutOff.y;
	}
	return temp;
}

/// <summary>
/// Returns edges of gameBoard
/// </summary>
/// <returns>edge cutoff</returns>
Point gameBoard::getCutOff() {
	return cutOff;
}

/// <summary>
/// Standard constructor
/// </summary>
gameBoard::gameBoard()
{
}

/// <summary>
/// Constructor that sets edge cutoff
/// </summary>
/// <param name="cO">Edge cutoff</param>
gameBoard::gameBoard(Point cO) {
	this->cutOff.x = cO.x;
	this->cutOff.y = cO.y;
}

/// <summary>
/// Destructor
/// </summary>
gameBoard::~gameBoard()
{
}
