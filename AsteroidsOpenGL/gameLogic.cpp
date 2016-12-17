#include "gameLogic.h"

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
/// <param name="origin">position</param>
/// <param name="friction">friction in physicsHandler</param>
void gameLogic::registerGameObject(gameObject * obj, Point origin, float friction)
{
	this->r->addGame(obj);
	this->pH->registerObject(obj, origin, friction);
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
			cout << "Player got hit" << endl;
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
}

/// <summary>
/// Destructor
/// </summary>
gameLogic::~gameLogic()
{
}
