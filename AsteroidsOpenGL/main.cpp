#include "main.h"
#include "gameController.h"
#include "renderer.h"
#include "playerShip.h"
#include "physicsHandler.h"


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


	//Gamelogic here propably
	while (controller.getGameState() != gameEnd)
	{
		r.render(); //Renderer can run as often as we like
		controller.run(); //Controller will decide for itself if we need the next frame
	}
	delete ship;
	return 0;
}