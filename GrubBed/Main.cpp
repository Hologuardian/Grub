#include <stdio.h>
#include "Constants.h"
#include "GrubTest.h"


Grub* NewGame;

#ifdef GRUB_USEOPENGL
int main(int argc, char** argv) {
	Clock::init();
	NewGame = new GrubTest(argc, argv);
	Grub::instance = NewGame;
	NewGame->Initialize();
	while (true)
		;
	getchar();
	return(0);
}
#endif

#ifdef GRUB_DX11

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3d10.lib")

#include <windows.h>
#include <DXGI.h>
#include <d3d11.h>
#include <d3d10.h>
#include <DirectXMath.h>

IDXGISwapChain* SwapChain; //changes front buffer to back buffer and vise versa aka double rendering
ID3D11Device* d3d11Device; //represents the GPU
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
const float bgColor[] = { red, green, blue, 1.0f };

LPCTSTR WndClassName = "Grub";
HWND hwnd = NULL;

//define width and height of window
const int Width = 800;
const int Height = 600;

bool InitializeDirect3D11App(HINSTANCE hInstance); //Will init Direct3D
void ReleaseObjects();	//Release objects we don't need to prevent memory leaks
bool InitScene();		//set up a scene
void UpdateScene();		//Update scene per-frame
void DrawScene();		//Draw scene to screen, also updated per-frame


/** InitializeWindow() function will do what it says, then depending on if the window was made or not, 
return either true or false.Then we initialize the message loop function, 
which is the function that keeps our program running 
@param hInstance : The handle to our current application
@param ShowWnd   : How the window should be displayed.
@param Width	 : Width of the window in pixels
@param Height	 : Height of the window in pixels
@param Windowed  : False if the window is fullscreen, true if it's windowed
**/
bool InitializeWindow(HINSTANCE hInstance, int ShowWnd, int width, int height, bool windowed);
int messageloop();

/** Initialize the windows callback procedure. Windows API is an "event-driven" programming model, 
so in this function, we can "capture" windows messages, like a key press (also called events) and 
manipulate the flow of our program.
**/
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

//The entry point to the application
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	//register the window, will return true or false based on if the window was registered and created
	if (!InitializeWindow(hInstance, nShowCmd, Width, Height, true))
	{
		MessageBox(0, "Window Initialization - Failed", "Error", MB_OK);
		Logger::Log(EMessageType::LOG_ERROR, "Window Initialization - Failed");

		return 0;
	}
	Logger::Log(EMessageType::LOG_ERROR, "Window Initialization - OK");

	if (!InitializeDirect3D11App(hInstance)) //Initialize Direct3D
	{
		MessageBox(0, "Direct3D Initialization - Failed ",
			"Error", MB_OK);
		return 0;
	}

	if (!InitScene()) //Initialize our Scene
	{
		MessageBox(0, "Scene Initialization - Failed ",
			"Error", MB_OK);
		return 0;
	}

	messageloop();

	ReleaseObjects();
	return 0;
}

/**create and register the class 
@param hInstance : The handle to our current application
@param ShowWnd   : How the window should be displayed. 
@param Width	 : Width of the window in pixels
@param Height	 : Height of the window in pixels
@param Windowed  : False if the window is fullscreen, true if it's windowed
**/
bool InitializeWindow(HINSTANCE hInstance, int ShowWnd, int width, int height, bool windowed)
{
	//create an extended styles windows class called wc, then fill out all the properties. 
	WNDCLASSEX wc;

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = NULL;
	wc.cbWndExtra = NULL;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WndClassName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	//register the class, if it fails we get an error. If it passes we move on to create the window
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Error registering class", "Error", MB_OK | MB_ICONERROR);
		Logger::Log(EMessageType::LOG_ERROR, "Error registering class");
		return 1;
	}

	//create the window
	hwnd = CreateWindowEx(NULL, WndClassName, "Grub", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
		CW_USEDEFAULT, width, height, NULL, NULL, hInstance, NULL);
	
	if (!hwnd)
	{
		MessageBox(NULL, "Error Creating Window", "Error", MB_OK | MB_ICONERROR);
		Logger::Log(EMessageType::LOG_ERROR, "Error Creating Window");
		return 1;
	}


	//we need to now show the window and refresh it using UpdateWindow()
	ShowWindow(hwnd, ShowWnd);

	/** send a WM_PAINT message directly to the windows procedure. If there isn't anything in the client area
	of the window, then UpdateWindow() does not send a message. We then return true so our WinMain() 
	function can get on to the message loop.
    **/
	UpdateWindow(hwnd); 

	return true;
}

