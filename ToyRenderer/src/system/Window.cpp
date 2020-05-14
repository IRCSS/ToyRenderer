#include "Window.h"
#include "managers/Settings.h"
#include "log/Log.h"

namespace ToyRenderer {
	
	int Window::Width;
	int Window::Height;

	Window::Window()
	{
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();

		const GLFWvidmode* mode = glfwGetVideoMode(monitor);

		glfwWindowHint(GLFW_RED_BITS,     mode->redBits);
		glfwWindowHint(GLFW_GREEN_BITS,   mode->greenBits);
		glfwWindowHint(GLFW_BLUE_BITS,    mode->blueBits);
		glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

		Width  = mode->width;
		Height = mode->height;


		/* Create a windowed mode window and its OpenGL context */
		p_Window = glfwCreateWindow(mode->width, mode->height, "GLFW: Window created", monitor, NULL);
		if (!p_Window)
		{
			glfwTerminate();
			ENGINE_LOG_FATAL("Failed to create a window");
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, contextVersionMax);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, contextVersionMin);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		SetContextAsCurrent();

	}
	Window::~Window()
	{
	}
	void Window::SetContextAsCurrent()
	{
		/* Make the window's context current */
		glfwMakeContextCurrent(p_Window);
	}
	GLFWwindow* Window::GetWindowAddress()
	{
		return p_Window;
	}
}