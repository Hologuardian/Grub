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
#pragma comment(lib, "d3dcompiler.lib")

#include <windows.h>
#include <DXGI.h>
#include <d3d11.h>
#include <d3d11sdklayers.h>
#include <d3dcompiler.h>
#include <d3d10.h>
#include <DirectXMath.h>
#include <LoadShaders.h>

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

LPCTSTR WndClassName =  "Grub";
HWND hwnd = NULL;
HRESULT	hr; //used for error checking


//define width and height of window
const int Width = 800;
const int Height = 600;

bool InitializeDirect3D11App(HINSTANCE hInstance); //Will init Direct3D
void ReleaseObjects();	//Release objects we don't need to prevent memory leaks
bool InitScene();		//set up a scene
void UpdateScene();		//Update scene per-frame
void DrawScene();		//Draw scene to screen, also updated per-frame

#pragma region Initialize Window Documentation

/** InitializeWindow() function will do what it says, then depending on if the window was made or not, 
return either true or false.Then we initialize the message loop function, 
which is the function that keeps our program running 

@param hInstance : The handle to our current application
@param ShowWnd   : How the window should be displayed.
@param Width	 : Width of the window in pixels
@param Height	 : Height of the window in pixels
@param Windowed  : False if the window is fullscreen, true if it's windowed
**/
#pragma endregion 

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

#pragma region Create and Register Window Class Documentation

/**create and register the class 
@param hInstance : The handle to our current application
@param ShowWnd   : How the window should be displayed. 
@param Width	 : Width of the window in pixels
@param Height	 : Height of the window in pixels
@param Windowed  : False if the window is fullscreen, true if it's windowed
**/
#pragma endregion

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

#pragma region SwapChain Documentation

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
#pragma endregion 

	hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, NULL, NULL, NULL,
		D3D11_SDK_VERSION, &swapChainDesc, &SwapChain, &d3d11Device, NULL, &d3d11DevCon);


#pragma region BackBuffer Documentation
	/*Create the back buffer which will be used to create the render target view. We call the
	GetBuffer() method of the SwapChain interface:

	HRESULT GetBuffer(
	[in]       UINT Buffer,	//Since we set swapChainDesc.SwapEffect to DXGI_SWAP_EFFECT_DISCARD, we only have access to the first buffer, so we set to 0.
	[in]       REFIID riid,	//reference ID to the type of interface to change the back buffer. We use a 2d texture (ID3D11Texture2D).
	[in, out]  void **ppSurface //pointer to the BackBuffer we created above, the surface we render to.
	);*/
#pragma endregion 

	ID3D11Texture2D* BackBuffer;
	hr = SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&BackBuffer);

#pragma region RenderTarget Documentation

	/*Now create our RenderTargetView, which we will send to the output merger stage of the pipeline.
	We can create our RenderTargetView by calling CreateRenderTargetView of our device interface

	HRESULT CreateRenderTargetView(
	[in]   ID3D11Resource *pResource,	//our backbuffer
	[in]   const D3D11_RENDER_TARGET_VIEW_DESC *pDesc, //pointer to the Target_View_Desc struct We set NULL to create a view that accesses all of the subresources in mipmap level 0.
	[out]  ID3D11RenderTargetView **ppRTView // This is a pointer to our ID3D11RenderTargetView interface, renderTargetView.

	);*/
#pragma endregion 

	hr = d3d11Device->CreateRenderTargetView(BackBuffer, NULL, &renderTargetView);
	BackBuffer->Release(); //Relase it when we dont need it anymore

#pragma region RenderTargetSet Documentation

 /*And the last thing we do while initializing, is bind the render target view to the output merger
 stage of the pipeline. This function will also bind our depth/stencil buffer as well, but we have
 not created one yet, so we set that parameter to NULL.

void OMSetRenderTargets(
[in]  UINT NumViews, //Number of render targets to bind. We only have one
[in]  ID3D11RenderTargetView *const **ppRenderTargetViews, //Array of render target views to bind
 [in]  ID3D11DepthStencilView *pDepthStencilView //pointer to depth stencil buffer. We do not have one yet so set to NULL
 );*/
#pragma endregion 

	d3d11DevCon->OMSetRenderTargets(1, &renderTargetView, NULL);

	return true;
}

