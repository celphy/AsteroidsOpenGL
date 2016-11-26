#include "renderer.h"

void renderer::registerObject(bool isInGame, gameObject *obj)
{
	if (isInGame)
		this->add(uiStart, obj);
	else
		this->add(objStart, obj);
}

void renderer::add(renderObject * ptr, gameObject *obj)
{
	renderObject* input = new renderObject();
	input->object = obj;
	input->next = nullptr;

	renderObject *test = ptr;
	renderObject *last;
	while (test != nullptr) {
		last = test;
		test = test->next;
	}
	last->next = input;
	numberOfElements++;
	numberOfPoints += obj->getOutline().getNumber();
}

void renderer::createRenderData()
{
	//Get vertices
}

void renderer::createWindow(string title, int width, int height)
{
	this->window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
	glfwMakeContextCurrent(window);
}

renderer::renderer()
{
	this->numberOfElements = 0;
	this->numberOfPoints = 0;
}


renderer::~renderer()
{
}
