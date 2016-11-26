#include "main.h"
#include "gameController.h"
#include "renderer.h"



int main()
{
	gameController controller = gameController();
	renderer r = renderer();
	r.initialize("aSTEROIDs", WIDTH, HEIGHT);

	while (controller.getGameState() != gameEnd)
	{
		r.render();
	}
	return 0;
}