/** This will Init Direct3D
@Param hInstance : The handle to the applications instance
**/
bool InitializeDirect3D11App(HINSTANCE hInstance)
{
	HRESULT	hr; //used for error checking

				//Describe our Buffer
	DXGI_MODE_DESC bufferDesc;

	ZeroMemory(&bufferDesc, sizeof(DXGI_MODE_DESC));

	bufferDesc.Width = Width;						//Width of resolution
	bufferDesc.Height = Height;						//Height of resolution
	bufferDesc.RefreshRate.Numerator = 60;
	bufferDesc.RefreshRate.Denominator = 1;			//Describes refresh rate in hertz 60/1 = 60hz
	bufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; //Describes format of the display 8 bits allocated for each
	bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED; //Describes the order the rasterizer will render onto a surface, because were using double rendering the order doesnt really matter
	bufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED; //Describes how an image will be stretched to fit a monitors resolution

														//Describe our swap chain
	DXGI_SWAP_CHAIN_DESC swapChainDesc;

	ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

	swapChainDesc.BufferDesc = bufferDesc;	//Describes the BackBuffer
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;	//Describes the Multi-Sampling
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; //Decribes the access the cpu has to the surface of the backbuffer
	swapChainDesc.BufferCount = 1;			//number of back buffers to be used, can use more if wanted
	swapChainDesc.OutputWindow = hwnd;		//Handle to our window
	swapChainDesc.Windowed = TRUE;			//True for windowed, False for full-screen CARE WITH FULL-SCREEN
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD; //What the display driver should do with th front buffer after swaping it with the back-buffer. In this case we let it decide what the most efficient setting is
	swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH; //changes resolution when swapping windowed - fullscreen

																  //Create our swap Chain

#pragma region SwapChain
																  /*Creates the Direct3D Device, Device Context, and Swap Chain by calling the Direct3D core function
																  the function's parameters look like this:

																  HRESULT D3D11CreateDeviceAndSwapChain(
																  __in   IDXGIAdapter *pAdapter,		//pointer to the GPU, or Video Adapter set NULL to use default
																  __in   D3D_DRIVER_TYPE DriverType,	//how D3D will be implemented. use D3DDRIVER_TYPE_HARDWARE to say it will be implented by the GPU
																  __in   HMODULE Software,				//HMODULE handle to a DLL that will be used to implement software rasterizing
																  __in   UINT Flags,				//This is one or more D3D11_CREATE_DEVICE_FLAG types or'ed together.
																  __in   const D3D_FEATURE_LEVEL *pFeatureLevels, //What version of Directx to use. NULL will use highest features avalliable
																  __in   UINT FeatureLevels,	//number of elements in the pFeatureLevels array. set to NULL.
																  __in   UINT SDKVersion,		//Version of the DirectX SDK. Use D3D11_SDK_VERSION.
																  __in   const DXGI_SWAP_CHAIN_DESC *pSwapChainDesc,	//a pointer to the swapChainDesc we created above
																  __out  IDXGISwapChain **ppSwapChain,	//pointer to an IDGXISwapChain interface to recieve the created SwapChain
																  __out  ID3D11Device **ppDevice, //pointer to our D3D device.
																  __out  D3D_FEATURE_LEVEL *pFeatureLevel, //pointer to D3D_FEAUTRE_LEVEL will hold the highest	feature avaliable(Feature levels are used for backwards compatibility)
																  __out  ID3D11DeviceContext **ppImmediateContext //pointer to device context will be used for the rendering methods of the device, to support multi-threading and boost performance.
																  );*/
#pragma endregion SwapChainExplanation

	hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, NULL, NULL, NULL,
		D3D11_SDK_VERSION, &swapChainDesc, &SwapChain, &d3d11Device, NULL, &d3d11DevCon);

	//Create our BackBuffer

#pragma region BackBuffer
	/*Create the back buffer which will be used to create the render target view. We call the
	GetBuffer() method of the SwapChain interface:

	HRESULT GetBuffer(
	[in]       UINT Buffer,	//Since we set swapChainDesc.SwapEffect to DXGI_SWAP_EFFECT_DISCARD, we only have access to the first buffer, so we set to 0.
	[in]       REFIID riid,	//reference ID to the type of interface to change the back buffer. We use a 2d texture (ID3D11Texture2D).
	[in, out]  void **ppSurface //pointer to the BackBuffer we created above, the surface we render to.
	);*/
