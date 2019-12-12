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

struct ParsedShader {
	std::string VertexSource;
	std::string FragmentSource;
};
static ParsedShader ParseShader(const std::string & filePath) {
	std::ifstream stream(filePath);

	enum class ShaderType {
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType currentShaderType = ShaderType::NONE;


	while (getline(stream, line)) {
		
		if (line.find("#shader") != std::string::npos) {
			if (line.find("vertex") != std::string::npos) {
				// found vertex shader
				currentShaderType = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos) {
				// found fragment shader
				currentShaderType = ShaderType::FRAGMENT;
			}
		}
		else {

			ss[(int)currentShaderType] << line << '\n';
		}
	}

	return { ss[0].str(), ss[1].str() };

}

static unsigned int CompileShader(unsigned int type, const std::string& source) {
	unsigned int id  = glCreateShader(type);
	const char*  src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		int length; 
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*) alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);

		std::cout <<  "Failed to compile"   <<
			(type == GL_VERTEX_SHADER ?  "vertex " :  "fragment ") <<   "shader!"  << std::endl;
		std::cout << message << std::endl;

		glDeleteShader(id);
		return 0;
	}

	return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
	GlCall(unsigned int programID = glCreateProgram());
	unsigned int vs = CompileShader(GL_VERTEX_SHADER,   vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	GlCall(glAttachShader(programID, vs));
	GlCall(glAttachShader(programID, fs));

	GlCall(glLinkProgram(programID));
	GlCall(glValidateProgram(programID));

	GlCall(glDeleteShader(vs));
	GlCall(glDeleteShader(fs));

	return programID;
}

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
	float positions[8] = {
		-1.0f, -1.0f, // 0
		 1.0f, -1.0f, // 1
		 1.0f,  1.0f, // 2
		-1.0f,  1.0f, // 3
	};

	unsigned int traingleIndcies[] =
	{
		0, 1 ,2, // first Triagnle 
		2, 3, 0, // second Triangle
	};


	VertexArray  va;
	VertexBuffer vb(positions, 4*2*sizeof(float));

	IndexBuffer  ib(traingleIndcies, 6);

	
	VertexBufferLayout layout;
	layout.Push<float>(2);
	va.AddBuffer(vb, layout);

	GlCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	GlCall(glUseProgram(0));
	GlCall(glBindVertexArray(0));

	ParsedShader vfs = ParseShader("res/shaders/basic.shader");


	unsigned int shader = CreateShader(vfs.VertexSource, vfs.FragmentSource);

	// --------------------------------------------------
	

	int location = glGetUniformLocation(shader, "u_iTime");
	Assert(location != -1);
	

	clock_t currentTick;

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{	

		currentTick =  clock();

		/* Render here */
		GlCall(glClear(GL_COLOR_BUFFER_BIT));
		
		GlCall(glUseProgram(shader));
		GlCall(glUniform1f(location, currentTick / 1000.0f));

		va.Bind();

		ib.Bind();

		GlCall(glDrawElements(GL_TRIANGLES, 3 * 2, GL_UNSIGNED_INT, nullptr));

	
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}
	GlCall(glDeleteProgram(shader));

	}

	glfwTerminate();
	return 0;
}