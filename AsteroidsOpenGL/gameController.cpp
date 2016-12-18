#include "gameController.h"


/// <summary>
/// Toggles pause-mode.
/// </summary>
void gameController::togglePause() {
	if (this->state == gameRunning) {
		this->state = gamePause;
	}
	else if (this->state == gamePause) {
		this->state = gameRunning;
	}
	
}

/// <summary>
/// Ends the game.
/// </summary>
void gameController::end() {
	this->state = gameEnd;
}

/// <summary>
/// Returns current gamestate.
/// </summary>
enum gameState gameController::getGameState(void) {
	return this->state;
}

/// <summary>
/// Proecesses key callbacks.
/// </summary>
/// <param name="window">Window</param>
/// <param name="key">Key</param>
/// <param name="scancode">Scancode</param>
/// <param name="action">Action</param>
/// <param name="mode">Mode</param>
void gameController::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	gameController* ptr = (gameController*)glfwGetWindowUserPointer(window);
	if (action == GLFW_PRESS) {
		switch (key) {
		case GLFW_KEY_ESCAPE:
			ptr->end();
			glfwSetWindowShouldClose(window, GL_TRUE);
			break;
		case GLFW_KEY_W:
			ptr->boost = true;
			break;
		case GLFW_KEY_A:
			ptr->rotateLeft = true;
			break;
		case GLFW_KEY_D:
			ptr->rotateRight = true;
			break;
		case GLFW_KEY_P:
			ptr->togglePause();
			break;
		default:
			break;
		}
	}
	else if (action == GLFW_RELEASE) {
		switch (key) {
		case GLFW_KEY_W:
			ptr->boost = false;
			break;
		case GLFW_KEY_A:
			ptr->rotateLeft = false;
			break;
		case GLFW_KEY_D:
			ptr->rotateRight = false;
			break;
		default:
			break;
		}
	}
}

/// <summary>
/// Sets the player ship for player input.
/// </summary>
/// <param name="ptr">Pointer to ship instance</param>
void gameController::setPlayerShip(playerShip *ptr) {
	this->player = ptr;
	player->rotate();
}

/// <summary>
/// Timed gameTick. Will run every 1/tickRatePS seconds.
/// </summary>
void gameController::run() { //We could make this the primary gameloop but we dont want to restructure
	//CODE DOES NOT WORK AS INTENDED BUT WORKS FOR NOW I GUESS
	if (firstStart) {
		this->logic->setupLevel();
		firstStart = false;
	}


	if (this->getGameState() == gameRunning) {
			
		LARGE_INTEGER ElapsedMicroseconds, current;
		QueryPerformanceCounter(&current);
		ElapsedMicroseconds.QuadPart = current.QuadPart - this->lastTick.QuadPart;
		ElapsedMicroseconds.QuadPart *= 1000000;
		ElapsedMicroseconds.QuadPart /= Frequency.QuadPart;
		//Now we have microseconds between lastTick and current
		//1 000 000
		if (ElapsedMicroseconds.QuadPart > tickThreshold.QuadPart) {
			QueryPerformanceCounter(&this->lastTick);
			if (this->rotateLeft) {
				this->player->turnLeft();
			}
			else if (this->rotateRight) {
				this->player->turnRight();
			}
			if (this->boost) {
				this->player->playerBoost();
			}
			this->pH->tick();
			this->logic->tick();
		}
	}
}


/// <summary>
/// Starts performance counter.
/// </summary>
void gameController::StartPerformanceCounter() {
	QueryPerformanceFrequency(&this->Frequency);
	QueryPerformanceCounter(&this->lastTick);
	this->tickThreshold.QuadPart = 1;
	this->tickThreshold.QuadPart = 1000000 / TickRatePS;
}

/// <summary>
/// Sets the handles to pyhsics and renderer.
/// TODO: Find out if still necessary after gameLogic inclusion.
/// </summary>
/// <param name="renderer"></param>
/// <param name="ptr"></param>
void gameController::setHandlers(void* renderer, physicsHandler* ptr) {
	this->pH = ptr;
	this->logic->reg(renderer, ptr);
}

/// <summary>
/// Constructor setting state, tickRatePS, movement switches and logic element.
/// Starts the performance counter for gameTick.
/// </summary>
gameController::gameController()
{
	this->state = gameRunning;
	this->StartPerformanceCounter();
	rotateRight = false;
	rotateLeft = false;
	boost = false;
	firstStart = true;
	this->logic = new gameLogic();
}

/// <summary>
/// Destructor
/// </summary>
gameController::~gameController()
{
	delete this->logic;
}
