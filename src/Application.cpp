#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

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
	unsigned int programID = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER,   vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(programID, vs);
	glAttachShader(programID, fs);

	glLinkProgram(programID);
	glValidateProgram(programID);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return programID;
}

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;




	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480,  "GLFW: Window created" , NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
		std::cout <<  "GLEW has not been initialized correctly " << std::endl;

	std::cout << glGetString(GL_VERSION) << std::endl;

	
	// --------------------------------------------------

	float positions[8] = {
		-0.5f, -0.5f, // 0
		 0.5f, -0.5f, // 1
		 0.5f,  0.5f, // 2
		-0.5f,  0.5f, // 3
	};

	unsigned int traingleIndcies[] =
	{
		0, 1 ,2, // first Triagnle 
		2, 3, 0, // second Triangle
	};


	unsigned int tBufferID; 
	glGenBuffers(1, &tBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, tBufferID);
	glBufferData(GL_ARRAY_BUFFER, 4* 2 * sizeof(float), positions, GL_STATIC_DRAW);

	unsigned int indexBufferID;
	glGenBuffers(1, &indexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 2* 3 * sizeof(unsigned int), traingleIndcies, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);


	ParsedShader vfs = ParseShader("res/shaders/basic.shader");


	unsigned int shader = CreateShader(vfs.VertexSource, vfs.FragmentSource);
	glUseProgram(shader);
	// --------------------------------------------------
	
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{	
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawElements(GL_TRIANGLES, 3 * 2, GL_UNSIGNED_INT, nullptr);

	
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}
	glDeleteProgram(shader);
	glfwTerminate();
	return 0;
}