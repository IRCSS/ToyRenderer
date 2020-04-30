#include "ToyRendererApp.h"
#include "log/Log.h"
#include "vendor/GL/glew.h"
#include "vendor/GLFW/glfw3.h"
#include "managers/Settings.h"
#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_impl_glfw_gl3.h"
#include "world/Time.h"
#include "managers/input/InputMaster.h"
#include "system/Window.h"

// Remove Later
#include "rendering/Renderer.h"

namespace ToyRenderer {

	

	ToyRendererApp::ToyRendererApp()
	{
	    // Initalize Loging
        //-------------------------------------------------------------------
		ToyRenderer::Log::Initialize();
		//-------------------------------------------------------------------
	}

	ToyRendererApp::~ToyRendererApp()
	{
	}

	void ToyRendererApp::Run()
	{
		
		/* Initialize the library */
		if (!glfwInit())
			ENGINE_LOG_FATAL("Failed to initalize the GLFW openGl Context");



		Window window = Window();


		glfwSwapInterval(Settings::VSync ? 1 : 0);

		if (glewInit() != GLEW_OK)
			ENGINE_LOG_FATAL("GLEW has not been initialized correctly ");

		ENGINE_LOG_INFO("Initialized with GL Version       {}", glGetString(GL_VERSION));


		// --------------------------------------------------
		{

			// Initalize UI
			//-------------------------------------------------------------------
			ImGui::CreateContext();
			ImGui_ImplGlfwGL3_Init(window.GetWindowAddress(), true);
			ImGui::StyleColorsDark();
			//-------------------------------------------------------------------

			ToyRenderer::Time timeHandler = ToyRenderer::Time();


			// INPUT MASTER 
			ToyRenderer::InputMaster inputMaster(window.GetWindowAddress()); // REFACTOR: CHANGE THE GLFW WINDOW TO MY OWN WIDNOW HERE


			/* Loop until the user closes the window */
			while (!glfwWindowShouldClose(window.GetWindowAddress()))
			{
				timeHandler.Update();
				// INPUT 
				inputMaster.OnUpdate(ToyRenderer::Time::GetDeltaTime());

				// Rendering

				ImGui_ImplGlfwGL3_NewFrame();



				ImGui::Render();
				ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

				/* Swap front and back buffers */
				glfwSwapBuffers(window.GetWindowAddress());
				/* Poll for and process events */
				glfwPollEvents();


			}

		}

		ImGui_ImplGlfwGL3_Shutdown();
		ImGui::DestroyContext();
		glfwTerminate();
	}

}