#pragma endregion BackBufferExplanation

	ID3D11Texture2D* BackBuffer;
	hr = SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&BackBuffer);

	//Create our render target

#pragma region RenderTarget
	/*Now create our RenderTargetView, which we will send to the output merger stage of the pipeline.
	We can create our RenderTargetView by calling CreateRenderTargetView of our device interface

	HRESULT CreateRenderTargetView(
	[in]   ID3D11Resource *pResource,	//our backbuffer
	[in]   const D3D11_RENDER_TARGET_VIEW_DESC *pDesc, //pointer to the Target_View_Desc struct We set NULL to create a view that accesses all of the subresources in mipmap level 0.
	[out]  ID3D11RenderTargetView **ppRTView // This is a pointer to our ID3D11RenderTargetView interface, renderTargetView.

	);*/
#pragma endregion RenderTargetExplanation

	hr = d3d11Device->CreateRenderTargetView(BackBuffer, NULL, &renderTargetView);
	BackBuffer->Release(); //Relase it when we dont need it anymore


						   //Set our Render Target

#pragma region RenderTargetSet
						   /*And the last thing we do while initializing, is bind the render target view to the output merger
						   stage of the pipeline. This function will also bind our depth/stencil buffer as well, but we have
						   not created one yet, so we set that parameter to NULL.

						   void OMSetRenderTargets(
						   [in]  UINT NumViews, //Number of render targets to bind. We only have one
						   [in]  ID3D11RenderTargetView *const **ppRenderTargetViews, //Array of render target views to bind
						   [in]  ID3D11DepthStencilView *pDepthStencilView //pointer to depth stencil buffer. We do not have one yet so set to NULL
						   );*/
#pragma endregion SetRenderTargetExplanation

	d3d11DevCon->OMSetRenderTargets(1, &renderTargetView, NULL);

	return true;
}

void ReleaseObjects()
{
	//Release the COM objects we created not doing this will cause memory leaks
	SwapChain->Release();
	d3d11Device->Release();
	d3d11DevCon->Release();
}

/*The InitScene() function will be used to initialize our scene. In a video game, you will probably have
many different scenes, so you will probably want to rename them from InitScene(). We will place our
objects, load our models, textures, sounds, all that must be done to start off that specific scene.
*/
bool InitScene()
{
	return true;
}

/*Next we have our UpdateScene() function. We will use this function to do all the updating of our scene,
like changing objects locations, changing values, anything that changes in our scene will be done here.
In this lesson, we will just change the color of our background, so in the update scene function, we will
just change the color.
*/
void UpdateScene()
{
	//Update the color of our scene
	red += colormodr * 0.00005f;
	green += colormodg * 0.00002f;
	blue += colormodb * 0.00001f;

	if (red >= 1.0f || red <= 0.0f)
		colormodr *= -1;
	if (green >= 1.0f || green <= 0.0f)
		colormodg *= -1;
	if (blue >= 1.0f || blue <= 0.0f)
		colormodb *= -1;
}

/*This is were we render our scene do not update here, only draw*/
void DrawScene()
{

	//Clear our backbuffer to the updated color
	//DirectX::XMFLOAT4 bgColor(red, green, blue, 1.0f);
	d3d11DevCon->ClearRenderTargetView(renderTargetView, bgColor);

	//Present the backbuffer to the screen
	SwapChain->Present(0, 0);
}



int messageloop()
{
	
	MSG msg; //make instance to MSG structure
	ZeroMemory(&msg, sizeof(MSG)); //clears the struct and sets it to null

	while (true) //while thre's a message...
	{
		BOOL PeekMessageL(
			LPMSG lpMsg,
			HWND hWnd,
			UINT wMsgFilterMin,
			UINT wMsgFilterMax,
			UINT wRemoveMsg
		);

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{

			if (msg.message == WM_QUIT) //If the message was a quit message, we close our program.
				break;
			
			TranslateMessage(&msg);//If our message was a windows message, we translate then dispatch.
			DispatchMessage(&msg);
		}
		else //if there ws not a windows message, we run our game
		{
			//run game code here
			UpdateScene();
			DrawScene();
		}
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//check the message for events
	switch (msg)
	{
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
		{
			if (MessageBox(0, "Are you sure you want to exit?", "Really?", MB_YESNO | MB_ICONQUESTION) == IDYES)
				DestroyWindow(hwnd);
		}
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	/*This is the default windows procedure function. We call this at the end to take care of all the 
	messages we recieve but don't take care of ourselves.*/
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

#endif