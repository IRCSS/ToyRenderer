#include "InputMaster.h"
#include "Settings.h"
#include "InputMapping.h"



namespace ToyRenderer {

	TOYRENDERER_GLFWMAPPING

	InputMaster::InputMaster(GLFWwindow* window) : p_window(window)
	{
		MapKeys(keyMaping);
	}
	InputMaster::~InputMaster()
	{
	}
	void InputMaster::OnUpdate(float deltaTime)
	{

	}

	bool InputMaster::GetKeyDown(KeyName keycode)
	{
		
		if (keyMaping.find(keycode) == keyMaping.end()) return false;
			

		int state = glfwGetKey(p_window, keyMaping[keycode]);
		if (state == GLFW_PRESS) return true;

		return false;
	}






}