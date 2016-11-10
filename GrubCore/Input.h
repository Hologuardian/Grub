#ifndef GRUB_INPUT
#define GRUB_INPUT
#include "Constants.h"

class Input
{
public:
	int IsKeyDown(int key);
	Vector2 GetMousePosition();
};

#endif