#include "gameController.h"

enum gameState gameController::getGameState(void) {
	return this->state;
}

void gameController::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (action == GLFW_PRESS) {
		switch (key) {
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, GL_TRUE);
		default:
			break;
		}
	}
}

void gameController::setPlayerShip(playerShip *ptr) {
	player = ptr;
}

void gameController::run() { //We could make this the primary gameloop but we dont want to restructure
	this->lastTick = this->GetPerformanceCounter();

	double delta = this->GetPerformanceCounter() - this->lastTick; //If we need to calculate another frame to meet our ticksPS requirement
	if (delta > (this->tickRatePS / 1000)) {
		this->lastTick = this->GetPerformanceCounter();
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
	this->tickRatePS = 21;
}


gameController::~gameController()
{
}
