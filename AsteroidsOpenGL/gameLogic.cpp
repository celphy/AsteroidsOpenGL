#include "gameLogic.h"

/// <summary>
/// Gets called when the player tries to shoot.
/// </summary>
/// <param name="player">Pointer to player object</param>
void gameLogic::playerShoot(playerShip* player) {
	//Get the projectileVector that playerShip provides us with. Its a vector from playerShip->position to the front.
	vectorClass projectileVector;
	projectileVector = player->getProjectileVector();
	//Set up a projectile from the front facing in the same direction the playerShip is.	
	projectileClass* projectile = new projectileClass();
	Point projectilePosition;
	projectilePosition.x = player->getOutline().getPolygonPoint(0).x + player->getPosition().x;
	projectilePosition.y = player->getOutline().getPolygonPoint(0).y + player->getPosition().y;
	projectile->setPosition(projectilePosition);
	GLfloat* points = new GLfloat[4];
	points[0] = projectileVector.getOrigin().x;
	points[1] = projectileVector.getOrigin().y;
	points[2] = projectileVector.getDirection().x;
	points[3] = projectileVector.getDirection().y;
	projectile->setOutline(2, points);
	projectileVector.multVector(PROJECTILESPEED);
	Point impulse;
	impulse.x = projectileVector.getDirection().x - projectileVector.getOrigin().x;
	impulse.y = projectileVector.getDirection().y - projectileVector.getOrigin().y;
	
	this->registerGameObject(projectile, impulse, 1.0);
}

/// <summary>
/// Register the renderer (drawing) and physicsHandler (movement) instances with the gameLogic
/// </summary>
/// <param name="renderptr">renderer instance</param>
/// <param name="pHptr">physicsHandler instance</param>
void gameLogic::reg(void* renderptr, physicsHandler* pHptr) {
	this->r = static_cast<renderer*>(renderptr);
	this->pH = pHptr;
}

/// <summary>
/// Registers a gameObject with both the renderer (drawing) and the pyhsicsHandler (movement)
/// </summary>
/// <param name="obj">gameObject</param>
/// <param name="impulse">initial impulse</param>
/// <param name="friction">friction in physicsHandler</param>
void gameLogic::registerGameObject(gameObject * obj, Point impulse, float friction)
{
	//this->r->addGame(obj);
	this->r->registerObject(true, obj);
	this->pH->registerObject(obj, impulse, friction);
}

/// <summary>
/// Resolve the reported collisions, update the gameState accordingly
/// </summary>
void gameLogic::tick()
{
	//resolve collisions, update gamestate
	vector<collisionStruct> lastCollisions = this->pH->getLastCollisions();
	for (auto& it : lastCollisions) {
		if (it.passive->object->getType() == playerType && it.active->object->getType() != playerType) { //Player got hit
			if (DEBUG_OUTPUT)
			cout << "Player got hit" << endl;
		}
		if (it.passive->object->getType() == asteroidType && it.active->object->getType() == projectileType) {
			if (DEBUG_OUTPUT) 
			cout << "Asteroid got hit by projectile!" << endl;
			it.passive->object->markToDestroy();
			it.active->object->markToDestroy();
			this->playerScore += 50;
			system("cls");
			cout << "Player score: " << this->playerScore << endl;
			asteroidClass* smallerOne, *smallerTwo;
			smallerOne = new asteroidClass(0.05);
			smallerTwo = new asteroidClass(0.05);
			smallerOne->setPosition(it.passive->object->getPosition());
			smallerTwo->setPosition(it.passive->object->getPosition());
			Point impulse;
			impulse = it.passive->impulse;
			impulse.x /= 0.9;
			this->registerGameObject(smallerOne, impulse, 1.0);
			impulse.x *= 1.1;
			impulse.y *= 1.1;
			this->registerGameObject(smallerTwo, impulse, 1.0);
			
		}
	}
}

/// <summary>
/// Constructor
/// </summary>
gameLogic::gameLogic()
{
	//Initialize variables
	this->playerLives = 3;
	this->playerScore = 0;
}

/// <summary>
/// Sets up the start of a level. Happens at game start and after all asteroids have been destroyed.
/// </summary>
void gameLogic::setupLevel() {
	//Initializing the level
	Point asteroidVar1, asteroidVar2, asteroidVar3, asteroidVar4, asteroidVar5;
	asteroidVar1.x = -0.8;
	asteroidVar1.y = -0.8;
	asteroidVar2.x = 0.8;
	asteroidVar2.y = 0.8;
	asteroidVar3.x = -0.8;
	asteroidVar3.y = 0.8;
	asteroidVar4.x = 0.006;
	asteroidVar4.y = 0.006;
	asteroidVar5.x = -0.006;
	asteroidVar5.y = 0.006;


	asteroidClass* asteroid1 = new asteroidClass(0.1);
	asteroidClass* asteroid2 = new asteroidClass(0.09);
	asteroidClass* asteroid3 = new asteroidClass(0.098);
	asteroidClass* asteroid4 = new asteroidClass(0.092);
	asteroidClass* asteroid5 = new asteroidClass(0.11);
	asteroid1->setPosition(asteroidVar1);
	asteroid2->setPosition(asteroidVar2);
	asteroid3->setPosition(asteroidVar3);
	asteroid4->setPosition(asteroidVar1-asteroidVar3);
	asteroid5->setPosition(asteroidVar2);


	this->registerGameObject(asteroid1, asteroidVar4, 1.0);
	this->registerGameObject(asteroid2, asteroidVar4, 1.0);
	this->registerGameObject(asteroid3, asteroidVar5, 1.0);
	this->registerGameObject(asteroid4, asteroidVar4, 1.0);
	this->registerGameObject(asteroid5, asteroidVar5 - asteroidVar4, 1.0);
	/*
	this->pH->registerObject(asteroid1, asteroidVar4, 1.0);
	this->pH->registerObject(asteroid2, asteroidVar4, 1.0);
	this->pH->registerObject(asteroid3, asteroidVar5, 1.0);
	this->pH->registerObject(asteroid4, asteroidVar4, 1.0);
	this->pH->registerObject(asteroid5, asteroidVar5-asteroidVar4, 1.0);
	this->r->registerObject(true, asteroid1);
	this->r->registerObject(true, asteroid2);
	this->r->registerObject(true, asteroid3);
	this->r->registerObject(true, asteroid4);
	this->r->registerObject(true, asteroid5);
	*/
}

/// <summary>
/// Destructor
/// </summary>
gameLogic::~gameLogic()
{
}
