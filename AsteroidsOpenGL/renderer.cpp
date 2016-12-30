#include "renderer.h"
#include "main.h"

/// <summary>
/// Returns the number of outline points.
/// </summary>
/// <returns>Number of outline points</returns>
int renderer::getNumberOfPoints() {
	return this->numberOfPoints;
}

/// <summary>
/// Returns the number of lives being displayed.
/// </summary>
/// <returns>Number of lives displayed</returns>
int renderer::getNumberOfLives() {
	return this->numberOfLivesLeft;
}

/// <summary>
/// Sets the current highscore of the player.
/// </summary>
/// <param name="newPoints">Changed highscore</param>
void renderer::setNumberOfPoints(int newPoints) {
	this->numberOfPoints = newPoints;
}

/// <summary>
/// Sets the number of lives being displayed.
/// </summary>
/// <param name="newLives">New number of remaining lives</param>
void renderer::setNumberOfLives(int newLives) {
	this->numberOfLivesLeft = newLives;
}

/// <summary>
/// Registers a gameObject either as ingame or UI.
/// </summary>
/// <param name="isInGame">ingame gameObject?</param>
/// <param name="obj">gameObject</param>
void renderer::registerObject(bool isInGame, gameObject* obj)
{
	if (isInGame)
		this->addGame(obj);
	else
		this->addUI(obj);
}

/// <summary>
/// Registers a gameObject that will be in game.
/// TODO: Find out if split is necessary. Doesn't one suffice?
/// </summary>
/// <param name="obj"></param>
void renderer::addGame(gameObject* obj)
{
	gameObjects.push_back(obj);
	this->numberOfElements++;
	this->numberOfPoints += obj->getOutline().getNumber();
}

/// <summary>
/// Registers a UI gameObject with the renderer.
/// </summary>
/// <param name="obj"></param>
void renderer::addUI(gameObject* obj) {

}


void renderer::removeObsoleteObjects() {
	//Every object that is marked toBeDestroyed needs to get thrown out of our vector
	for (auto it = gameObjects.end() - 1; it != gameObjects.begin(); )//We start at the end to have as little overhead as possible
	{
		if ((*it)->getDestroyed()) {
			it = gameObjects.erase(it);
		}
		--it;

	}

	//gameObjects.resize(distance(begin(gameObjects), remove_if(begin(gameObjects), end(gameObjects), [](const auto& i) { return i->getDestroyed(); })));
}

/// <summary>
/// Creates the data that will be rendered from the registered gameObjects.
/// </summary>
void renderer::createRenderData()
{
	//For every point we need 3 floats in vertices
	//For every line we need 2 ints in indices
	this->vertices = new GLfloat[this->numberOfPoints * 3];
	this->indices = new GLuint[this->numberOfPoints * 2];
	int counterVertices = 0;
	int counterIndices = 0;
	int beginningOfPolygon = 0;

	//GetData
  	for (auto& it : this->gameObjects) { //Iterate over all gameObjects
		beginningOfPolygon = counterIndices;
		for (int i = 0; i < it->getOutline().getNumber(); i++) { //Iterate over all points of the gameObject
			//Add Point
			//this->vertices[counterVertices] = it->getOutline().getPolygonPoint(i).x;
			this->vertices[counterVertices] = it->getRenderPoint(i).x;
			if (DEBUG_OUTPUT)
				cout << "Point " << i << " X: " << this->vertices[counterVertices];
			counterVertices++;
			//this->vertices[counterVertices] = it->getOutline().getPolygonPoint(i).y;
			this->vertices[counterVertices] = it->getRenderPoint(i).y;
			if (DEBUG_OUTPUT)
				cout << " Y: " << this->vertices[counterVertices] << endl;
			counterVertices++;
			this->vertices[counterVertices] = 0.0f;
			counterVertices++;
			//Add Line to draw
			this->indices[counterIndices * 2] = counterIndices;
			this->indices[(counterIndices * 2) + 1] = counterIndices + 1;
			if (DEBUG_OUTPUT)
				cout << "Added line at " << counterIndices * 2 << " and " << counterIndices * 2 + 1 << " to (Point " << counterIndices << " <-> Point " << counterIndices + 1 << ")" << endl;
			counterIndices++;
		}
		this->indices[(counterIndices * 2) - 1] = beginningOfPolygon; //Major possibility for wrong offsets when we're adding more stuff
		if (DEBUG_OUTPUT) {
			cout << "Changed indices[" << counterIndices * 2 - 1 << "] to Point " << beginningOfPolygon << endl;
			cout << "Changed line at " << counterIndices * 2 - 2 << " and " << counterIndices * 2 - 1 << " to (Point " << counterIndices - 1 << " <-> Point " << beginningOfPolygon << ")" << endl;
			cout << "-------------EndOfEntity--------------" << endl;
		}
	}
	if (DEBUG_OUTPUT)
		cout << "###########EndOfCreateRenderData############" << endl;
}

/// <summary>
/// Render function. Draws all the gameObjects.
/// </summary>
void renderer::render()
{
	//Events und Locations 
	glfwPollEvents();
	this->removeObsoleteObjects();
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



	// Render
	// Clear
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(this->shaderProgram);
	glBindVertexArray(VAO);
	//glDrawArrays(GL_TRIANGLES, 0, 6);
	glDrawElements(GL_LINES, this->numberOfPoints * 2, GL_UNSIGNED_INT, 0);
	//glDrawElements(GL_POINTS, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	// Buffer tauschen
	glfwSwapBuffers(this->window);
	delete this->vertices;
	delete this->indices;
}

/// <summary>
/// Creates the window the game will run in.
/// </summary>
/// <param name="title">Window title</param>
/// <param name="width">Window width</param>
/// <param name="height">Window height</param>
void renderer::createWindow(string title, int width, int height)
{
	this->window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
	glfwMakeContextCurrent(this->window);
}

/// <summary>
/// Returns the current window.
/// </summary>
/// <returns>Game window</returns>
GLFWwindow* renderer::getWindow() {
	return this->window;
}
//TODO: Find out if save to include back after gameLogic inclusion.
/* Excluded to prevent cyclic dependencies
void renderer::setKeyCallback(gameController* controller) {
	// Tasten -> key_callback
	glfwSetWindowUserPointer(this->window, (void*)controller);
	glfwSetKeyCallback(this->window, gameController::key_callback);
}*/

/// <summary>
/// Initializes renderer. Sets up GLFW and OpenGL.
/// </summary>
/// <param name="windowTitle">Window title</param>
/// <param name="width">Window width</param>
/// <param name="height">Window height</param>
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

	//Laut tutorial true für wasauchimmer
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

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
}

/// <summary>
/// Constructor that zeroes the number of elements and points being displayed.
/// </summary>
renderer::renderer()
{
	this->numberOfElements = 0;
	this->numberOfPoints = 0;
}

/// <summary>
/// Destructor that clears some OpenGL buffers, terminates GLFW and deletes memory handles.
/// </summary>
renderer::~renderer()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	// GLFW Over and Out
	glfwTerminate();
	/*delete this->vertices;
	delete this->indices;*/
}