void ReleaseObjects()
{
	//Release the COM objects we created not doing this will cause memory leaks
	SwapChain->Release();
	d3d11Device->Release();
	d3d11DevCon->Release();
	renderTargetView->Release();
	triangleVertBuffer->Release();
	VS->Release();
	PS->Release();
	VS_Buffer->Release();
	PS_Buffer->Release();
	vertLayout->Release();
}

/*The InitScene() function will be used to initialize our scene. In a video game, you will probably have
many different scenes, so you will probably want to rename them from InitScene(). We will place our
objects, load our models, textures, sounds, all that must be done to start off that specific scene.
*/
bool InitScene()
{
	//Compile shaders from shader file

	hr = D3DCompileFromFile(L"Effects.fx", nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "VS", "vs_5_0", D3DCOMPILE_DEBUG, 0, &VS_Buffer, &Errors);
	hr = D3DCompileFromFile(L"Effects.fx", nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "PS", "ps_5_0", D3DCOMPILE_DEBUG, 0, &PS_Buffer, &Errors);
	
	if (Errors)
	{
		OutputDebugStringA(reinterpret_cast<const char*> (Errors->GetBufferPointer()));
	}

#pragma region Create Shaders Documentation
	/**
	Create the shaders; the struct is as follows:
	HRESULT CreateVertexShader(
	[in]		const void *pShaderByteCode,
	[in]		SIZE_T ByteCodeLength,
	[in]		ID3D11ClassLinkage *pClassLinkage,
	[in, out]	ID3D11VertexShader **ppVertexShader) = 0;
	);

	HRESULT CreatePixelShader(
	[in]		const void *pShaderByteCode,
	[in]		SIZE_T ByteCodeLength,
	[in]		ID3D11ClassLinkage *pClassLinkage,
	[in, out]	ID3D11PixelShader **ppPixelShader) = 0;
	);
	@Param pShaderByteCode:		This is a pointer to the start of the shaders buffer
	@Param ByteCodeLength:		This is the size of the buffer
	@Param pClassLinkage:		a pointer to a class linkage interface. Set this to NULL
	@Param ppVertexShader:		This is our returned vertex shader
	@Param ppPixelShader:		This is our returned pixel shader
	**/
#pragma endregion 

	hr = d3d11Device->CreateVertexShader(VS_Buffer->GetBufferPointer(), VS_Buffer->GetBufferSize(), NULL, &VS);
	hr = d3d11Device->CreatePixelShader(PS_Buffer->GetBufferPointer(), PS_Buffer->GetBufferSize(),NULL, &PS);
	
#pragma region Setting Shader Documentation

	/**
	Now that the shaders are created, we need to set them as the current pipeline shaders. We can do this 
	by calling ID3D11DeviceContext::VSSetShader() if we want to set the vertex shader, and 
	ID3D11DeviceContext::PSSetShader if we want to set the pixel shader.

	Most of the time an application will use different sets of shaders for different sets of geometry
	for example, later we will be using a seperate pixel shader to draw our skybox. Becaue of this, shaders
	will be set at runtime instead of only in the scene set up function. DIRECT3D IS A STATE MACHINE, where
	it will keep the current state and settings until it is changed later, don't expect D3D to set shaders
	back to a default after they are set in code, you need to always set the right shaders before you render
	stuff. That goes for render states and other things too. 

	void VSSetShader(
	[in] ID3D11VertexShader *pVertexShader,
	[in] (NumClassInstances) ID3D11ClassInstance *const *ppClassInstances,
	[in] UINT NumClassInstances);

	voidPSSetShader(
	[in] ID3D11PixelShader *pPixelShader,
	[in] (NumClassInstances) ID3D11ClassInstance *const *ppClassInstances,
	[in] UINT NumClassInstances);

	@Param pVertexShader:		Our VertexShader
	@Param pPixelShader:		Our PixelShader
	@Param ppClassInstances:	Only used if our shader uses an interface. Set to NULL.	
	@Param NumClassInstances:	# of class-instances in the array from ppClassInstances. Set to 0, we have 0.	 
	**/
#pragma endregion 

	d3d11DevCon->VSSetShader(VS, 0, 0);
	d3d11DevCon->PSSetShader(PS, 0, 0);

#pragma region Creating Vertex Buffer Documentation

/**To start creating the vertex buffer, we create an array of vertices using a Vertex Structure.
After we have an array of vertices, describe our vertex buffer by filling out a D3D11_BUFFER_DESC struct
and call ZeroMemory() t make sure its empty. The D3D11_BUFFE_DESC looks as follows:

typedef struct D311_BUFFER_DESC
{
	UINT			ByteWidth;
	D3D11_USAGE		Usage;
	UINT			BindFlags;
	UINT			CPUAcessFlags;
	UINT			MiscFlags;
	UINT			StructureByteStride;
	
}D3D11_BUFFER_DESC;

@Param ByteWidth :	The size in bytes of our buffer
@Param Usage	 :	A D3D11_USAGE type describing how our buffer will be read from and written to.
@Param BindFlags :	Specify D3D11_BIND_VERTEX_BUFFER since this is a vertex buffer.
@Param CPUAcessFlags : This says how our buffer will be used by the cpu
@Param MiscFlags :	Extra Flags we will not use, set to NULL.
@Param StructureByteStride : Not used here, set to NULL.

After that is set we can finally create the buffer using the buffer description and buffer data we jus created
To create the buffer, all we have to do is call ID3D11DEVICE::CreateBuffer() the function looks like this:

HRESULT CreateBuffer(
[in] const D3D11_BUFFER_DESC *pDesc,
[in] const D3D11_SUBRESOURCE_DATA *pInitialData,
[in] ID3D11Buffer **ppBuffer
);

@Param pDesc		: Pointer to buffer description
@Param pInitialData	: Pointer to a subresource data struct containing the data we want to put here. 
@Param ppBuffer		: The returned ID3D11Buffer **ppBuffer
**/


#pragma endregion 

	Vertex v[] =
	{
		Vertex(0.0f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f),
		Vertex(0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f),
		Vertex(-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f),
	};

	D3D11_BUFFER_DESC vertexBufferDesc;
	ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));

	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(Vertex) * 3;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA vertexBufferData;

	ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));
	vertexBufferData.pSysMem = v;
	hr = d3d11Device->CreateBuffer(&vertexBufferDesc, &vertexBufferData, &triangleVertBuffer);

