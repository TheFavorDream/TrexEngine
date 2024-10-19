#include "Keyboard.h"


namespace TrexEngine
{


	TX_API std::unordered_map<int, Key> Keyboard::Key_Table;
	TX_API std::string* Keyboard::Current_String;
	TX_API bool Keyboard::IsReadingText = false;
	TX_API bool Keyboard::IsCapsLockOn = false;
	TX_API bool Keyboard::IsNumPadOn = false;

	TX_API void Keyboard::SetKeyCallBack(GLFWwindow* p_window) 
	{
		glfwSetKeyCallback(p_window, KeyCallBack);
		glfwSetCharCallback(p_window, CharacterCallBack);

	}

	TX_API void Keyboard::KeyCallBack(GLFWwindow* p_window, int key, int scancode, int action, int mode)
	{
		if (IsReadingText)
		{
			if (key >= KEY_A && key <= KEY_Z)
				return;
		}


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

	TX_API void Keyboard::CharacterCallBack(GLFWwindow * p_window, unsigned int codepoint)
	{

		if (IsReadingText)
		{
			*Current_String += char(codepoint);
		}
	}


	TX_API int Keyboard::GetKeyCurrentState(int Key)
	{
		return Key_Table[Key].State;
	}


	TX_API void Keyboard::PopTheLastChar()
	{
		if (IsReadingText)
		{
			if ((*Current_String) != "")
				Current_String->pop_back();
			return;
		}

		Logger::CoreLogger->SetError("Unable to Pop char while not on reading mode!");
	}

	TX_API bool Keyboard::IsKeyPressed(int Key)
	{
		if (GetKeyCurrentState(Key) == PRESS)
		{
			ResetKey(Key);
			return true;
		}

		return false;
	}

	TX_API bool Keyboard::IsKeyReleased(int Key) 
	{
		if (GetKeyCurrentState(Key) == RELEASE)
		{
			ResetKey(Key);
			return true;
		}

		return false;
	}

	TX_API bool Keyboard::IsKeyHold(int Key) 
	{
		if (GetKeyCurrentState(Key) == HOLD)
		{
			ResetKey(Key);
			return true;
		}

		return false;
	}

	TX_API void Keyboard::ResetKey(int Key)
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

	TX_API void Keyboard::StartTextInput(std::string& p_Text)
	{

		if (!IsReadingText)
		{
			Current_String = &p_Text;
			IsReadingText = true;

			Key_Table[KEY_BACKSPACE].OnPress = PopTheLastChar;
			Key_Table[KEY_BACKSPACE].OnHold = PopTheLastChar;
		}

		else		
		{
			Logger::CoreLogger->SetError("There is already a text inputing");
			return;
		}
	}

	TX_API void Keyboard::StopTextInput()
	{
		if (!IsReadingText)
		{
			Logger::CoreLogger->SetError("There is no current text inputing to be stoped");
			return;
		}


		IsReadingText = false;
	}

	TX_API bool Keyboard::GetCapsLockState()
	{
		if ((GetKeyState(VK_CAPITAL) & 0x0001) == 1)
		{
			IsCapsLockOn = true;
			return true;
		}
		IsCapsLockOn = false;
		return false;
	}

	TX_API bool Keyboard::GetNumPadState()
	{
		if ((GetKeyState(VK_NUMLOCK) & 0x0001) == 1)
		{
			IsNumPadOn = true;
			return true;
		}
		IsNumPadOn = false;
		return false;
	}

};