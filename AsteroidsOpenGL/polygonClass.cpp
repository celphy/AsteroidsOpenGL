#include "polygonClass.h"

/// <summary>
/// Checks if this polygon colides with another one.
/// </summary>
/// <param name="other">Target polygon</param>
/// <returns>Collisions occured?</returns>
bool polygonClass::collidesWith(Point positionUs, polygonClass other, Point positionTheirs) { //TODO WE NEED TO TAKE OBJECT POSITION INTO ACCOUNT AS WELL!!!
	vector<vectorClass> ours, theirs;
	//Generate all vectors that represent us
	Point one, two;
	for (int i = 0; i < (this->n)-1; i++) {
		one = this->getPolygonPoint(i);
		one.x += positionUs.x;
		one.y += positionUs.y;
		two = this->getPolygonPoint(i + 1);
		two.x += positionUs.x;
		two.y += positionUs.y;
		ours.push_back(vectorClass(one, two));
	}
	one = this->getPolygonPoint(n - 1);
	one.x += positionUs.x;
	one.y += positionUs.y;
	two = this->getPolygonPoint(0);
	two.x += positionUs.x;
	two.y += positionUs.y;
	ours.push_back(vectorClass(one, two));

	//Generate all vectors that represent them
	for (int i = 0; i < (other.getNumber()-1); i++) {
		one = other.getPolygonPoint(i);
		one.x += positionTheirs.x;
		one.y += positionTheirs.y;
		two = other.getPolygonPoint(i + 1);
		two.x += positionTheirs.x;
		two.y += positionTheirs.y;
		theirs.push_back(vectorClass(one, two));
	}
	one = other.getPolygonPoint(other.getNumber() - 1);
	one.x += positionTheirs.x;
	one.y += positionTheirs.y;
	two = other.getPolygonPoint(0);
	two.x += positionTheirs.x;
	two.y += positionTheirs.y;
	theirs.push_back(vectorClass(one, two));

	//Now check all of ours vs all of theirs

	for (auto& us : ours) {
		for (auto& them : theirs) {
			if (us.getIntersection(them) != nullptr) //If we have one collision, thats enough!
				return true;
		}
	}
	return false;
}

/// <summary>
/// Returns numberOfPoints polygon is made up of.
/// </summary>
/// <returns>Number of sides.</returns>
int polygonClass::getNumber() {
	return n;
}

/// <summary>
/// Finds out if a point is inside the polygon or not.
/// </summary>
/// <param name="p">Point</param>
/// <returns>Point inside?</returns>
bool polygonClass::containsPoint(Point p, Point ownPosition) {
	//TODO use point that refers to actual gameBoard cutoff
	Point outside;
	outside.x = -2.0;
	outside.y = -2.0;
	vectorClass *testVector = new vectorClass(outside, p);
	int numberOfCollisions = 0;
	for (int i = 0; i < this->n; i++) {
		Point sideOne, sideTwo;
		if (i == 0) {
			sideOne = this->getPolygonPoint(n - 1);
			sideOne.x += ownPosition.x;
			sideTwo.y += ownPosition.y;
		}
		else {
			sideOne = this->getPolygonPoint(i - 1);
			sideOne.x += ownPosition.x;
			sideTwo.y += ownPosition.y;
		}
		sideTwo = this->getPolygonPoint(i);
		vectorClass *sideVector = new vectorClass(sideOne, sideTwo);
		if (sideVector->getIntersection(*testVector) != nullptr)
			numberOfCollisions++;
	}
	if (numberOfCollisions % 2)
		return true;
	return false;
}

/// <summary>
/// Set number of outline points.
/// </summary>
/// <param name="newNumberOfOutlinePoints">New number of outline points</param>
/// <returns>Old number of outline points</returns>
int polygonClass::setNumber(int newNumberOfOutlinePoints)
{
	int r = this->n;
	this->n = newNumberOfOutlinePoints;
	return r;
}

/// <summary>
/// Returns polygonPoint number n.
/// </summary>
/// <param name="n">Number of point</param>
/// <returns>Point</returns>
Point polygonClass::getPolygonPoint(int n) {
	Point r;
	r.x = this->outline[2 * n];
	r.y = this->outline[(2 * n) + 1];
	return r;
}

/// <summary>
/// Sets polygonPoint number n from point.
/// </summary>
/// <param name="pos">Point number</param>
/// <param name="pNew">New Point coordinates</param>
/// <returns>Returns success</returns>
bool polygonClass::setPolygonPoint(int pos, Point pNew) {
	return this->setPolygonPoint(pos, pNew.x, pNew.y);
}

/// <summary>
/// Sets polygonPoint number n from two floats.
/// </summary>
/// <param name="pos">Point number</param>
/// <param name="x">X-Coord</param>
/// <param name="y">Y-Coord</param>
/// <returns>Returns success</returns>
bool polygonClass::setPolygonPoint(int pos, GLfloat x, GLfloat y) {
	//Error handling
	if (pos < 0 || pos >= this->n)
		return false;
	//Pos 0 -> 0, 1 || Pos 1 -> 2, 3 || Pos 2 -> 4, 5 || Pos n -> 2n, 2n+1
	this->outline[2 * pos] = x;
	this->outline[(2 * pos) + 1] = y; //#works?
	return true;
}

/// <summary>
/// constructor that sets number of points from arguments.
/// </summary>
/// <param name="num">Number of points the polygon should have</param>
polygonClass::polygonClass(int num) { //Should we set GLfloat attribute for constructor?
	this->n = num;
	this->outline = new GLfloat[num * 2];
}

/// <summary>
/// Default constructor.
/// </summary>
polygonClass::polygonClass()
{
}

/// <summary>
/// Default destructor.
/// </summary>
polygonClass::~polygonClass()
{
	//delete this->outline;
	//this->outline = nullptr;
}
