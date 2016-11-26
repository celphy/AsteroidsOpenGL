#pragma once
#include "main.h"
#include <string>
//We will make a list with all objects, not just gameObjects because we need to render text as well
class renderer
{
private:
	GLfloat* vertices;
	GLuint* indices;
public:
	void registerObject();
	void createVertices();
	void createIndices();
	void render();
	void createWindow(string title, int width, int height);
	void initialize();
	renderer();
	~renderer();
};

