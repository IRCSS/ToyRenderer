#pragma once
#include "Core.h"
#include "vendor/GLFW/glfw3.h"
#include "maths/Vector2.h"
#include <unordered_map>
namespace ToyRenderer {

	enum KeyName {
		A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, // Keyboard Keys
		LeftShift, LeftCtrl, LeftAlt,
		RightShift,  RightCtrl,  RightAlt, 
		Space, Enter,
		LeftMouseButton, RightMouseButton, MouseMiddle, MouseLast,
		MouseButton1, MouseButton2, MouseButton3, MouseButton4,
		MouseButton5, MouseButton6, MouseButton7, MouseButton8,
		JoyStick1, JoyStick2, JoyStick3, JoyStick4, JoyStick5, 
		JoyStick6, JoyStick7, JoyStick8, JoyStick9, JoyStick10, 
		JoyStick11, JoyStick12, JoyStick13, JoyStick14, JoyStick15, JoyStick16,
		GampadA, GampadB, GampadX, GampadY, GampadLeftBumper, 
		GampadRightBumper, GampadBack, GampadStart, GampadGuide,
		GampadLeftThumb, GampadRightThumb, GampadDPadUp, GampadDpadRight, 
		GampadDpadDown, GampadDpadLeft, GampadCross, GampadCricle,
		GampadSquare, GampadTriangle,
		ArrowLeft, ArrowRight, ArrowUp, ArrowDown,
		Apostrophe, Comma, Minus, Period, Slash, Semicolon, Equal, LeftBracket, Backlash, 
		RightBracket, GraveAccent, Escape, Tab, Backspace, Insert, Delete, PageUp, PageDown, 
		Home, End, CapsLock, ScrollLock, NumLock, PrintScreen, Pause, 
		K0, K1, K2, K3, K4, K5, K6, K7, K8, K9,
		F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
		KP0, KP1, KP2, KP3, KP4, KP5, KP6, KP7, KP8, KP9, 
		KPDecimal, KPDivide, KPMultiply, KPSubtract, KPAdd, KPEnter, KPEqual,
	};


	struct TOYRENDERER_API PressedKey {

	// PUBLIC ======================================================================================
	public:
		PressedKey();
		PressedKey(const PressedKey& copyFrom);
		PressedKey(GLFWwindow* pWindow, int keyCode);

		void IsPressed();
		void SetUpForRelease();
		bool IsReleased();
	public: 
		bool        actedOnThisFrame;
		GLFWwindow*	window;
		int         keyCode;

    // ______________________________________________________________________________________________
	// PRIVATE ======================================================================================
	private:
		
		int numberOfFramesActive;


	};

	class TOYRENDERER_API Mouse {
	// PUBLIC ======================================================================================	
	public: 

		Mouse();
		Mouse(GLFWwindow* window);
		void    Update();
		void    SetMouseVisible(bool b);
		Vector2 GetMouseDelta() const;
	public: 
		/// Screen space, from top left corner
		Vector2 mousePos;
    // ______________________________________________________________________________________________
	// PRIVATE ======================================================================================
	private:
		Vector2 mouseDelta;
		GLFWwindow* window;

	};

	class TOYRENDERER_API InputMaster {
	// PUBLIC ======================================================================================
	public:
		 InputMaster(GLFWwindow* window);
		~InputMaster();

		void OnUpdate(float deltaTime);

		static bool GetKeyDown(KeyName keycode);
		static bool GetKeyUp  (KeyName keycode);
		static bool GetKey    (KeyName keycode);
    #pragma warning( disable : 4251)  
	public: 
		static std::unordered_map<KeyName, int> keyMaping;

		static std::unordered_map<int, PressedKey> PressedKeys;
		static std::unordered_map<int, PressedKey> ReleasedKeys;

		static Mouse mouse;

    #pragma warning(default:4251) 
	private:
		GLFWwindow* p_window;


	};
}