#include "physicsHandler.h"

/// <summary>
/// gameTick that moves the gameObjects and checks for collisions
/// </summary>
void physicsHandler::tick() {
	this->deleteObjects();
	this->move();
	this->collisionDetection();
}

/// <summary>
/// Deletes all flagged objects from the list of existing physicsObjects.
/// </summary>
void physicsHandler::deleteObjects() {
	for (auto it = physicsObjects.end() - 1; it != physicsObjects.begin(); /* We start at the end to have as little overhead as possible */)
	{
		if ((*it)->object->getType() == projectileType) {
			static_cast<projectileClass*>((*it)->object)->reduceLifetime();
		}

		if ((*it)->object->getDestroyed()) {
			//(*it)->object->deleteOutline(); //Try and free all unneeded memory
			//delete (*it)->object;
			//delete (*it);
			it = physicsObjects.erase(it);
		}

		
			--it;
	}
}

/// <summary>
/// Checks for collisions between all existing physicsObjects.
/// </summary>
void physicsHandler::collisionDetection() {
	//Empty out the list of collisions
	lastCollisions.clear();
	Point toTest;
	/*
	//Check by point in polygon method
	for (auto& it : this->physicsObjects) {
		for (auto& target : this->physicsObjects) {
			for (int i = 0; i < target->object->getOutline().getNumber(); i++) {
				toTest = target->object->getOutline().getPolygonPoint(i);
				toTest.x += target->object->getPosition().x;
				toTest.y += target->object->getPosition().y;
				if (it->object->getOutline().containsPoint(toTest)) {
					if (it->object->getType() == target->object->getType()) {
						break;
					}
					collisionStruct collisions;
					collisions.active = it;
					collisions.passive = target;
					lastCollisions.push_back(collisions);
					break;
				}
			}
		}
	}
	*/
	//Check by intersecting outline vectors
	for (auto& it : this->physicsObjects) {
		//Überspringe geprüfte äußere Elemente
		for (auto& target : this->physicsObjects) {
			if (it->object->getOutline().collidesWith(it->object->getPosition(), target->object->getOutline(), target->object->getPosition())) {
				if (it->object == target->object) {
					continue;
				}
				collisionStruct collisions;
				collisions.active = it;
				collisions.passive = target;
				lastCollisions.push_back(collisions);
			}
		}
	}
	
}

/// <summary>
/// Moves a physicsObject by impulse and takes friction into account.
/// </summary>
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

/// <summary>
/// Register a new gameObject as an existing physicsObject.
/// </summary>
/// <param name="gO">gameObject</param>
/// <param name="i">Impulse</param>
/// <param name="f">Friction</param>
/// <returns></returns>
physicsObject* physicsHandler::registerObject(gameObject* gO, Point i, float f ) {
	physicsObject* temp = new physicsObject;
	temp->impulse = i;
	temp->friction = f;
	temp->object = gO;
	this->physicsObjects.push_back(temp);
	return temp;
}

/// <summary>
/// Returns the last Collisions as a vector of structs.
/// </summary>
/// <returns>Vector of last collisions</returns>
vector<collisionStruct> physicsHandler::getLastCollisions()
{
	return lastCollisions;
}

/// <summary>
/// Constructor that sets up gameBoard with screenCutOff
/// </summary>
physicsHandler::physicsHandler()
{
	Point cutOff;
	cutOff.x = screenCutOff;
	cutOff.y = screenCutOff;
	this->gameScreen = new gameBoard(cutOff);
}

/// <summary>
/// Destructor
/// </summary>
physicsHandler::~physicsHandler()
{
	delete this->gameScreen;
}
