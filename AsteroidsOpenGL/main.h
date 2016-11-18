#pragma once

#define GLEW_STATIC
#define projectileLifetime 80

#include <Windows.h>
#include "include/GL/glew.h"
#include "include/GLFW/glfw3.h"
#include <gl/gl.h>
#include <gl/glu.h>
#include <iostream>

#include "point.h"

using namespace std;

const GLuint WIDTH = 800, HEIGHT = 600;

// Shaders
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

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);