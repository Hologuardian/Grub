#include "Direct3D.h"



Direct3D::Direct3D()
{
}


Direct3D::~Direct3D()
{
}

/** This will Init Direct3D
@Param hInstance : The handle to the applications instance
**/
bool::Direct3D::InitializeDirect3D11App(HINSTANCE hInstance)
{
	HRESULT	hr;

	//Describe our Buffer
	DXGI_MODE_DESC bufferDesc;

	ZeroMemory(&bufferDesc, sizeof(DXGI_MODE_DESC));

	//I need Mains variables here to parse the description of the GPU
	//bufferDesc.Width = Main->Width;

}