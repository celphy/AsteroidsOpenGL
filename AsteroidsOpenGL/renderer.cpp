#include "renderer.h"
#include "main.h"




void renderer::registerObject(bool isInGame, gameObject* obj)
{
	if (isInGame)
		this->addGame(obj);
	else
		this->addUI(obj);
}

void renderer::addGame(gameObject* obj)
{
	gameObjects.push_back(obj);
	this->numberOfElements++;
	this->numberOfPoints += obj->getOutline().getNumber();
}

void renderer::addUI(gameObject* obj) {

}

void renderer::createRenderData()
{
	//For every point we need 3 floats in vertices
	//For every line we need 2 ints in indices
	this->vertices = new GLfloat[this->numberOfPoints * 3];
	this->vertices = new GLfloat[this->numberOfPoints * 2];
	int counterVertices = 0;
	int counterIndices = 0;
	int beginningOfPolygon = 0;

	for (auto& it : this->gameObjects) { //Iterate over all gameObjects
		beginningOfPolygon = counterIndices;
		for (int i = 0; i < it->getOutline().getNumber(); i++) { //Iterate over all points of the gameObject
			//Add Point
			this->vertices[counterVertices] = it->getOutline().getPolygonPoint(i).x;
			cout << "Point " << i << " X: " << this->vertices[counterVertices];
			counterVertices++;
			this->vertices[counterVertices] = it->getOutline().getPolygonPoint(i).y;
			cout << " Y: " << this->vertices[counterVertices] << endl;
			counterVertices++;
			this->vertices[counterVertices] = 0.0f;
			counterVertices++;
			//Add Line to draw
			this->indices[counterIndices*2] = counterIndices;
			this->indices[(counterIndices * 2) + 1] = counterIndices + 1;
			cout << "Added line at " << counterIndices * 2 << " and " << counterIndices * 2 + 1 << " to (Point " << counterIndices << " <-> Point " << counterIndices + 1 << ")" << endl;
			counterIndices++;
		}
		this->indices[(counterIndices * 2)-1] = beginningOfPolygon; //Major possibility for wrong offsets when we're adding more stuff
		cout << "Changed indices[" << counterIndices * 2 - 1 << "] to Point " << beginningOfPolygon << endl;
		cout << "-------------EndOfCreateRenderData--------------" << endl;
	}

}

void renderer::render()
{
	//Events und Locations 
	glfwPollEvents();
	this->createRenderData();
	//Experimental movement stuff
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->vertices)*this->numberOfPoints * 3, vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(this->indices)*this->numberOfPoints * 2, indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0); //Auf 0 setzen, da bereits gebunden

	glBindVertexArray(0);

	this->vertices[3] += 0.0001f;


	// Render
	// Clear
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(this->shaderProgram);
	glBindVertexArray(VAO);
	//glDrawArrays(GL_TRIANGLES, 0, 6);
	glDrawElements(GL_LINES, 6, GL_UNSIGNED_INT, 0);
	//glDrawElements(GL_POINTS, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	// Buffer tauschen
	glfwSwapBuffers(this->window);
}

void renderer::createWindow(string title, int width, int height)
{
	this->window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
	glfwMakeContextCurrent(this->window);
}

void renderer::initialize(string windowTitle, int width, int height)
{
	// GLFW
	glfwInit();
	// Extensions
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	this->createWindow(windowTitle, width, height);
	// Tasten -> key_callback
	glfwSetKeyCallback(this->window, gameController::key_callback);

	//Laut tutorial true f�r wasauchimmer
	glewExperimental = GL_TRUE;
	glewInit();

	//OpenGL viewport...
	int glwidth, glheight;
	glfwGetFramebufferSize(window, &glwidth, &glheight);
	glViewport(0, 0, glwidth, glheight);

	/////////////
	// Shader
	////////////
	// Vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &this->vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	//Erfolg? 
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// Fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &this->fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	// Erfolg?
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// Link shaders
	this->shaderProgram = glCreateProgram();
	glAttachShader(this->shaderProgram, vertexShader);
	glAttachShader(this->shaderProgram, fragmentShader);
	glLinkProgram(this->shaderProgram);
	// Erfolg?
	glGetProgramiv(this->shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(this->shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	this->vertices = new GLfloat[9];
	this->vertices[0] = 0.0f;
	this->vertices[1] = 0.2f;
	this->vertices[2] = 0.0f;
	this->vertices[3] = 0.1f;
	this->vertices[4] = -0.1f;
	this->vertices[5] = 0.0f;
	this->vertices[6] = -0.1f;
	this->vertices[7] = -0.1f;
	this->vertices[8] = 0.0f;



	this->indices = new GLuint[6];
	this->indices[0] = 0;
	this->indices[1] = 1;
	this->indices[2] = 1;
	this->indices[3] = 2;
	this->indices[4] = 2;
	this->indices[5] = 0;

	this->numberOfElements = 1;
	this->numberOfPoints = 3;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
}

renderer::renderer()
{
	this->numberOfElements = 0;
	this->numberOfPoints = 0;
}


renderer::~renderer()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	// GLFW Over and Out
	glfwTerminate();
	delete this->vertices;
	delete this->indices;
}
