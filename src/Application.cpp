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
		-1.0f,  1.0f, 0.0f, 1.0f // 3
	};

	unsigned int traingleIndcies[] =
	{
		0, 1 ,2, // first Triagnle 
		2, 3, 0, // second Triangle
	};

	GlCall(glEnable(GL_BLEND));
	GlCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	Renderer g_renderer;

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

	Shader shader("res/shaders/basic.shader");
	shader.Bind();
	shader.SetUniform1i("u_Texture", 0); // binding the texture to the 0 slot of the sampler2D

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


	// --------------------------------------------------
	
	Vector3 v(2.0f,1000.0f,0.0f);
	
	std::cout << v.x << " was x, " << v.y << " was y, " << v.z << std::endl;
	
	

	clock_t currentTick;

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{	

		currentTick =  clock();

		/* Render here */
		g_renderer.Clear();
		

		shader.Bind();
		shader.SetUniformf("u_iTime", currentTick / 1000.0f); // need to abstract his in material class

		g_renderer.Draw(va, ib, shader);

	
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}
	}

	glfwTerminate();
	return 0;
}