#ifndef GRUB_INPUT
#define GRUB_INPUT
#include "Constants.h"
#include "OpenGL/include/glut.h"
#include <vector>

class Input
{
public:
	Input() = delete;
	static bool warped;
	static bool LockPointer;
	static void HideCursor(bool hide);
	static void ListenForKeyDown(void(*callback)(unsigned char key));
	static void ListenForKeyUp(void(*callback)(unsigned char key));
	static void ListenForClick(void(*callback)(int button, int state, int x, int y));
	static void ListenForMove(void(*callback)(int x, int y));
	static void ListenForDrag(void(*callback)(int x, int y));
	static void StopListenForKeyDown(void(*callback)(unsigned char key));
	static void StopListenForKeyUp(void(*callback)(unsigned char key));
	static void StopListenForClick(void(*callback)(int button, int state, int x, int y));
	static void StopListenForMove(void(*callback)(int x, int y));
	static void StopListenForDrag(void(*callback)(int x, int y));
public:
	static void KeyboardDownFunc(unsigned char key, int x, int y);
	static void KeyboardUpFunc(unsigned char key, int x, int y);
	static void ClickFunc(int button, int state, int x, int y);
	static void MoveFunc(int x, int y);
	static void DragFunc(int x, int y);
public:
	static std::vector<void(*)(unsigned char key)> KeyDownCallbacks;
	static std::vector<void(*)(unsigned char key)> KeyUpCallbacks;
	static std::vector<void(*)(int button, int state, int x, int y)> ClickCallbacks;
	static std::vector<void(*)(int x, int y)> MoveCallbacks;
	static std::vector<void(*)(int x, int y)> DragCallbacks;
};

#endif