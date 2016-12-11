#include "D3DClass.h"



D3DClass::D3DClass()
{
	//NULL out pointers 
	swapChain = nullptr;
	device = nullptr;
	deviceContext = nullptr;
	renderTargetView = nullptr;
	depthStencilBuffer = nullptr;
	depthStencilState = nullptr;
	depthStencilView = nullptr;
	rasterState = nullptr;

}


D3DClass::~D3DClass()
{
}

/*Completes entire setup for Direct3D and DirectX11. screenWidth/screenHeight are variables pulled*/