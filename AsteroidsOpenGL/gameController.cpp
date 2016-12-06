#include "gameController.h"

void gameController::togglePause() {
	if (this->state == gameRunning) {
		this->state = gamePause;
	}
	else if (this->state == gamePause) {
		this->state = gameRunning;
	}
	
}

void gameController::end() {
	this->state = gameEnd;
}

enum gameState gameController::getGameState(void) {
	return this->state;
}

void gameController::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	gameController* ptr = (gameController*)glfwGetWindowUserPointer(window);
	if (action == GLFW_PRESS) {
		switch (key) {
		case GLFW_KEY_ESCAPE:
			ptr->end();
			glfwSetWindowShouldClose(window, GL_TRUE);
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

void gameController::setPlayerShip(playerShip *ptr) {
	this->player = ptr;
	player->rotate();
}

void gameController::run() { //We could make this the primary gameloop but we dont want to restructure
	this->lastTick = this->GetPerformanceCounter();

	double delta = this->GetPerformanceCounter() - this->lastTick; //If we need to calculate another frame to meet our ticksPS requirement
	if (delta > (this->tickRatePS / 1000)) {
		this->lastTick = this->GetPerformanceCounter();
		if (this->rotateLeft) {
			this->player->turnLeft();
		}
		else if (this->rotateRight) {
			this->player->turnRight();
		}
		this->pH->tick();
	}
}

double gameController::GetPerformanceCounter() {
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	return double(li.QuadPart - CounterStart) / PCFreq;
}

void gameController::StartPerformanceCounter() {
	LARGE_INTEGER li;
	if (!QueryPerformanceFrequency(&li))
		cout << "QueryPerformanceFrequency failed!" << endl;
	PCFreq = double(li.QuadPart) / 1000.0;
	QueryPerformanceCounter(&li);
	CounterStart = li.QuadPart;
}

void gameController::setPhysicsHandler(physicsHandler* ptr) {
	this->pH = ptr;
}

gameController::gameController()
{
	this->state = gameRunning;
	this->StartPerformanceCounter();
	this->tickRatePS = 40;
	rotateRight = false;
	rotateLeft = false;
}


gameController::~gameController()
{
}
