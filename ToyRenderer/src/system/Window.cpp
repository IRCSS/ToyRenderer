#include "Window.h"
#include "managers/Settings.h"
#include "log/Log.h"

namespace ToyRenderer {
	
	Window::Window()
	{
		/* Create a windowed mode window and its OpenGL context */
		p_Window = glfwCreateWindow(Settings::WindowWidth, Settings::WindowHeigth, "GLFW: Window created", NULL, NULL);
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