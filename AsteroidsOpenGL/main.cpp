#include "main.h"
#include "gameController.h"
#include "renderer.h"


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

int main()
{
	gameController controller = gameController();
	renderer r = renderer();
	r.initialize("aSTEROIDs", WIDTH, HEIGHT);

	while (controller.getGameState() != gameEnd)
	{
		r.render();
	}
	return 0;
}