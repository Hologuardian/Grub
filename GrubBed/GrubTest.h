#ifndef GRUB_GRUB_TEST_H
#define GRUB_GRUB_TEST_H
#include "Grub.h"

class GrubTest : public Grub
{
public:
	GrubTest(int argc, char** argv);
	void Update(float Delta);
	void Render();
	void Initialize();
	static void Keyboard(unsigned char key);
	static void KeyboardUp(unsigned char key);
	static void MouseMove(int x, int y);
	static void MouseDrag(int x, int y);
};

#endif