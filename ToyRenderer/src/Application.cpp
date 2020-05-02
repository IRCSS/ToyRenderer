#include "vendor/GL/glew.h"
#include "vendor/GLFW/glfw3.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include "managers/Settings.h"
#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_impl_glfw_gl3.h"

#include "Tests/TestClearColor.h"
#include "Tests/TestTexture2D.h"
#include "Tests/TestObjLoader.h"

#include "managers/input/InputMaster.h"
#include "log/Log.h"
#include "world/Time.h"

namespace ToyRenderer {
	 
	int main(void)
	{
		// Initalize Loging
		//-------------------------------------------------------------------
		ToyRenderer::Log::Initialize();


		//-------------------------------------------------------------------
		GLFWwindow* window;

		/* Initialize the library */
		if (!glfwInit())
			return -1;


		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4.6);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		/* Create a windowed mode window and its OpenGL context */
		window = glfwCreateWindow(Settings::WindowWidth, Settings::WindowHeigth, "GLFW: Window created", NULL, NULL);
		if (!window)
		{
			glfwTerminate();
			return -1;
		}

		/* Make the window's context current */
		glfwMakeContextCurrent(window);

		glfwSwapInterval(Settings::VSync ? 1 : 0);

		if (glewInit() != GLEW_OK)
			ENGINE_LOG_FATAL("GLEW has not been initialized correctly ");

		ENGINE_LOG_INFO("Initialized with GL Version       {}", glGetString(GL_VERSION));



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
			test::TestMenu* menu = new test::TestMenu(currenTest);
			currenTest = menu;

			ToyRenderer::Time timeHandler = ToyRenderer::Time();

			menu->RegisterTest<test::TestClearColor>("Clear Color");
			menu->RegisterTest<test::TesstObjLoader>("obj load");


			// INPUT MASTER 
			ToyRenderer::InputMaster inputMaster(window);

			/* Loop until the user closes the window */
			while (!glfwWindowShouldClose(window))
			{

				timeHandler.Update();
				// INPUT 
				inputMaster.OnUpdate(ToyRenderer::Time::GetDeltaTime());



				// Rendering

				ImGui_ImplGlfwGL3_NewFrame();
				if (currenTest) {
					currenTest->OnUpdate(ToyRenderer::Time::GetDeltaTime());
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
}