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
/// Reports a collisions between two gameObjects to the gameLogic ?Collisions might be reported twice?
/// </summary>
/// <param name="first">Active Object</param>
/// <param name="second">Passive Object</param>
void gameLogic::reportCollision(physicsObject * first, physicsObject * second)
{
	//currentCollisions.push_back(make_tuple(first, second));
}

/// <summary>
/// Constructor
/// </summary>
gameLogic::gameLogic()
{
}

/// <summary>
/// Destructor
/// </summary>
gameLogic::~gameLogic()
{
}
