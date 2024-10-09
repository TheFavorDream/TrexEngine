#include "Keyboard.h"


namespace TrexEngine
{

	TX_API std::unordered_map<int, Key> Keyboard::Key_Table;


	TX_API void Keyboard::SetKeyCallBack(GLFWwindow* p_window) 
	{
		glfwSetKeyCallback(p_window, KeyCallBack);
	}

	TX_API void Keyboard::KeyCallBack(GLFWwindow* p_window, int key, int scancode, int action, int mode)
	{

		switch (action)
		{
		case PRESS:
			if (Key_Table[key].OnPress != NULL)
				Key_Table[key].OnPress();
			break;

		case HOLD:
			if (Key_Table[key].OnHold != NULL)
				Key_Table[key].OnHold();
			break;

		case RELEASE:
			if (Key_Table[key].OnRelease != NULL)
				Key_Table[key].OnRelease();

			break;
		}

		Key_Table[key].State = action;
	}

	TX_API int Keyboard::GetKeyState(int Key, bool Restore) const
	{
		int State = Key_Table[Key].State;

		if (Restore)
			Key_Table[Key].State = NONE;

		return State;
	}

	TX_API void Keyboard::SetKeyStateNone(int Key)
	{
		Key_Table[Key].State = NONE;
	}

	TX_API void Keyboard::SetKeyPressCallBack(int Key, void(*CallBackFunction)(void))
	{
		Key_Table[Key].OnPress = CallBackFunction;
	}

	TX_API void Keyboard::SetKeyReleaseCallBack(int Key, void(*CallBackFunction)(void))
	{
		Key_Table[Key].OnRelease = CallBackFunction;
	}

	TX_API void Keyboard::SetKeyHoldCallBack(int Key, void(*CallBackFunction)(void))
	{
		Key_Table[Key].OnHold = CallBackFunction;
	}

};