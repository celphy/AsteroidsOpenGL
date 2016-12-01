#include "playerShip.h"

void playerShip::turnRight() {
	angle += 0.004f;
	this->rotate();
}

void playerShip::turnLeft() {
	angle -= 0.004f;
	this->rotate();
}

void playerShip::rotate() {

	Point p0, p1, p2;

	/*
	X = R * cos(Innenwinkel)
	Y = R * sin(Innenwinkel)
	*/
	//Following bit is useless but informative
	p0 = this->getOutline().getPolygonPoint(0);
	p1 = this->getOutline().getPolygonPoint(1);
	p2 = this->getOutline().getPolygonPoint(2);
	//Until here

	float angle1, angle2, angle3;
	angle1 = (this->angle + this->pointAngles[0]);
	angle2 = (this->angle + this->pointAngles[1]);
	angle3 = (this->angle + this->pointAngles[2]);


	//this->pointAngles[1] += 0.01;
	cout << "Angle 0 is at " << this->pointAngles[0] << endl;
	cout << "Angle 1 is at " << this->pointAngles[1] << endl;
	cout << "Angle 2 is at " << this->pointAngles[2] << endl;
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

playerShip::playerShip()
{
	this->angle = 0.0;

	Point p;
	p.x = 0.5f;
	p.y = 0.5f;

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
	this->radius = 0.2;

}


playerShip::~playerShip()
{
}
