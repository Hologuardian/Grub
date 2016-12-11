#include "GraphicsClass.h"

//Simple framework for now, will draw polys and models later

GraphicsClass::GraphicsClass()
{
	Direct3D = 0;
}

GraphicsClass::GraphicsClass(const GraphicsClass& other)
{

}
GraphicsClass::~GraphicsClass()
{
}

/*create D3DClass object and call it's Init function. Send relevant window information to object
so it can set up the Direct3D system*/
bool::GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;

	//Create D3D object
	Direct3D = new D3DClass;

	if (!Direct3D)
	{
		return false;
	}

	//Init the D3D object
	result = Direct3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN,
		SCREEN_DEPTH, SCREEN_NEAR);

	if (!result)
	{
		MessageBox(hwnd, L"Couldn't Init Direct3D", L"Error", MB_OK);
		return false;
	}
	return true;
}

/*The shutdown of all graphics objects occur here, so I included D3D's Shutdown in this function.
It's important to check if the pointer was initialized or not, because if it wasn't it can be assumed
that it was never set up and and we don't have to call ShutDown() this is why it's important to NULL pointers
in class constructors*/

void::GraphicsClass::ShutDown()
{
	//Release the D3D object
	if (Direct3D)
	{
		Direct3D->ShutDown();
		delete Direct3D;
		Direct3D = 0;
	}
	return;
}

bool::GraphicsClass::Frame()
{
	bool result;

	//Render the graphics scene
	result = Render(); //called every frame
	if (!result)
	{
		return false;
	}
	return true;
}

//call Direct3D object to clear screen to a grey color. Then call EndScene so that it is displayed to window
bool::GraphicsClass::Render()
{
	//clear the buffers to begin the scene
	Direct3D->BeginScene(0.5f, 0.5f, 0.5f, 1.0f);

	//Present rendered scene to screen
	Direct3D->EndScene();

	return true;
}
