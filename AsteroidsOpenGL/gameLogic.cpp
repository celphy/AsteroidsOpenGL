#include "gameLogic.h"

/// <summary>
/// Gets called when the player tries to shoot.
/// </summary>
/// <param name="player">Pointer to player object</param>
void gameLogic::playerShoot(playerShip* player) {
	if (this->shotCooldown != 0) {
		return;
	}
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

	this->shotCooldown = playerShotCooldown;
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
physicsObject* gameLogic::registerGameObject(gameObject * obj, Point impulse, float friction)
{
	//this->r->addGame(obj);
	this->r->registerObject(true, obj);
	return this->pH->registerObject(obj, impulse, friction);
}

/// <summary>
/// Changes the impulse of the saucer physicsObject causing it to turn.
/// </summary>
void gameLogic::saucerTurn() {
	if (!this->saucerActive) //If the saucer is inactive it has been destroyed and can't be accessed!!
		return;
	float interchange;
	interchange = this->activeSaucer->impulse.x;
	this->activeSaucer->impulse.x = this->activeSaucer->impulse.y;
	this->activeSaucer->impulse.y = interchange;
}

/// <summary>
/// Orders the saucer to shoot at a gameObject and handles it.
/// </summary>
/// <param name="target">Target gameObject</param>
void gameLogic::saucerShoot(gameObject * target)
{
	//Set up a projectile from the front facing in the same direction the playerShip is.	
	projectileClass* projectile = new projectileClass();
	Point from, to;
	from = this->activeSaucer->object->getPosition();
	to = target->getPosition();

	vectorClass vector = vectorClass(from, to);
	vector.normVector();

	from.x += (vector.getDirection().x - vector.getOrigin().x) / 6;
	from.y += (vector.getDirection().y - vector.getOrigin().y) / 6;

	projectile->setPosition(from);

	GLfloat* points = new GLfloat[4];
	points[0] = 0.0f;
	points[1] = 0.0f;
	points[2] = 0.01f;
	points[3] = 0.01f;
	projectile->setOutline(2, points);

	Point impulse;
	impulse.x = vector.getDirection().x - vector.getOrigin().x;
	impulse.y = vector.getDirection().y - vector.getOrigin().y;
	impulse.x *= 0.05;
	impulse.y *= 0.05;

	this->registerGameObject(projectile, impulse, 1.0);
}

/// <summary>
/// Resolve the reported collisions, update the gameState accordingly
/// </summary>
void gameLogic::tick()
{
	//resolve collisions, update gamestate
	vector<collisionStruct> lastCollisions = this->pH->getLastCollisions();
	int playerHitCount = 0; //Count number of hits against player per tick. If its zero we can reset playerHit after collisions TODO
	if (this->shotCooldown > 0) {
		this->shotCooldown--;
	}
	if (this->saucerTurnCounter == 0 && this->saucerActive == false) {
		Point saucerImpulse, saucerPos;
		saucerPos.x = -0.9;
		saucerPos.y = -0.3;
		saucerImpulse.x = 0.001;
		saucerImpulse.y = 0.007;
		this->addSaucer(saucerImpulse, saucerPos);
		this->saucerActive = true;
		saucerTurnCounter = timeBetweenSaucerTurns;
	}
	else if (this->saucerTurnCounter == 0) {
		this->saucerTurn();
		this->saucerTurnCounter = timeBetweenSaucerTurns;
		if (saucerActive)
			saucerShoot(this->player);
	}
	if (this->saucerTurnCounter > 0) {
		this->saucerTurnCounter--;
	}
	for (auto& it : lastCollisions) {
		if (it.passive->object->getType() == playerType && it.active->object->getType() == projectileType) {
			if (DEBUG_OUTPUT) {
				cout << "Player got hit by projectile" << endl;
			}
			//Projectile currently spawns inside of player
			//this->playerLives--;
			//this->centerPlayer(it.passive->object);
			//playerHit++;
		}
		if (it.passive->object->getType() == playerType && it.active->object->getType() == asteroidType && !playerHit) { //Player got hit
			if (DEBUG_OUTPUT) {
				cout << "Player got hit" << endl;
			}
			playerHit = true;
			this->playerLives--;
			centerPlayer(it.passive->object);
			playerHitCount++;
			generateUI();
		}
		if (it.passive->object->getType() == playerType && it.active->object->getType() == saucerType && !playerHit) {
			if (DEBUG_OUTPUT) {
				cout << "Player hit by saucer" << endl;
			}
			playerHit = true;
			this->playerLives--;
			centerPlayer(it.passive->object);
			playerHitCount++;
			generateUI();
		}
		if (it.passive->object->getType() == asteroidType && it.active->object->getType() == projectileType) {
			if (DEBUG_OUTPUT)
				cout << "Asteroid got hit by projectile!" << endl;
			it.passive->object->markToDestroy();
			this->asteroidCount--;
			it.active->object->markToDestroy();
			this->playerScore += asteroidScore;
			asteroidClass* smallerOne, *smallerTwo;
			asteroidClass* old = static_cast<asteroidClass*>(it.passive->object);
			float newSize = old->getSize() / 2;
			if (newSize > 0.02) {
				Point impulse;
				impulse = it.passive->impulse;
				impulse.x /= 0.9;
				impulse.y /= 0.9;
				this->addAsteroid(newSize, impulse, it.passive->object->getPosition());
				impulse.x *= 1.1;
				impulse.y *= 1.1;
				this->addAsteroid(newSize, impulse, it.passive->object->getPosition());

			}
			if (asteroidCount == 0) {
				this->setupLevel();
			}
			generateUI();
		}
		if (it.passive->object->getType() == saucerType && it.active->object->getType() == projectileType) {
			if (DEBUG_OUTPUT)
				cout << "Saucer hit by projectile" << endl;
			this->playerScore += saucerScore;
			it.passive->object->markToDestroy();
			it.active->object->markToDestroy();
			this->saucerActive = false;
			this->saucerTurnCounter = 2000;
			generateUI();
		}
	}
	if (playerHitCount == 0) {
		playerHit = false;
	}

}

/// <summary>
/// Resets the player position to the centre location.
/// </summary>
/// <param name="player">Player gameObject</param>
void gameLogic::centerPlayer(gameObject* player) {
	Point center;
	center.x = 0.0;
	center.y = 0.0;
	player->setPosition(center);
}

/// <summary>
/// Constructor
/// </summary>
gameLogic::gameLogic()
{
	//Initialize variables
	this->playerLives = 3;
	this->playerScore = 0;
	this->asteroidCount = 0;
	this->shotCooldown = 0;
	this->saucerTurnCounter = 0;
	this->saucerActive = false;
	this->playerHit = false;
}

/// <summary>
/// Sets up the start of a level. Happens at game start and after all asteroids have been destroyed.
/// </summary>
void gameLogic::setupLevel() {
	Point asteroidVar1, asteroidVar2, asteroidVar3, asteroidVar4, asteroidVar5, saucerImpulse;
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
	saucerImpulse.x = 0.001;
	saucerImpulse.y = 0.007;


	this->addAsteroid(0.11, asteroidVar4, asteroidVar1);
	this->addAsteroid(0.09, asteroidVar4, asteroidVar2);
	this->addAsteroid(0.098, asteroidVar5, asteroidVar3);
	this->addAsteroid(0.092, asteroidVar4, asteroidVar1 - asteroidVar3);
	this->addAsteroid(0.11, asteroidVar5 - asteroidVar4, asteroidVar2);

	this->saucerTurnCounter = 2000;

	generateUI();
}

/// <summary>
/// Adds a saucer at position with impulse to the game.
/// </summary>
/// <param name="impulse"></param>
/// <param name="position"></param>
void gameLogic::addSaucer(Point impulse, Point position) {
	saucerClass* newSaucer = new saucerClass();
	newSaucer->setPosition(position);
	this->activeSaucer = this->registerGameObject(newSaucer, impulse, 1.0);
}

void gameLogic::setPlayer(playerShip * ptr)
{
	player = ptr;
}

void gameLogic::generateUI()
{
	r->clearUI();
	//Our variables to display
	this->playerScore;
	this->playerLives;
	//Our fontbuilder can be accessed like this
	//r->addUI(fontBuilder::getInstance().makeToText(1, PointOfOrigin, 0.5));

	//We'll display four numbers and up to three lives
	int firstNumber = this->playerScore % 10;
	int secondNumber = this->playerScore / 10 % 10;
	int thirdNumber = this->playerScore / 100 % 10;
	int fourthNumber = this->playerScore / 1000 % 10;

	Point pOO;
	pOO.x = -0.5;
	pOO.y = 0.9;
	for (int i = 0; i < this->playerLives; i++) {
		r->addUI(fontBuilder::getInstance().makeToText(-1, pOO, 0.1));
		pOO.x += 0.1;
	}

	pOO.x = 0.8;

	if (fourthNumber != 0) {
		//print all
		r->addUI(fontBuilder::getInstance().makeToText(fourthNumber, pOO, 0.1));
		pOO.x += 0.1;
		r->addUI(fontBuilder::getInstance().makeToText(thirdNumber, pOO, 0.1));
		pOO.x += 0.1;
		r->addUI(fontBuilder::getInstance().makeToText(secondNumber, pOO, 0.1));
		pOO.x += 0.1;
		r->addUI(fontBuilder::getInstance().makeToText(firstNumber, pOO, 0.1));
	}
	//print others
	else if (thirdNumber != 0) {
		r->addUI(fontBuilder::getInstance().makeToText(thirdNumber, pOO, 0.1));
		pOO.x += 0.1;
		r->addUI(fontBuilder::getInstance().makeToText(secondNumber, pOO, 0.1));
		pOO.x += 0.1;
		r->addUI(fontBuilder::getInstance().makeToText(firstNumber, pOO, 0.1));
	}
	else if (secondNumber != 0) {
		r->addUI(fontBuilder::getInstance().makeToText(secondNumber, pOO, 0.1));
		pOO.x += 0.1;
		r->addUI(fontBuilder::getInstance().makeToText(firstNumber, pOO, 0.1));
	}
	else
		r->addUI(fontBuilder::getInstance().makeToText(firstNumber, pOO, 0.1));

}

/// <summary>
/// Adds an asteroid to the game.
/// </summary>
/// <param name="s">Relative size</param>
/// <param name="impulse">Initial impulse</param>
/// <param name="position">Starting point</param>
void gameLogic::addAsteroid(float s, Point impulse, Point position) {
	this->asteroidCount++;
	asteroidClass* newAsteroid = new asteroidClass(s);
	newAsteroid->setPosition(position);
	this->registerGameObject(newAsteroid, impulse, 1.0);
}

/// <summary>
/// Destructor
/// </summary>
gameLogic::~gameLogic()
{
}


