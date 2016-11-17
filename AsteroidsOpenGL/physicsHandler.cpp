#include "physicsHandler.h"

void physicsHandler::tick() {
	return;
}

void physicsHandler::registerObject(gameObject* gO, Point i, float f ) {
	
	physicsObject temp;
	temp.friction = f;
	temp.impulse = i;
	temp.object = gO;
	temp.next = NULL;
	/*
	if (this->first == NULL)
		first = &temp;
	else {
		physicsObject *ptr;
		ptr = this->first;
		while (true) {
			if (ptr->next == NULL)
				break;
			ptr = ptr->next;
		}
		ptr->next = &temp;
	}
	*/
	physicsObject *ptr;
	physicsObject *last;
	ptr = this->first;
	while (ptr != NULL) {
		last = ptr;
		ptr = ptr->next;
	}
}

physicsHandler::physicsHandler()
{
	this->first = NULL;
}


physicsHandler::~physicsHandler()
{
}
