#ifndef GRUB_ABSTRACT_WINDOW_H
#define GRUB_ABSTRACT_WINDOW_H
#include "Model.h"
#include "Constants.h"
#include "Camera.h"

class AbstractWindow
{
public:
	enum PrimativeType {
		NONE,
		QUAD,
		TRI,
		TRIFAN,
		POLY
	};
	Grubuint program;
	virtual ~AbstractWindow();
	virtual void MakeWindow(int argc, char** argv) = 0;
	virtual void SetUpdate(void (UpdateCallBack)()) = 0;
	virtual void SetDisplay(void (Display)()) = 0;
	virtual void SetInput(void(*KeyboardDown)(unsigned char key, int x, int y), void(*KeyboardUp)(unsigned char key, int x, int y), void(*Click)(int button, int state, int x, int y), void(*Move)(int x, int y), void(*Drag)(int x, int y)) = 0;
public:
	virtual void renderPrimitive(PrimativeType prim, Grubuint VAO, int start, int length) = 0;
	virtual void renderModel(Model* model) = 0;
	virtual void startRender() = 0;
	virtual void endRender() = 0;
	virtual void begin() = 0;
	virtual Camera* GetCamera() = 0;
};

#endif