#ifndef _D3DCLASS_H_
#define _D3DCLASS_H_

//Linking 
#pragma comment(lib, "d3d11.lib") //compiler directive, will link at compile time. get rid of these and do it the proper way after
#pragma comment(lib, "dgix.lib")
#pragma comment(lib, "d3dcompiler.lib")

//Includes

//Headers for above lib files, as well as headers for DirectX typedefs and math functionality
#include <d3d11.h>
#include <directxmath.h>
using namespace DirectX;

class D3DClass
{
public:
	D3DClass();
	D3DClass(const D3DClass&);
	~D3DClass();

	bool Initialize(int, int, bool, HWND, bool, float, float);
	void ShutDown();
	void BeginScene(float, float, float, float);
	void EndScene();	

	ID3D11Device* GetDevice(); //get pointer to the device that created this interface
	ID3D11DeviceContext* GetDeviceContext(); //look this up??

	void GetProjectionMatrix(XMMATRIX&);
	void GetWorldMatrix(XMMATRIX&);
	void GetOrthoMatrix(XMMATRIX&);

	void GetVideoCardInfo(char*, int&); //get specs of GPU

private:
	bool vsyncEnabled;
	int videoCardMemory;
	char videoCardDescription[128];
	IDXGISwapChain* swapChain;
	ID3D11Device* device;
	ID3D11DeviceContext* deviceContext;
	ID3D11RenderTargetView* renderTargetView;	
	ID3D11Texture2D* depthStencilBuffer;
	ID3D11DepthStencilState* depthStencilState;
	ID3D11DepthStencilView* depthStencilView;
	ID3D11RasterizerState* rasterState;
	XMMATRIX projectionMatrix;
	XMMATRIX worldMatrix;
	XMMATRIX orthoMatrix;
};

#endif