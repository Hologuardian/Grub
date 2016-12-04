#ifndef GRUB_ABSTRACT_WINDOW_H
#define GRUB_ABSTRACT_WINDOW_H
#include "Model.h"
#include "Constants.h"
#include "Camera.h"
#include "GraphicPrimitive.h"

class Window
{
public:
	//A uint pointer to a loaded set of shaders that draw to the screen.
	Grubuint program;
	//A uint pointer to a loaded set of shaders that draw to the screen.
	Grubuint uiprogram;
	virtual ~Window() {};

	virtual void MakeWindow(int argc, char** argv) = 0;

	//Main loop setups are set up and registered to the backend by the window's specific sub class
	virtual void SetUpdate(void (UpdateCallBack)()) = 0;
	virtual void SetDisplay(void (Display)()) = 0;
	//Will start any main loops that may be registered to the window.
	virtual void begin() = 0;

	//Input Functions, the window is also in charge of registering function callbacks for input functions
	virtual void SetKeyDownInput(void(*KeyboardDown)(unsigned char key, int x, int y)) = 0;
	virtual void SetKeyUpInput(void(*KeyboardUp)(unsigned char key, int x, int y)) = 0;
	virtual void SetMouseClickInput(void(*Click)(int button, int state, int x, int y)) = 0;
	virtual void SetMouseMoveInput(void(*Move)(int x, int y)) = 0;
	virtual void SetMouseDragInput(void(*Drag)(int x, int y)) = 0;
	virtual void SetSpecialKeyDownInput(void(*SpecialDown)(int key ,int x, int y)) = 0;
	virtual void SetSpecialKeyUpInput(void(*SpecialUp)(int key, int x, int y)) = 0;
public:
	virtual void renderPrimitive(Primitive prim, Grubuint VAO, int start, int length) = 0;
	virtual void renderModel(Model* model) = 0;
	//Deals with all pre-render global settings for the window
	virtual void startRender() = 0;
	//Finishes any render settings for the window and should draw the buffer to screen
	virtual void endRender() = 0;
	//A getter for the camera attached to the window.
	virtual Camera* GetCamera() = 0;
};

#endif