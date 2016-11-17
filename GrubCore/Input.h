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
	
	//Locks the pointer to the middle of the window.
	static bool LockPointer;
	/**
	Hides the cursor while it is above the registered window.
	*/
	static void HideCursor(bool hide);

	/**
	Register a static method with the parameters (unsigned char key) to be called when an ascii key is pressed.
	*/
	static void ListenForKeyDown(void(*callback)(unsigned char key));
	/**
	Register a static method with the parameters (unsigned char key) to be called when an ascii key is lifted.
	*/
	static void ListenForKeyUp(void(*callback)(unsigned char key));
	/**
	Register a static method with the parameters (int key) to be called when a non-ascii key is pressed.
	*/
	static void ListenForSpecialKeyDown(void(*callback)(int key));
	/**
	Register a static method with the parameters (int key) to be called when a non-ascii key is lifted.
	*/
	static void ListenForSpecialKeyUp(void(*callback)(int key));
	/**
	Register a static method with the parameters (int button, int state, int x, int y) to be called when the mouse is clicked.
	*/
	static void ListenForClick(void(*callback)(int button, int state, int x, int y));
	/**
	Register a static method with the parameters (int x, int y) to be called when the mouse is moved.
	*/
	static void ListenForMove(void(*callback)(int x, int y));
	/**
	Register a static method with the parameters (int x, int y) to be called when the mouse is moved while a mouse button is currently being pressed.
	*/
	static void ListenForDrag(void(*callback)(int x, int y));

	/**
	Removes the specified static function from the registered list of callbacks
	*/
	static void StopListenForKeyDown(void(*callback)(unsigned char key));
	/**
	Removes the specified static function from the registered list of callbacks
	*/
	static void StopListenForKeyUp(void(*callback)(unsigned char key));
	/**
	Removes the specified static function from the registered list of callbacks
	*/
	static void StopListenForSpecialKeyDown(void(*callback)(int key));
	/**
	Removes the specified static function from the registered list of callbacks
	*/
	static void StopListenForSpecialKeyUp(void(*callback)(int key));
	/**
	Removes the specified static function from the registered list of callbacks
	*/
	static void StopListenForClick(void(*callback)(int button, int state, int x, int y));
	/**
	Removes the specified static function from the registered list of callbacks
	*/
	static void StopListenForMove(void(*callback)(int x, int y));
	/**
	Removes the specified static function from the registered list of callbacks
	*/
	static void StopListenForDrag(void(*callback)(int x, int y));
public:
	/**
		The function that is registered to the backend window that will notify all callbacks, is registered by default in Grub.cpp
	*/
	static void KeyboardDownFunc(unsigned char key, int x, int y);
	/**
		The function that is registered to the backend window that will notify all callbacks, is registered by default in Grub.cpp
	*/
	static void KeyboardUpFunc(unsigned char key, int x, int y);
	/**
		The function that is registered to the backend window that will notify all callbacks, is registered by default in Grub.cpp
	*/
	static void SpecialKeyboardDownFunc(int key, int x, int y);
	/**
		The function that is registered to the backend window that will notify all callbacks, is registered by default in Grub.cpp
	*/
	static void SpecialKeyboardUpFunc(int key, int x, int y);
	/**
		The function that is registered to the backend window that will notify all callbacks, is registered by default in Grub.cpp
	*/
	static void ClickFunc(int button, int state, int x, int y);
	/**
		The function that is registered to the backend window that will notify all callbacks, is registered by default in Grub.cpp
	*/
	static void MoveFunc(int x, int y);
	/**
		The function that is registered to the backend window that will notify all callbacks, is registered by default in Grub.cpp
	*/
	static void DragFunc(int x, int y);
public:
	//Lists of function callbacks registered to the input system
	static std::vector<void(*)(unsigned char key)> KeyDownCallbacks;
	static std::vector<void(*)(unsigned char key)> KeyUpCallbacks;
	static std::vector<void(*)(int key)> SpecialKeyDownCallbacks;
	static std::vector<void(*)(int key)> SpecialKeyUpCallbacks;
	static std::vector<void(*)(int button, int state, int x, int y)> ClickCallbacks;
	static std::vector<void(*)(int x, int y)> MoveCallbacks;
	static std::vector<void(*)(int x, int y)> DragCallbacks;
};

#endif