#include <stdio.h>
#include "Constants.h"
#include "GrubTest.h"

#ifdef GRUB_DX11

#include "Direct3D.h"

#endif

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

LPCTSTR WndClassName = "Grub";
HWND hwnd = NULL;

//define width and height of window
const int Width = 800;
const int Height = 600;

//Class object
Direct3D* D3D;

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

	if (!D3D->InitializeDirect3D11App(hInstance)) //Initialize Direct3D
	{
		MessageBox(0, "Direct3D Initialization - Failed ",
			"Error", MB_OK);
		return 0;
	}

	if (!D3D->InitScene()) //Initialize our Scene
	{
		MessageBox(0, "Scene Initialization - Failed ",
			"Error", MB_OK);
		return 0;
	}

	messageloop();

	D3D->ReleaseObjects();
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

int messageloop()
{
	
	MSG msg; //make instance to MSG structure
	ZeroMemory(&msg, sizeof(MSG)); //clears the struct and sets it to null

	while (true) //while thre's a message...
	{
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