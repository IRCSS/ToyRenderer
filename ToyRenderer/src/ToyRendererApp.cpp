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
#include "vendor/soloud/soloud.h"
#include "system/File.h"
#include "vendor/soloud/soloud_wav.h"

namespace ToyRenderer {

	

	ToyRendererApp::ToyRendererApp() : window(nullptr), timeHandler(nullptr), inputMaster(nullptr), activeScene(nullptr)
	{
	    // Initalize Loging
        //-------------------------------------------------------------------
		ToyRenderer::Log::Initialize();
		//-------------------------------------------------------------------

		/* Initialize the library */
		if (!glfwInit())
			ENGINE_LOG_FATAL("Failed to initalize the GLFW openGl Context");



		window = new Window();


		glfwSwapInterval(Settings::VSync ? 1 : 0);

		if (glewInit() != GLEW_OK)
			ENGINE_LOG_FATAL("GLEW has not been initialized correctly ");

		ENGINE_LOG_INFO("Initialized with GL Version       {}", glGetString(GL_VERSION));


		// Initalize UI
	    //-------------------------------------------------------------------
		ImGui::CreateContext();
		ImGui_ImplGlfwGL3_Init(window->GetWindowAddress(), true);
		ImGui::StyleColorsDark();
		//-------------------------------------------------------------------

		timeHandler = new Time();


		// INPUT MASTER 
		inputMaster = new InputMaster(window->GetWindowAddress()); // REFACTOR: CHANGE THE GLFW WINDOW TO MY OWN WIDNOW HERE


	}

	ToyRendererApp::~ToyRendererApp()
	{
		delete inputMaster;
		delete timeHandler;
		delete activeScene;
	}

	void ToyRendererApp::Run()
	{
		
		// Sound 
// -------------------------------------------------------
		SoLoud::Soloud gSoloud; // SoLoud engine
		SoLoud::Wav gWave;      // One wave file

		gSoloud.init(); // Initialize SoLoud

		std::string pathToexe = std::string();
		TOYRENDERER_EXEPATH(pathToexe);
		std::string filepath = pathToexe + "\\res\\audio\\service-bell_daniel_simion.wav";
		TOYRENDERER_STYLE_PATH(filepath);

		SoLoud::result results = gWave.load(filepath.c_str()); // Load a wave
		ENGINE_LOG_DEBUG("the loading result is: {}", results);
		gSoloud.play(gWave); // Play the wave



		// --------------------------------------------------
		{


			/* Loop until the user closes the window */
			while (!glfwWindowShouldClose(window->GetWindowAddress()))
			{
				timeHandler->Update();
				// INPUT 
				inputMaster->OnUpdate(ToyRenderer::Time::GetDeltaTime());


				if (activeScene != nullptr) {

				   activeScene->OnUpdate(ToyRenderer::Time::GetDeltaTime());
				   activeScene->OnRender();
				   activeScene->OnGUI();
				}


				// Rendering
				ImGui_ImplGlfwGL3_NewFrame();
				ImGui::Render();
				ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

				/* Swap front and back buffers */
				glfwSwapBuffers(window->GetWindowAddress());
				/* Poll for and process events */
				glfwPollEvents();


			}

		}
		gSoloud.deinit(); // Clean up!
		ImGui_ImplGlfwGL3_Shutdown();
		ImGui::DestroyContext();
		glfwTerminate();
	}

}