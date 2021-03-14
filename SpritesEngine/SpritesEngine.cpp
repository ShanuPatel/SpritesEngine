// SpritesEngine.cpp : Defines the entry point for the application.
//

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

void HandleKeyInput(GLFWwindow* window, int key, int status, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
	else
	{
		std::cout << "" << key << ";status" << status << "; Action" << action << "; Mods" << mods << std::endl;
	}
}

const float Vertics[] =
{
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	0.0f, 0.5f, 0.0f
};

std::string ReadFile(const std::string& fileloc)
{
	std::ifstream file;
	file.open(fileloc, std::ios::in);
	std::stringstream Contents;
	if (!file.fail())
	{
		Contents << file.rdbuf();
	}
	return Contents.str();
}

GLuint CreatAndCompileShaders(const std::string& fileloc, GLuint ShaderType)
{
	const std::string ShaderSource = ReadFile(fileloc);
	const char* cShader = ShaderSource.c_str();

	GLuint shader = glCreateShader(ShaderType);
	glShaderSource(shader, 1, &cShader, nullptr);
	glCompileShader(shader);

	//error checking
	int SuccessStatus;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &SuccessStatus);
	if (!SuccessStatus)
	{
		char InfoLog[512];
		glGetShaderInfoLog(shader, 512, nullptr, InfoLog);
		std::cerr << "ShaderError:" << InfoLog << std::endl;
	}
	return shader;
}

GLuint CreateandLinkProgram()
{
	GLuint vertexShader = CreatAndCompileShaders("../../../shaders/shader.vert", GL_VERTEX_SHADER);
	GLuint fragmentShader = CreatAndCompileShaders("../../../shaders/shader.frag", GL_FRAGMENT_SHADER);
	GLuint program = glCreateProgram();

	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);

	int SuccessStatus;
	glGetShaderiv(program, GL_LINK_STATUS, &SuccessStatus);
	if (!SuccessStatus)
	{
		char InfoLog[512];
		glGetShaderInfoLog(program, 512, nullptr, InfoLog);
		std::cerr << "Programm Error:" << InfoLog << std::endl;
	}
	return 1;
}

int main()
{
	if (!glfwInit())
	{
		std::cerr << "glfw Initialization failed" << std::endl;
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

	GLFWwindow* Window = glfwCreateWindow(1280, 720, "SpritesEngine", nullptr, nullptr);

	if (Window == nullptr)
	{
		std::cerr << "glfw Window Initialization failed" << std::endl;
		glfwTerminate();
		return -2;
	}

	glfwMakeContextCurrent(Window);
	glfwSetKeyCallback(Window, HandleKeyInput);
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		std::cerr << "glfw 2 Initialization failed" << std::endl;
		glfwDestroyWindow(Window);
		glfwTerminate();
		return -3;
	}

	//Shader iniatlization in render loop
	GLuint ShaderProgram = CreateandLinkProgram();

	GLuint VBObj, VAObj;
	glGenVertexArrays(1, &VAObj);
	glGenBuffers(1, &VBObj);
	glBindVertexArray(VAObj);
	glBindBuffer(GL_ARRAY_BUFFER, VBObj);

	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertics), Vertics, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glClearColor(0.5f, 0.3f, 0.4f, 1.0f);

	while (!glfwWindowShouldClose(Window))
	{
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		int width, height;
		glfwGetFramebufferSize(Window, &width, &height);
		glViewport(0, 0, width, height);

		glUseProgram(ShaderProgram);
		glBindVertexArray(VAObj);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(Window);
	}

	glDeleteVertexArrays(1, &VAObj);
	glDeleteBuffers(1, &VBObj);
	glDeleteProgram(ShaderProgram);

	glfwDestroyWindow(Window);
	glfwTerminate();

	//std::cout << "Hello Sprites." << std::endl;
	std::cin.get();
	return 0;
}
