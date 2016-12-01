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
		ship->turnLeft();
		Point newP;
		newP.x = ship->getPosition().x - 0.001;
		newP.y = ship->getPosition().y - 0.001;
		ship->setPosition(newP);
	}
	delete ship;
	return 0;
}