#include "playerShip.h"

/// <summary>
/// Increases impulse of player in the direction the ship is facing.
/// </summary>
void playerShip::playerBoost() {
	VectorClass vector;
	vector = this->getProjectileVector();
	vectorStruct additionalImpulse;
	additionalImpulse.x = vector.getDirection().x - vector.getOrigin().x;
	additionalImpulse.y = vector.getDirection().y - vector.getOrigin().y;
	additionalImpulse.x *= 0.01;
	additionalImpulse.y *= 0.01;
	this->self->impulse.x += additionalImpulse.x;
	this->self->impulse.y += additionalImpulse.y;
}

/// <summary>
/// Returns a vector into the direction the ship is facing.
/// </summary>
/// <returns>Vector the ship is facing</returns>
VectorClass playerShip::getProjectileVector() {
	Point middle;
	middle.x = this->outline->getPolygonPoint(1).x + this->outline->getPolygonPoint(2).x;
	middle.y = this->outline->getPolygonPoint(1).y + this->outline->getPolygonPoint(2).y;
	middle.x /= 2;
	middle.y /= 2;
	Point front = this->outline->getPolygonPoint(0);

	VectorClass r = VectorClass(middle, front);
	return r;
}

/// <summary>
/// Turns the players ship to the right
/// </summary>
void playerShip::turnRight() {
	angle += turnSpeed;
	this->rotate();
}


/// <summary>
/// Sets the pointer inside to the physicsObject for the player.
/// Used for acceleration.
/// </summary>
/// <param name="ptr"></param>
void playerShip::setSelf(physicsObject * ptr)
{
	this->self = ptr;
}


/// <summary>
/// Turn the players ship to the left.
/// </summary>
void playerShip::turnLeft() {
	angle -=turnSpeed;
	this->rotate();
}

/// <summary>
/// Rotate the player ships outline to match the direction it should be facing.
/// </summary>
void playerShip::rotate() {

	Point p0, p1, p2;

	/*
	X = R * cos(Innenwinkel)
	Y = R * sin(Innenwinkel)
	*/
	//Following bit is useless but informative
	/*
	p0 = this->getOutline().getPolygonPoint(0);
	p1 = this->getOutline().getPolygonPoint(1);
	p2 = this->getOutline().getPolygonPoint(2);
	*/

	float angle1, angle2, angle3;
	angle1 = (this->angle + this->pointAngles[0]);
	angle2 = (this->angle + this->pointAngles[1]);
	angle3 = (this->angle + this->pointAngles[2]);


	//this->pointAngles[1] += 0.01;
	if (DEBUG_OUTPUT) {
		cout << "Angle 0 is at " << this->pointAngles[0] << endl;
		cout << "Angle 1 is at " << this->pointAngles[1] << endl;
		cout << "Angle 2 is at " << this->pointAngles[2] << endl;
	}
	p0.x = this->radius * sin(angle1);
	p0.y = this->radius * cos(angle1);
	p1.x = this->radius * sin(angle2);
	p1.y = this->radius * cos(angle2);
	p2.x = this->radius * sin(angle3);
	p2.y = this->radius * cos(angle3);
	
	/*
	p0.x = this->radius * cos(angle1);
	p0.y = this->radius * sin(angle1);
	p1.x = this->radius * cos(angle2);
	p1.y = this->radius * sin(angle2);
	p2.x = this->radius * cos(angle3);
	p2.y = this->radius * sin(angle3);
	*/
	this->getOutline().setPolygonPoint(0, p0);
	this->getOutline().setPolygonPoint(1, p1);
	this->getOutline().setPolygonPoint(2, p2);
}

/// <summary>
/// Constructor that sets direction, objectType, position, outline and size of the ship.
/// </summary>
playerShip::playerShip()
{
	this->angle = 0.0;
	this->type = playerType;

	Point p;
	p.x = 0.0f;
	p.y = 0.0f;

	GLfloat outline[] = {
		0.0f,  0.2f,
		0.1f, -0.1f,
		-0.1f, -0.1f,
	}; //Fuck, do we need to add Z-position in 2d? maybe we can use a filler later in draw code
	this->setOutline(3, outline);
	this->setPosition(p);
	this->pointAngles[0] = 0;
	this->pointAngles[1] = 2.43; //2.13
	this->pointAngles[2] = 3.86; //4.16
	this->radius = playerSize;
	

}

/// <summary>
/// Destructor
/// </summary>
playerShip::~playerShip()
{
}
