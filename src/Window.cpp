#include "Window.hpp"
#include <iostream>


	void defaultFrameBufferSizeCallback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	Window::Window(WindowProperties props)
		: properties(props)
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, properties.glMajorVersion);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, properties.glMinorVersion);
		glfwWindowHint(GLFW_DECORATED, !properties.borderless);

		if (properties.glCoreProfile)
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		else
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);


		GLFWmonitor* fs = 0;
		if (properties.fullscreen)
			fs = glfwGetPrimaryMonitor();


		windowRef = glfwCreateWindow(properties.width, properties.height, properties.title, 0, 0);
		if (windowRef == 0)
		{
			std::cerr << "Error creating GLFW window\n";
			return;
		}


		glfwMakeContextCurrent(windowRef);

		glfwSetFramebufferSizeCallback(windowRef, defaultFrameBufferSizeCallback);

		valid = true;
	}

	Window::~Window()
	{
		glfwDestroyWindow(windowRef);
	}

	void Window::swapBuffers()
	{
		glfwSwapBuffers(windowRef);
	}

	void Window::pollEvents()
	{
		glfwPollEvents();
	}


	GLADloadproc Window::getProcAddress()
	{
		return (GLADloadproc)glfwGetProcAddress;
	}

	GLFWwindow* Window::getGLFWWindow()
	{
		return windowRef;
	}

	bool Window::shouldClose()
	{
		if (!_shouldClose)
			_shouldClose = glfwWindowShouldClose(windowRef) == GLFW_TRUE;

		return _shouldClose;
	}

	double Window::getTime()
	{
		return glfwGetTime();
	}

	int Window::getKeyState(int key)
	{
		return glfwGetKey(windowRef,key);
	}

	glm::f64vec2 Window::getCursorPosition()
	{
		glm::f64vec2 position;
		glfwGetCursorPos(windowRef, glm::value_ptr(position), glm::value_ptr(position) + 1);
		return position;
	}

	void Window::setShouldClose(bool newValue)
	{
		_shouldClose = newValue;
	}

	void terminateGLFW()
	{
		glfwTerminate();
	}

	bool initialiseGLFW()
	{
		if (!glfwInit())
		{
			std::cerr << "Error initialising GLFW\n";
			return false;
		}
		return true;
	}