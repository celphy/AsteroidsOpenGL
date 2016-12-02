#include "physicsHandler.h"

void physicsHandler::tick() {
	this->move();
	this->collisionDetection();
}

void physicsHandler::collisionDetection() {
	for (auto& it : this->physicsObjects) {
		switch (it->object->getType()) {
		case asteroid:
			break;
		case player:
			break;
		case projectile:
			break;
		case saucer:
			break;
		default:
			break;
		}
	}
}

void physicsHandler::move() {
	for (auto& it : this->physicsObjects) {
		//Get current position
		Point newP;
		newP = it->object->getPosition();
		//Calculate new position
		newP.x += it->impulse.x;
		newP.y += it->impulse.y;
		//Teleport to new Point TODO: Check for collisions along the way
		it->object->setPosition(newP);
		//Friction applies?
		it->impulse.x *= it->friction;
		it->impulse.y *= it->friction;
	}
}

void physicsHandler::registerObject(gameObject* gO, Point i, float f ) {
	physicsObject* temp = new physicsObject;
	temp->impulse = i;
	temp->friction = f;
	temp->object = gO;
	this->physicsObjects.push_back(temp);
}

physicsHandler::physicsHandler()
{
	
}


physicsHandler::~physicsHandler()
{
}
