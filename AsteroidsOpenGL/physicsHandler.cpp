#include "physicsHandler.h"

void physicsHandler::tick() {
	this->deleteObjects();
	this->move();
	this->collisionDetection();
}

void physicsHandler::deleteObjects() {
	for (auto it = physicsObjects.end() - 1; it != physicsObjects.begin(); /* We start at the end to have as little overhead as possible */)
	{
		if ((*it)->object->getDestroyed()) {
			(*it)->object->deleteOutline(); //Try and free all unneeded memory
			delete (*it)->object;
			delete (*it);
			it = physicsObjects.erase(it);
		}
		else
			--it;
	}
}

void physicsHandler::collisionDetection() {
	for (auto& it : this->physicsObjects) {
		if (it->object->getType() == player) {

		}
		else if (it->object->getType() == projectile) {
			for (auto& target : this->physicsObjects) {
				if (target->object->getOutline().containsPoint(it->object->getPosition()))
					target->object->markToDestroy();
			}
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
		//Wrap around edges
		newP = gameScreen->translate(newP);
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
	Point cutOff;
	cutOff.x = 1.1;
	cutOff.y = 1.1;
	this->gameScreen = new gameBoard(cutOff);
}


physicsHandler::~physicsHandler()
{
	delete this->gameScreen;
}
