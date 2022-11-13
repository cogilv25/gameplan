#pragma once
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


typedef void* (*GLADloadproc)(const char* name);

struct WindowProperties
{
	int glMajorVersion = 4;
	int glMinorVersion = 6;
	bool glCoreProfile = true;
	const char* title = "Hello World";
	int width = 1920;
	int height = 1080;
	bool fullscreen = false;
	bool borderless = false;
};

class Window
{
protected:
	bool _shouldClose = false;
	WindowProperties properties;
	GLFWwindow* windowRef;
public:
	bool valid = false;
public:
	Window(WindowProperties = WindowProperties());
	~Window();
	void swapBuffers();
	void pollEvents();
	GLADloadproc getProcAddress();
	bool shouldClose();
	void setShouldClose(bool newValue);
	double getTime();
	int getKeyState(int key);
	GLFWwindow* getGLFWWindow();
	glm::f64vec2 getCursorPosition();
	const WindowProperties& peekProperties() { return properties; };
};

void terminateGLFW();
bool initialiseGLFW();