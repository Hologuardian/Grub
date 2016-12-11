#include "InputClass.h"


InputClass::InputClass()
{
}

InputClass::InputClass(const InputClass& other)
{
}

InputClass::~InputClass()
{
}

void::InputClass::Initialize()
{
	int i;

	//initialize all the keys to released instead of pressed
	for (int i = 0; i < 256; i++)
	{
		keys[i] = false;
	}
	return;
}

void::InputClass::KeyDown(unsigned int input)
{
	//if key is pressed save that state in the key array
	keys[input] = true;
	return;
}

void::InputClass::KeyUp(unsigned int input)
{
	//if key is released clear the state from the key array
	keys[input] = false;
	return;
}

bool::InputClass::IsKeyDown(unsigned int key)
{
	//return what state the key is in (pressed/released)
	return keys[key];
}