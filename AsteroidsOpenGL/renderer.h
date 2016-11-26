#pragma once
#include <string>
#include "main.h"
#include "gameObject.h"
#include "gameController.h"


//We will make a list with all objects, not just physicsObjects because we need to render text as well
typedef struct renderObject {
	gameObject *object;//reference to gameObject
	renderObject *next;
}renderObject;

//Should we make seperate lists for UI, gameObjects

class renderer
{
private:
	GLFWwindow* window;
	GLuint VBO, VAO, EBO, shaderProgram;
	GLfloat* vertices;
	GLuint* indices;
	renderObject *uiStart;
	renderObject *objStart;
	int numberOfElements;
	int numberOfPoints;
public:
	void registerObject(bool isInGame, gameObject *obj);
	void add(renderObject *ptr, gameObject *obj);
	void createRenderData(); //Vertices and Indices
	void render();
	void createWindow(string title, int width, int height);
	void initialize(string windowTitle, int width, int height);
	renderer();
	~renderer();
};

