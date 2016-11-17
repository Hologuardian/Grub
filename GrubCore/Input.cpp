#include "Input.h"

std::vector<void(*)(unsigned char key)> Input::KeyDownCallbacks;
std::vector<void(*)(unsigned char key)> Input::KeyUpCallbacks;
std::vector<void(*)(int key)> Input::SpecialKeyDownCallbacks;
std::vector<void(*)(int key)> Input::SpecialKeyUpCallbacks;
std::vector<void(*)(int button, int state, int x, int y)> Input::ClickCallbacks;
std::vector<void(*)(int x, int y)> Input::MoveCallbacks;
std::vector<void(*)(int x, int y)> Input::DragCallbacks;
bool Input::warped = false;

bool Input::LockPointer;

void Input::HideCursor(bool hide)
{
	if(hide)
		glutSetCursor(GLUT_CURSOR_NONE);
	else
		glutSetCursor(GLUT_CURSOR_INHERIT);
}

void Input::ListenForKeyDown(void (* callback)(unsigned char key))
{
	Input::KeyDownCallbacks.push_back(callback);
}

void Input::ListenForKeyUp(void(*callback)(unsigned char key))
{
	Input::KeyUpCallbacks.push_back(callback);
}

void Input::ListenForSpecialKeyDown(void(*callback)(int key))
{
	Input::SpecialKeyDownCallbacks.push_back(callback);
}

void Input::ListenForSpecialKeyUp(void(*callback)(int key))
{
	Input::SpecialKeyUpCallbacks.push_back(callback);
}

void Input::ListenForClick(void (* callback)(int button, int state, int x, int y))
{
	Input::ClickCallbacks.push_back(callback);
}

void Input::ListenForMove(void(*callback)(int x, int y))
{
	Input::MoveCallbacks.push_back(callback);
}

void Input::ListenForDrag(void(*callback)(int x, int y))
{
	Input::DragCallbacks.push_back(callback);
}

void Input::StopListenForKeyDown(void(*callback)(unsigned char key))
{
	for (int i = 0; i < Input::KeyDownCallbacks.size(); i++)
	{
		if (Input::KeyDownCallbacks[i] == callback)
		{
			Input::KeyDownCallbacks.erase(Input::KeyDownCallbacks.begin() + i);
		}
	}
}

void Input::StopListenForKeyUp(void(*callback)(unsigned char key))
{
	for (int i = 0; i < Input::KeyUpCallbacks.size(); i++)
	{
		if (Input::KeyUpCallbacks[i] == callback)
		{
			Input::KeyUpCallbacks.erase(Input::KeyUpCallbacks.begin() + i);
		}
	}
}

void Input::StopListenForSpecialKeyDown(void(*callback)(int key))
{
	for (int i = 0; i < Input::SpecialKeyDownCallbacks.size(); i++)
	{
		if (Input::SpecialKeyDownCallbacks[i] == callback)
		{
			Input::SpecialKeyDownCallbacks.erase(Input::SpecialKeyDownCallbacks.begin() + i);
		}
	}
}

void Input::StopListenForSpecialKeyUp(void(*callback)(int key))
{
	for (int i = 0; i < Input::SpecialKeyUpCallbacks.size(); i++)
	{
		if (Input::SpecialKeyUpCallbacks[i] == callback)
		{
			Input::SpecialKeyUpCallbacks.erase(Input::SpecialKeyUpCallbacks.begin() + i);
		}
	}
}

void Input::StopListenForClick(void(*callback)(int button, int state, int x, int y))
{
	for (int i = 0; i < Input::ClickCallbacks.size(); i++)
	{
		if (Input::ClickCallbacks[i] == callback)
		{
			Input::ClickCallbacks.erase(Input::ClickCallbacks.begin() + i);
		}
	}
}

void Input::StopListenForMove(void(*callback)(int x, int y))
{
	for (int i = 0; i < Input::MoveCallbacks.size(); i++)
	{
		if (Input::MoveCallbacks[i] == callback)
		{
			Input::MoveCallbacks.erase(Input::MoveCallbacks.begin() + i);
		}
	}
}

void Input::StopListenForDrag(void(*callback)(int x, int y))
{
	for (int i = 0; i < Input::DragCallbacks.size(); i++)
	{
		if (Input::DragCallbacks[i] == callback)
		{
			Input::DragCallbacks.erase(Input::DragCallbacks.begin() + i);
		}
	}
}

void Input::KeyboardDownFunc(unsigned char key, int x, int y)
{
	for each(void(*callback)(unsigned char key) in Input::KeyDownCallbacks)
	{
		callback(key);
	}
}

void Input::KeyboardUpFunc(unsigned char key, int x, int y)
{
	for each(void(*callback)(unsigned char key) in Input::KeyUpCallbacks)
	{
		callback(key);
	}
}

void Input::SpecialKeyboardDownFunc(int key, int x, int y)
{
	for each(void(*callback)(int key) in Input::SpecialKeyDownCallbacks)
	{
		callback(key);
	}
}

void Input::SpecialKeyboardUpFunc(int key, int x, int y)
{
	for each(void(*callback)(int key) in Input::SpecialKeyUpCallbacks)
	{
		callback(key);
	}
}

void Input::ClickFunc(int button, int state, int x, int y)
{
	for each(void(*callback)(int button, int state, int x, int y) in Input::ClickCallbacks)
	{
		callback(button, state, x, y);
	}
}

void Input::MoveFunc(int x, int y)
{
	if (warped)
	{
		warped = false;
		return;
	}
	for each(void(*callback)(int x, int y) in Input::MoveCallbacks)
	{
		callback(x, y);
	}
	if (LockPointer)
	{
		warped = true;
		glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
	}
}

void Input::DragFunc(int x, int y)
{
	if (warped)
	{
		warped = false;
		return;
	}
	for each(void(*callback)(int x, int y) in Input::DragCallbacks)
	{
		callback(x, y);
	}
	if (LockPointer)
	{
		warped = true;
		glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
	}
}