#pragma region Setting VertexBuffer Documentation
	/**
	Now that we have a vertexBuffer, we need to bind it to the IA. We can do this by calling the function
	ID3D11DeviceContext::IASetVertexBuffers function.

	void IASetVertexBuffers(
	[in] UINT StartSlot,
	[in] UINT NumBuffers,
	[in] ID3D11Buffer *const *ppVertexBuffers,
	[in] const UINT *pStrides,
	[in] const UINT *pOffsets
	);

	@Param StartSlot	   :	The input slot we can bind to. set to 0 here.
	@Param NumBuffers	   :	The number of buffers we are binding. We are only binding 1.
	@Param ppVertexBuffers :	This is a pointer to our actual vertex buffer
	@Param pStrides		   :	The size of each vertex
	@Param pOffSets		   :	This is an offset in bytes from the beginning of the buffer of where to start
	**/
#pragma endregion 

	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	d3d11DevCon->IASetVertexBuffers(0, 1, &triangleVertBuffer, &stride, &offset);

#pragma region Create Input (Vertex) Layout Documentation
	/**
	 create the input layout. We can do this with the function ID3D11Device::CreateInputLayout():

	 HRESULT CreateInputLayout(
	[in] const D3D11_INPUT_ELEMENT_DESC *pInputElementDescs,
	[in] UINT NumElements,
	[in] const void *pShaderBytecodeWithInputsSignature,
	[in] SIZE_T ByteCodeLength,
	[out] ID3D11InputLayout	**ppInputLayout
	);

	@Param pInputElementDescs	: array of D3D11_INPUT_ELEMENT_DESC elements that contain our vertex layout.
	@Param NumElements			: The number of elements in out Vertex Layout.
	@Param pShaderBytecodeWithInputsSignature : Pointer to the start of our vertex Shader.
	@Param ByteCodeLength		: The size of our vertex shader

	@Returns ppInputLayout		: The returned pointer to our Input (Vertex) Layout

	**/

