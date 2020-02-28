#include "InputMaster.h"
#include "Settings.h"
#include "InputMapping.h"



namespace ToyRenderer {

	std::unordered_map<int, PressedKey> InputMaster::PressedKeys ;
	std::unordered_map<int, PressedKey> InputMaster::ReleasedKeys;

	static void OnKeyPressed(GLFWwindow* window, int key, int action, int mods)
	{
		if (InputMaster::PressedKeys.find(key)   != InputMaster::PressedKeys.end()) return;
		if (InputMaster::ReleasedKeys.find(key)  != InputMaster::ReleasedKeys.end()) return;


		PressedKey registerKey(window, key);
		InputMaster::PressedKeys[key] = registerKey;

	};

	TOYRENDERER_GLFWMAPPING


	InputMaster::InputMaster(GLFWwindow* window) : p_window(window)
	{
		MapKeys(keyMaping);
		glfwSetKeyCallback(p_window, (GLFWkeyfun)OnKeyPressed);

	}


	InputMaster::~InputMaster()
	{
	}
	void InputMaster::OnUpdate(float deltaTime)
	{
		auto it_pressedKeys = PressedKeys.begin();
		while (it_pressedKeys != PressedKeys.end()) {
			if (it_pressedKeys->second.IsPressed()) {
				it_pressedKeys++;
				continue;
			}

			it_pressedKeys->second.SetUpForRelease();
			ReleasedKeys[it_pressedKeys->first] = it_pressedKeys->second;

			PressedKeys.erase(it_pressedKeys->first);
			it_pressedKeys++;
		}
	}

	bool InputMaster::GetKeyDown(KeyName keycode) const
	{
		
		if (keyMaping.find(keycode) == keyMaping.end()) return false;
		int keyBackEndCode = keyMaping.at(keycode);

		if (PressedKeys.find(keyBackEndCode) == PressedKeys.end()) return false;
		if (PressedKeys.at(keyBackEndCode).actedOnThisFrame) return true;

		return false;
	}

	bool InputMaster::GetKeyUp(KeyName keycode) const
	{

		return false;
	}

	bool InputMaster::GetKey(KeyName keycode) const
	{
		
		if (keyMaping.find(keycode) == keyMaping.end()) return false;
			

		int state = glfwGetKey(p_window, keyMaping.at(keycode));
		if (state == GLFW_PRESS ) return true;

		return false;
	}








	PressedKey::PressedKey()
	{
		window               = nullptr;
		keyCode              = 0;
		actedOnThisFrame     = true;
		numberOfFramesActive = 0;
	}

	PressedKey::PressedKey(const PressedKey & copyFrom)
	{
		window                = copyFrom.window;
		keyCode               = copyFrom.keyCode;
		actedOnThisFrame      = true;
		numberOfFramesActive  = 0;
	}

	PressedKey::PressedKey(GLFWwindow* pWindow, int code) : window(pWindow), keyCode(code)
	{
		actedOnThisFrame     = true;
		numberOfFramesActive = 0;
	}

	bool PressedKey::IsPressed() 
	{
		if (numberOfFramesActive > 0) actedOnThisFrame = false;
		else numberOfFramesActive++;

		int state = glfwGetKey(window, keyCode);
		if (state == GLFW_PRESS) return true;
		return false;
	}

	void PressedKey::SetUpForRelease()
	{
		actedOnThisFrame = true;
		numberOfFramesActive = 0;
	}

	bool PressedKey::IsReleased()
	{
		if (numberOfFramesActive > 0) return false;
		else numberOfFramesActive++;

		return true;
	}



}