#ifndef GRAPHICS_CLASS_H
#define GRAPHICS_CLASS_H

#include <Windows.h>

//globals
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	//function declarations
	bool Initialize(int, int, HWND);
	void ShutDown();
	bool Frame();

private :
	bool Render();


};
#endif