#pragma endregion

	hr = d3d11Device->CreateInputLayout(layout, numElements, VS_Buffer->GetBufferPointer(),
		VS_Buffer->GetBufferSize(), &vertLayout);

#pragma region Setting the Input (Vertex) Layout
	/**
	We have created the Vertex Layout, The next thing to do is bind it to the IA as the active input
	(vertex) layout. We can do this by calling the function ID3D11DeviceContext::IASetInputLayout

	void STDMETHODCALLTYPE IASetInputLayout(
	[in] ID3D11InputLayout *pInputLayout
	);

	@Param pInputayout	: our created InputLayout
	**/
#pragma endregion

	d3d11DevCon->IASetInputLayout(vertLayout);

#pragma region Setting the primitive Topology
	/**
	This is where we tell the IA what primitive types we are sending it. We can set the primitive topology
	by calling the function ID3D11DeviceContext::IASetPrimitiveTopology(). The only Param is is the 
	D3D11_PRIMITIVE_TOPOLOGY enumerated type.

	PointList :
		D3D10_PRIMITIVE_TOPOLOGY_POINTLIST. by using this topology every vertex will be drawn as an
		individual point.

	Line Strip :
		D3D10_PRIMITIVE_TOPOLOGY_LINESTRIP. All vertices will be part of a line (connect the dots)

	Line List  :
		D3D10_PRIMITIVE_TOPOLOGY_LINELIST. Every two vertices will create a line. The difference between this
		and Line Strip is that in a Line Strip, all vertices will be connected to create one continuous line.

	Triangle Strip :
		D3D10_PRIMITIVE_TOPLOLOGY_TRINAGLESTRIP. Here we create each triangles, easch triangle shares it's
		vertices with the adjacent triangles. All triangles will be connected.

	Triangle List :
		D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELST. This says that every 3 vertices make a triangle, so that no all
		triangles have to be connected. It is slower than a triangle strip because more verts will be used,
		unlike a triangle strip, where you can have	2 triangles made with 4 vertices, 6 are required for a 
		Triangle List.

	Primitives With Adjacency :
		ex. D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ. These are only used for the geometry shader. 

	**/
#pragma endregion

	d3d11DevCon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

#pragma region Creating the Viewport
	/**
	The viewport will tell the RS stage of the pipeline	what to draw. We can create a viewport using the
	D3D11_VIEWPORT structure. The viwport creates a square in pixels, which the rasterizer uses to find
	where to display our geometry on the client area of the window. The viewport will also be used to 
	Introduce the depth buffer.
	
	We can set the min and max depth values, usually between 0 and 1. Then the OM
	will decide which pixel "fragments" to display based on their depth values. We want the viewport to cover
	our entire window client area, so we set the top left of the box to 0, 0, and the bottom right to the 
	Width and Height, which are in Pixels.
	**/
#pragma endregion

	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = Width;
	viewport.Height = Height;	

#pragma region Setting the ViewPort
	/**
	After creating the viewport, we need to Bind it to the RS stage of the pipeline using the function
	ID3D11DeviceContext::RSSetViewports(). 

	@Param NumViewports : The number of viewports to Bind.
	@Param pViewports	: Pointer to an array of viewports. This is where you could have multiple windows,
						  like for player 1 and player 2
	**/
#pragma endregion

	d3d11DevCon->RSSetViewports(1, &viewport);

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
	/*red += colormodr * 0.00005f;
	green += colormodg * 0.00002f;
	blue += colormodb * 0.00001f;

	if (red >= 1.0f || red <= 0.0f)
		colormodr *= -1;
	if (green >= 1.0f || green <= 0.0f)
		colormodg *= -1;
	if (blue >= 1.0f || blue <= 0.0f)
		colormodb *= -1;*/
}

/*This is were we render our scene do not update here, only draw*/
void DrawScene()
{

	//Clear our backbuffer to the updated color
	//DirectX::XMFLOAT4 bgColor(red, green, blue, 1.0f);
	d3d11DevCon->ClearRenderTargetView(renderTargetView, bgColor);

	d3d11DevCon->Draw(3, 0);//3 vertices with no offset.

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
			
			TranslateMessage(&msg);//If our message was a windows message, we translate, then dispatch.
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