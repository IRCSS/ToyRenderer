#include "InputMaster.h"
#include "Settings.h"
namespace ToyRenderer {
	InputMaster::InputMaster()
	{
		MouseId    = manager.CreateDevice<gainput::InputDeviceMouse>();
		KeyboardId = manager.CreateDevice<gainput::InputDeviceKeyboard>();
		manager.SetDisplaySize(Settings::WindowWidth, Settings::WindowHeigth);
		map = new gainput::InputMap(manager);


		map->MapBool(Key::LeftMouseButton, MouseId, gainput::MouseButtonLeft);
		map->MapBool(Key::A, KeyboardId, gainput::KeyA);


	}
	InputMaster::~InputMaster()
	{
		delete map;
	}
	void InputMaster::OnUpdate(float deltaTime)
	{

		manager.Update();
	}

	bool InputMaster::GetKeyDown(Key keycode)
	{

		return map->GetBoolWasDown(keycode);
	}



}