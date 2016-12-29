#include "gameObject.h"
#include "point.h"

string gameObject::toString() {
	string output;
	output = "Position: ";
	output += to_string(this->getPosition().x);
	output += "/";
	output += to_string(this->getPosition().y);
	output += " Destroy:";
	if (this->getDestroyed())
		output += " true";
	else
		output += " false";
	return output;
}

/// <summary>
/// Marks the object to be destroyed in the next gameTick.
/// </summary>
void gameObject::markToDestroy() {
	this->toBeDestroyed = true;
}

/// <summary>
/// Returns if it should be destroyed.
/// </summary>
/// <returns></returns>
bool gameObject::getDestroyed() {
	//return false;
	return this->toBeDestroyed;
	//return this->toBeDestroyed; WHY DOES THIS RETURN TRUE???
}

/// <summary>
/// Deletes the outline memory.
/// </summary>
void gameObject::deleteOutline() {
	delete this->outline;
}

/// <summary>
/// Returns the objectType.
/// </summary>
/// <returns></returns>
objectType gameObject::getType() {
	return this->type;
}

/// <summary>
/// Returns render point number num.
/// </summary>
/// <param name="num">Number of render point</param>
/// <returns>Returns render point</returns>
Point gameObject::getRenderPoint(int num) {
	Point p;
	p.x = this->outline->getPolygonPoint(num).x + this->position->x;
	p.y = this->outline->getPolygonPoint(num).y + this->position->y;
	return p;
}

/// <summary>
/// Sets the outline to a number of points
/// </summary>
/// <param name="num">Number of point to change</param>
/// <param name="points">Point it should be set to</param>
void gameObject::setOutline(int num, GLfloat points[]) {
	this->outline = new polygonClass(num);
	for (int i = 0; i < num; i++) {
		if(!this->outline->setPolygonPoint(i, points[2*i], points[(2*i) + 1]))
 			cout << "Major issue setting polygonPoints" << endl;
	} //Might work after all by setting i/2 as number
	this->outline->setNumber(num);
}

/// <summary>
/// Returns current position.
/// </summary>
/// <returns>Returns the position as a point</returns>
Point gameObject::getPosition() {
	return *position;
}

/// <summary>
/// Returns the outline.
/// </summary>
/// <returns>Outline as polygonClass</returns>
polygonClass gameObject::getOutline() {
	return *this->outline;
}

/// <summary>
/// Sets current position.
/// </summary>
/// <param name="p">New position</param>
void gameObject::setPosition(Point p) {
	this->position->x = p.x;
	this->position->y = p.y;
}

/// <summary>
/// Default constructor only creates space for the position.
/// Doesnt actually set anything.
/// </summary>
gameObject::gameObject()
{
	this->position = new Point;
	this->toBeDestroyed = false;
}

/// <summary>
/// Constructor that creates the gameObject with a position and not to be destroyed flag.
/// </summary>
/// <param name="p"></param>
gameObject::gameObject(Point p) {
	this->toBeDestroyed = false;
	this->position = new Point;
	this->setPosition(p);
}

/// <summary>
/// Destructor
/// </summary>
gameObject::~gameObject()
{
}
