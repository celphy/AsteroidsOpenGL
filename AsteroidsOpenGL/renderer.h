#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include "main.h"
#include "gameObject.h"
//#include "gameController.h"
#include "polygonClass.h"


// Shaders
//extern const GLchar* vertexShaderSource;
//extern const GLchar* fragmentShaderSource;

//We created a seperate List for UI elements
//Either we delta update it (scanning for changed details and updating them)
//Or we simply discard the entire UI list and re-add everything

class renderer
{
private:
	GLFWwindow* window;
	GLuint VBO, VAO, EBO, shaderProgram;
	GLfloat* vertices;
	GLuint* indices;
	vector<gameObject*> gameObjects;
	vector<gameObject*> uiObjects;
	int numberOfElements;
	int numberOfPoints;
	int numberOfLivesLeft;

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
	//void setKeyCallback(gameController* controller);
	void removeObsoleteObjects();
	void registerObject(bool isInGame, gameObject* obj);
	void addGame(gameObject* obj);
	void addUI(gameObject* obj);
	void createRenderData(); //Vertices and Indices
	void render();
	void createWindow(string title, int width, int height);
	GLFWwindow* getWindow();
	void initialize(string windowTitle, int width, int height);
	int getNumberOfLives();
	int getNumberOfPoints();
	void setNumberOfLives(int newLives);
	void setNumberOfPoints(int newPoints);
	renderer();
	~renderer();
};

