#include "gameController.h"

void gameController::isDestroyed(gameObject* obj) {
	switch (obj->getType()) {
	case asteroidType:
		break;
	case playerType:
		break;
	default:
		break;
	}
}

void gameController::playerCollision() {
	Point middle;
	middle.x = 0.0;
	middle.y = 0.0;
	this->player->setPosition(middle);
}

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

void gameController::raiseScore(int amount)
{
	this->playerScore += amount;
}

void gameController::setPlayerShip(playerShip *ptr) {
	this->player = ptr;
	player->rotate();
}

void gameController::run() { //We could make this the primary gameloop but we dont want to restructure
	//CODE DOES NOT WORK AS INTENDED BUT WORKS FOR NOW I GUESS
	double delta = this->GetPerformanceCounter() - this->lastTick; //If we need to calculate another frame to meet our ticksPS requirement
	if (delta > (this->tickRatePS / 1000.0)) {
		this->lastTick = this->GetPerformanceCounter();
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
	this->lastTick = this->GetPerformanceCounter();
}

void gameController::setHandlers(void* renderer, physicsHandler* ptr) {
	this->pH = ptr;
	this->logic->reg(renderer, ptr);
}

/*
void gameController::setPhysicsHandler(physicsHandler* ptr) {
	this->pH = ptr;
}
void gameController::setRenderer(renderer * ptr)
{
	this->r = ptr;
}
*/

gameController::gameController()
{
	this->state = gameRunning;
	this->StartPerformanceCounter();
	this->tickRatePS = 40;
	rotateRight = false;
	rotateLeft = false;
	boost = false;
	this->playerScore = 0;
	this->logic = new gameLogic();
}


gameController::~gameController()
{
	delete this->logic;
}
