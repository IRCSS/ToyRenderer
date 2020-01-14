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

		// Vertex layout, vec2 positions (2 floats), vec2 uv (2 floats), maybe move this to a struct of a sort later

	float positions[] = {
		-1.0f, -1.0f, 0.0f, 0.0f, // 0
		 1.0f, -1.0f, 1.0f, 0.0f, // 1
		 1.0f,  1.0f, 1.0f, 1.0f, // 2
		-1.0f,  1.0f, 0.0f, 1.0f  // 3
	};

	unsigned int traingleIndcies[] =
	{
		0, 1 ,2, // first Triagnle 
		2, 3, 0, // second Triangle
	};

	GlCall(glEnable(GL_BLEND));
	GlCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	Renderer g_renderer;


	ImGui::CreateContext();
	ImGui_ImplGlfwGL3_Init(window, true);
	ImGui::StyleColorsDark();


	// Need to abstract this later to an obejct of a sort. The shader stuff and uniforms need 
	// to go to a matrial and the vertex array and vertexbuffer need to be constructed from a 
	// mesh and a meshRenderer class of a sort

	VertexArray  va;
	VertexBuffer vb(positions, 4*4*sizeof(float));

	IndexBuffer  ib(traingleIndcies, 6);
	

	// to do: add semantics to layout for ease of API use later
	VertexBufferLayout layout;
	layout.Push<float>(2); // position
	layout.Push<float>(2); // uv
	va.AddBuffer(vb, layout);

	glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);

	glm::mat4 view  = glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 mvp = proj * view * model;

	Shader shader("res/shaders/basic.shader");
	shader.Bind();
	shader.SetUniform1i("u_Texture", 0); // binding the texture to the 0 slot of the sampler2D
	shader.SetUniformMat4("u_MVP", mvp);

	Texture texture("res/textures/checkerFormat.png");
	texture.Bind();

	va.UnBind();
	vb.UnBind();
	ib.UnBind();
	shader.UnBind();

	GlCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	GlCall(glUseProgram(0));
	GlCall(glBindVertexArray(0));

	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	// --------------------------------------------------


	clock_t currentTick;

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{	

		currentTick =  clock();

		/* Render here */
		g_renderer.Clear();
		
		ImGui_ImplGlfwGL3_NewFrame();

		shader.Bind();
		shader.SetUniformf("u_iTime", currentTick / 1000.0f); // need to abstract his in material class

		g_renderer.Draw(va, ib, shader);

	

		{
			static float f = 0.0f;
			static int counter = 0;
			ImGui::Text("Hello, world!");                           // Display some text (you can use a format string too)
			ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f    
			ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

			ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our windows open/close state
			ImGui::Checkbox("Another Window", &show_another_window);

			if (ImGui::Button("Button"))                            // Buttons return true when clicked (NB: most widgets return true when edited/activated)
				counter++;
			ImGui::SameLine();
			ImGui::Text("counter = %d", counter);

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		}

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
	return 0;
}