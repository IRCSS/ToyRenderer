#include "ToyRendererApp.h"
#include "log/Log.h"
#include "vendor/GL/glew.h"
#include "vendor/GLFW/glfw3.h"
#include "managers/Settings.h"
#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_impl_glfw_gl3.h"
#include "world/Time.h"
#include "managers/input/InputMaster.h"

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

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4.6);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		GLFWwindow* window;

		/* Create a windowed mode window and its OpenGL context */
		window = glfwCreateWindow(Settings::WindowWidth, Settings::WindowHeigth, "GLFW: Window created", NULL, NULL);

		if (!window)
		{
			glfwTerminate();
			ENGINE_LOG_FATAL("Failed to create a window");
		}

		/* Make the window's context current */
		glfwMakeContextCurrent(window);

		glfwSwapInterval(Settings::VSync ? 1 : 0);

		if (glewInit() != GLEW_OK)
			ENGINE_LOG_FATAL("GLEW has not been initialized correctly ");

		ENGINE_LOG_INFO("Initialized with GL Version       {}", glGetString(GL_VERSION));


		// --------------------------------------------------
		{

			// Initalize UI
			//-------------------------------------------------------------------
			ImGui::CreateContext();
			ImGui_ImplGlfwGL3_Init(window, true);
			ImGui::StyleColorsDark();
			//-------------------------------------------------------------------

			GlCall(glEnable(GL_BLEND));
			GlCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

			ToyRenderer::Time timeHandler = ToyRenderer::Time();


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



				ImGui::Render();
				ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

				/* Swap front and back buffers */
				glfwSwapBuffers(window);
				/* Poll for and process events */
				glfwPollEvents();


			}

		}

		ImGui_ImplGlfwGL3_Shutdown();
		ImGui::DestroyContext();
		glfwTerminate();
	}

}