#include "main.h"
#include "gameController.h"
#include "renderer.h"
#include "playerShip.h"
#include "physicsHandler.h"
#include "asteroidClass.h"


int main()
{
	gameController controller = gameController();
	renderer r = renderer();

	r.initialize("aSTEROIDs", WIDTH, HEIGHT);

	playerShip* ship = new playerShip();
	physicsHandler* physics = new physicsHandler();
	Point shipMovement;
	shipMovement.x = -0.001;
	shipMovement.y = -0.001;

	physics->registerObject(ship, shipMovement, 0.999);

	controller.setPlayerShip(ship);
	controller.setPhysicsHandler(physics);
	r.registerObject(true, ship);

	Point asteroidMovement;
	asteroidMovement.x = -0.005;
	asteroidMovement.y = +0.005;
	asteroidClass* asteroid1 = new asteroidClass(0.1);
	asteroidClass* asteroid2 = new asteroidClass(0.2);
	asteroid1->setPosition(asteroidMovement);
	asteroid2->setPosition(asteroidMovement);
	r.registerObject(true, asteroid1);
	r.registerObject(true, asteroid2);
	physics->registerObject(asteroid1, asteroidMovement, 1);
	physics->registerObject(asteroid2, asteroidMovement, 1);


	//Gamelogic here propably
	while (controller.getGameState() != gameEnd)
	{
		r.render(); //Renderer can run as often as we like
		controller.run(); //Controller will decide for itself if we need the next frame
	}
	delete ship;
	return 0;
}