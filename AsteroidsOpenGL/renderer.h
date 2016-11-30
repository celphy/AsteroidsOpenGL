#pragma once
#include <string>
#include <vector>
#include "main.h"
#include "gameObject.h"
#include "gameController.h"
#include "polygonClass.h"

// Shaders
//extern const GLchar* vertexShaderSource;
//extern const GLchar* fragmentShaderSource;

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
	vector<gameObject*> gameObjects;
	int numberOfElements;
	int numberOfPoints;

	const GLchar* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 position;\n"
		"void main()\n"
		"{\n"
		"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
		"}\0";
	const GLchar* fragmentShaderSource = "#version 330 core\n"
		"out vec4 color;\n"
		"void main()\n"
		"{\n"
		"color = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
		"}\n\0";

public:
	void registerObject(bool isInGame, gameObject* obj);
	void addGame(gameObject* obj);
	void addUI(gameObject* obj);
	void createRenderData(); //Vertices and Indices
	void render();
	void createWindow(string title, int width, int height);
	void initialize(string windowTitle, int width, int height);
	renderer();
	~renderer();
};

