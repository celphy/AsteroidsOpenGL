#include "VectorClass.h"

/// <summary>
/// Returns the intersection of two vectors
/// </summary>
/// <param name="v">Vector that is checked against</param>
/// <returns>Returns nullptr or point of intersection</returns>
Point* VectorClass::getIntersection(VectorClass v){
	float x1 = this->getOrigin().x, x2 = this->getDirection().x, x3 = v.getOrigin().x, x4 = v.getDirection().x;
	float y1 = this->getOrigin().y, y2 = this->getDirection().y, y3 = v.getOrigin().y, y4 = v.getDirection().y;

	float d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
	// Parallel?
	if (d == 0) return nullptr;
	// Deckungsgleich?
	if (d == 1) return nullptr;

	// X und Y des Schnittpunkts - danke Wikipedia
	float pre = (x1*y2 - y1*x2), post = (x3*y4 - y3*x4);
	float x = (pre * (x3 - x4) - (x1 - x2) * post) / d;
	float y = (pre * (y3 - y4) - (y1 - y2) * post) / d;

	// Ist der Schnittpunkt innerhalb der Linien?
	if (x < min(x1, x2) || x > max(x1, x2) ||
		x < min(x3, x4) || x > max(x3, x4)) return nullptr;
	if (y < min(y1, y2) || y > max(y1, y2) ||
		y < min(y3, y4) || y > max(y3, y4)) return nullptr;

	// Schnittpunkt
	Point* r = new Point();
	r->x = x;
	r->y = y;
	return r;
}

/// <summary>
/// Returns size of vector
/// </summary>
/// <returns>Size</returns>
double VectorClass::sizeOf(void) {
	return sqrt(pow(this->getOrigin().x + this->getDirection().x,2) + pow(this->getOrigin().y + this->getDirection().y,2));
}

/// <summary>
/// Normalizes the vector.
/// </summary>
void VectorClass::normVector(void) {
	double invNorm = 1 / this->sizeOf();
	this->direction.x *= invNorm;
	this->direction.y *= invNorm;
	this->origin.x *= invNorm;
	this->origin.y *= invNorm;
}

/// <summary>
/// Multiplies the vector by a factor.
/// </summary>
/// <param name="factor">Multiplication factor</param>
void VectorClass::multVector(float factor){
	this->direction.x *= factor;
	this->direction.y *= factor;
} 

/// <summary>
/// Adds a vector.
/// </summary>
/// <param name="v">Vector to add</param>
void VectorClass::addVector(vectorStruct v){
	this->direction.x += v.x;
	this->direction.y += v.y;
}

/// <summary>
/// Substracts a vector.
/// </summary>
/// <param name="v">Vector to substract</param>
void VectorClass::subVector(vectorStruct v){
	this->direction.x -= v.x;
	this->direction.y -= v.y;
}

/// <summary>
/// Returns the origin of the vector.
/// </summary>
/// <returns>Origin</returns>
vectorStruct VectorClass::getOrigin(){
	return this->origin;
}

/// <summary>
/// Returns the direction fo the vector.
/// </summary>
/// <returns></returns>
vectorStruct VectorClass::getDirection(){
	return this->direction;
}

/// <summary>
/// Sets the origin of the vector.
/// </summary>
/// <param name="oArg">Origin</param>
void VectorClass::setOrigin(vectorStruct oArg){
	this->origin = oArg;
}

/// <summary>
/// Sets the direction of the vector.
/// </summary>
/// <param name="dArg">Direction</param>
void VectorClass::setDirection(vectorStruct dArg){
	this->direction = dArg;
}

/// <summary>
/// Constructor that sets both origin and direction.
/// </summary>
/// <param name="oArg">Origin</param>
/// <param name="dArg">Direction</param>
VectorClass::VectorClass(vectorStruct oArg, vectorStruct dArg){
	this->origin = oArg;
	this->direction = dArg;
}

/// <summary>
/// Constructor that sets both origin and direction from points.
/// </summary>
/// <param name="one">Origin point</param>
/// <param name="two">Direction point</param>
VectorClass::VectorClass(Point one, Point two) {
	this->origin.x = one.x;
	this->origin.y = one.y;
	this->direction.x = two.x;
	this->direction.y = two.y;
}

/// <summary>
/// Standard constructor
/// </summary>
VectorClass::VectorClass(void)
{
}

/// <summary>
/// Destructor
/// </summary>
VectorClass::~VectorClass(void)
{
}
