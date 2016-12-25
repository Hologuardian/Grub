#include "Constants.h"
#ifdef GRUB_DX11
#ifndef GRAPHICS_CLASS_H_
#define GRAPHICS_CLASS_H_

#include "d3dClass.h"

//GLOBAL VARIABLES
const bool FULL_SCREEN = true;
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

private:
	bool Render();

	D3DClass* Direct3D;

};

#endif
#endif
