#include "main.h"
#include "gameController.h"
#include "renderer.h"
#include "playerShip.h"


int main()
{
	gameController controller = gameController();
	renderer r = renderer();

	r.initialize("aSTEROIDs", WIDTH, HEIGHT);

	playerShip* ship = new playerShip();

	controller.setPlayerShip(ship);
	r.registerObject(true, ship);

	while (controller.getGameState() != gameEnd)
	{
		r.render();
	}
	delete ship;
	return 0;
}