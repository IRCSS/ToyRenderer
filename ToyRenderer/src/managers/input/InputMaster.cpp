#include "InputMaster.h"
#include "system/Window.h"
#include "InputMapping.h"
#include <string>
#include <iostream>

namespace ToyRenderer {

	std::unordered_map<int, PressedKey> InputMaster::PressedKeys ;
	std::unordered_map<int, PressedKey> InputMaster::ReleasedKeys;
	std::unordered_map<KeyName, int> InputMaster::keyMaping;
	 Mouse InputMaster::mouse;

	static void OnKeyPressed(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		//std::cout << "key: " + std::to_string(key) << " ,scancode: " + std::to_string(scancode) << " ,action: " + std::to_string(action) << " ,mods: " + std::to_string(mods) << std::endl;
		// RELEASE
		switch (action)
		{
		case GLFW_RELEASE:
			if (InputMaster::PressedKeys.find(key) == InputMaster::PressedKeys.end()) return;

			InputMaster::PressedKeys[key].SetUpForRelease();

			InputMaster::ReleasedKeys[key] = InputMaster::PressedKeys[key];
			InputMaster::PressedKeys.erase(key);

			break;

		case GLFW_PRESS:
			// PRESSED
			if (InputMaster::PressedKeys.find(key) != InputMaster::PressedKeys.end()) return;
			if (InputMaster::ReleasedKeys.find(key) != InputMaster::ReleasedKeys.end()) return;


			PressedKey registerKey(window, key);
			InputMaster::PressedKeys[key] = registerKey;
			break;
		}

	

	};

	static void OnMouseButtonPressed(GLFWwindow* window, int key, int action, int mods)
	{
		//std::cout << "key: " + std::to_string(key) << " ,action: " + std::to_string(action) << " ,mods: " +std::to_string(mods) << std::endl;
		// RELEASE
		switch (action)
		{
		case GLFW_RELEASE:

			if (InputMaster::PressedKeys.find(key) == InputMaster::PressedKeys.end()) return;

			InputMaster::PressedKeys[key].SetUpForRelease();

			InputMaster::ReleasedKeys[key] = InputMaster::PressedKeys[key];
			InputMaster::PressedKeys.erase(key);

			break;

		case GLFW_PRESS:

			
			// PRESSED
			if (InputMaster::PressedKeys.find(key) != InputMaster::PressedKeys.end()) return;
			if (InputMaster::ReleasedKeys.find(key) != InputMaster::ReleasedKeys.end()) return;


			PressedKey registerKey(window, key);
			InputMaster::PressedKeys[key] = registerKey;
			break;
		}



	};

	

	TOYRENDERER_GLFWMAPPING


	InputMaster::InputMaster(GLFWwindow* window) : p_window(window)
	{
		MapKeys(keyMaping);

		glfwSetMouseButtonCallback(p_window, (GLFWmousebuttonfun)OnMouseButtonPressed);
		glfwSetKeyCallback(p_window, (GLFWkeyfun)OnKeyPressed);
		mouse = Mouse(p_window);

	}


	InputMaster::~InputMaster()
	{
	}
	void InputMaster::OnUpdate(float deltaTime)
	{
		
		mouse.Update();

		// Handeling PressedKeys
		auto it_pressedKeys = PressedKeys.begin();
		while (it_pressedKeys != PressedKeys.end()) {
			it_pressedKeys->second.IsPressed();
			it_pressedKeys++;
		}

		// Buffering the Released keys for a frame in case the application asks for it then releasing it
		auto it_releasedKeys = ReleasedKeys.begin();
		while (it_releasedKeys != ReleasedKeys.end()) {

			if (it_releasedKeys->second.IsReleased()) {
				it_releasedKeys++;
				continue;
			}

			it_releasedKeys = ReleasedKeys.erase(it_releasedKeys);

		}
	}

	bool InputMaster::GetKeyDown(KeyName keycode) 
	{
		
		if (keyMaping.find(keycode) == keyMaping.end()) return false;
		int keyBackEndCode = keyMaping.at(keycode);

		if (PressedKeys.find(keyBackEndCode) == PressedKeys.end()) return false;
		if (PressedKeys.at(keyBackEndCode).actedOnThisFrame) return true;

		return false;
	}

	bool InputMaster::GetKeyUp(KeyName keycode) 
	{
		if (keyMaping.find(keycode) == keyMaping.end()) return false;
		int keyBackEndCode = keyMaping.at(keycode);

		if (ReleasedKeys.find(keyBackEndCode) == ReleasedKeys.end()) return false;

		return true;
	}

	bool InputMaster::GetKey(KeyName keycode) 
	{
		
		if (keyMaping.find(keycode) == keyMaping.end()) return false;
			

		int keyBackEndCode = keyMaping.at(keycode);

		if (PressedKeys.find(keyBackEndCode) == PressedKeys.end()) return false;

		return true;
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

	/// Update for a pressed key. It checks if the key is still pressed. Sets flag for first frame the key is pressed
	void PressedKey::IsPressed() 
	{
		if (numberOfFramesActive > 0) actedOnThisFrame = false;
		else numberOfFramesActive++;

	}

	void PressedKey::SetUpForRelease()
	{
		actedOnThisFrame = true;
		numberOfFramesActive = 0;
	}

	///Update for a released key. A released keys life time is only a frame
	bool PressedKey::IsReleased()
	{
		if (numberOfFramesActive > 0) return false;
	    numberOfFramesActive++;

		return true;
	}



	Mouse::Mouse()
	{
	}

	Mouse::Mouse(GLFWwindow * window) :window(window)
	{
		double x, y;
		glfwGetCursorPos(window, &x, &y);

		mousePos = Vector2(x, y);
		mouseDelta = Vector2(0.0f, 0.0f);

	}

	void Mouse::Update()
	{

		double x, y;
		glfwGetCursorPos(window, &x, &y);
		
		Vector2 newMousePos((float)x, (float)y);

		if ((newMousePos - mousePos).magnitude() > std::fmin(Window::Width, Window::Height) / 2.0) {
			mousePos = newMousePos;
			mouseDelta;
			return;
		}
		mouseDelta = newMousePos - mousePos;

		mousePos   = newMousePos;

	}

	void Mouse::SetMouseVisible(bool b)
	{
		if(b) glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		else { 
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
			glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
		}
	}

	Vector2 Mouse::GetMouseDelta() const
	{
		return mouseDelta;
	}

}