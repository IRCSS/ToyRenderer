#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include "Settings.h"
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include "maths/Vector3.h"
#include "maths/Matrix4x4.h"
#include "maths/Vector4.h"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

#include "Tests/TestClearColor.h"
#include "Tests/TestTexture2D.h"
#include "Tests/TestObjLoader.h"

#include "InputMaster.h"


int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;


	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(Settings::WindowWidth, Settings::WindowHeigth,  "GLFW: Window created" , NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSwapInterval(Settings::VSync ? 1: 0);

	if (glewInit() != GLEW_OK)
		std::cout <<  "GLEW has not been initialized correctly " << std::endl;

	std::cout << glGetString(GL_VERSION) << std::endl;



	// --------------------------------------------------
	{

	

	GlCall(glEnable(GL_BLEND));
	GlCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	Renderer g_renderer;

	ImGui::CreateContext();
	ImGui_ImplGlfwGL3_Init(window, true);
	ImGui::StyleColorsDark();




	GlCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	GlCall(glUseProgram(0));
	GlCall(glBindVertexArray(0));



	// --------------------------------------------------

	test::Test* currenTest = nullptr;
	test::TestMenu* menu  = new test::TestMenu(currenTest);
	currenTest = menu;

	clock_t currentTick;

	menu->RegisterTest<test::TestClearColor>("Clear Color");
	menu->RegisterTest<test::TestTexture2D>("Texture 2D");
	menu->RegisterTest<test::TesstObjLoader>("obj load");
	

	// INPUT MASTER 
	ToyRenderer::InputMaster inputMaster;

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{	
		currentTick =  clock();
		
		// INPUT 
		inputMaster.OnUpdate(currentTick);
		
		bool clicked = inputMaster.GetKeyDown(ToyRenderer::Key::LeftMouseButton);

		if (clicked) std::cout << "clicked Left Button" << std::endl;

		clicked = inputMaster.GetKeyDown(ToyRenderer::Key::A);

		if (clicked) std::cout << "pressed A" << std::endl;



		// Rendering
		g_renderer.Clear();
		
		ImGui_ImplGlfwGL3_NewFrame();
		if (currenTest) {
			currenTest->OnUpdate(currentTick);
			currenTest->OnRender();

			ImGui::Begin("Test");
			if (currenTest != menu && ImGui::Button("<-")) {

				delete currenTest;
				currenTest = menu;



			}
			currenTest->OnImGuiRender();

			ImGui::End();
		}

		

		ImGui::Render();
		ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

		/* Swap front and back buffers */
		glfwSwapBuffers(window);
		/* Poll for and process events */
		glfwPollEvents();
	}

	if (currenTest != menu) delete menu;
	delete currenTest;

	}

	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
	return 0;
}