#include "main.h"
#include "gameController.h"
#include "renderer.h"
#include "playerShip.h"
#include "physicsHandler.h"
#include "asteroidClass.h"

/// <summary>
/// Main method that sets up some stuff and runs the core loop
/// </summary>
/// <returns>Exit code</returns>
int main()
{
	gameController controller = gameController();
	renderer r = renderer();

	r.initialize("aSTEROIDs", WIDTH, HEIGHT);
	//r.setKeyCallback(&controller);
	
	//Removed from renderer itself to avoid cyclic dependencies
	glfwSetWindowUserPointer(r.getWindow(), &controller);
	glfwSetKeyCallback(r.getWindow(), gameController::key_callback);

	playerShip* ship = new playerShip();
	physicsHandler* physics = new physicsHandler();

	Point shipMovement;
	shipMovement.x = -0.000;
	shipMovement.y = -0.000;

	ship->setSelf(physics->registerObject(ship, shipMovement, 0.97));
	controller.setPlayerShip(ship);
	r.registerObject(true, ship);

	controller.setHandlers(static_cast<void*>(&r), physics);

	//Gamelogic here propably
	while (controller.getGameState() != gameEnd)
	{
		r.render(); //Renderer can run as often as we like
		controller.run(); //Controller will decide if we need to calculate the next frame
	}
	delete ship;
	return 0;
}