#ifndef DIRECT3D_H
#define DIRECT3D_H

 #include <DXGI.h>
#include <d3d11.h>


class Direct3D
{
public:
	Direct3D();
	~Direct3D();

	IDXGISwapChain* SwapChain; //changes front buffer to back buffer and vise versa aka double rendering
	ID3D11Device* d3dDevice; //represents the GPU
	ID3D11DeviceContext* d3d11DevCon; // allows for multi-thread rendering calls.
	
	/*we never write directly to the screen, instead we write to the backbuffer, then the texture is sent
	to the output merger stage of the pipeline as our render target, which will be rendered to the screen*/
	ID3D11RenderTargetView* renderTargetView;

	float red = 0.0f;
	float green = 0.0f;
	float blue = 0.0f;
	int colormodr = 1;
	int colormodg = 1;
	int colormodb = 1;	//changes the color of the background

	bool InitializeDirect3D11App(HINSTANCE hInstance); //Will init Direct3D
	void ReleaseObject();	//Release objects we don't need to prevent memory leaks
	bool InitScene();		//set up a scene
	void UpdateScene();		//Update scene per-frame
	void DrawScene();		//Draw scene to screen, also updated per-frame

};
#endif

