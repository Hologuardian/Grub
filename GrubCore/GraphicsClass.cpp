#include "GraphicsClass.h"

//Simple framework for now will draw polys and models later. Might refactor to marks solution after code review


GraphicsClass::GraphicsClass()
{

}

GraphicsClass::GraphicsClass(const GraphicsClass& other)
{

}

GraphicsClass::~GraphicsClass()
{
}

//Create D3Dclass object and call it's init function. Send relevant window information to object
//so it can set up the Direct3D system.
bool::GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;


}