#include "SystemClass.h"


SystemClass::SystemClass()
{
	/*initialize the object pointers to null. This is important because if the initialization of these objects fail
	then the Shutdown function further on will attempt to clean up those objects.
	If the objects are not null then it assumes they were valid created objects and that they need to be cleaned up.*/

	Input = 0;
	Graphics = 0;
}

// empty copy constructor do i even need?
SystemClass::SystemClass(const SystemClass& other)
{
}

/*all object destruction called in Shutdown(), this is because I cn't trust this to always be called when needed
Certain windows functions like ExitThread() are known for not calling your class destructors resulting in memory
leaks.*/
SystemClass::~SystemClass()
{
}

/* does all the setup for the application. It first calls InitializeWindows which will create the window
for our application to use. It also creates and initializes both the input and graphics objects
that the application will use for handling user input and rendering graphics to the screen.*/

bool::SystemClass::Initialize()
{

	//do these have to be here? try moving to header file later.
	int screenWidth;
	int screenHeight;
	bool result;

	//initialize width and height to 0, before sending the variables into the function.

	screenWidth = 0;
	screenHeight = 0;

	//initialise the windows api
	InitializeWindows(screenWidth, screenHeight);

	//create an input object, this will be used to handle reading keyboard events from the 
	Input = new InputClass;
	if (!Input)
	{
		return false;
	}

	//Initialize the input object
	Input->Initialize();

	//create graphics object, this will handle rendering graphics for the application
	Graphics = new GraphicsClass;
	if (!Graphics)
	{
		return false;
	}

	//Initialize the graphics object
	result = Graphics->Initialize(screenWidth, screenHeight, hwnd);

	if (!result)
	{
		return false;
	}

	return true;
}

/*does the clean up. It shuts down and releases everything associated with the graphics and input object.
As well it also shuts down the window and cleans up the handles associated with it.*/

void SystemClass::ShutDown()
{
	//Release Graphics object
	if (Graphics)
	{
		Graphics->ShutDown();
		delete Graphics;
		Graphics = 0;
	}

	//Release Input object
	if (Input)
	{
		delete Input;
		Input = 0;
	}

	//Shut down the window
	ShutDownWindows();

	return;
}

/*the application will loop and do all the application processing until we decide to quit.
The application processing is done in the Frame function which is called each loop.
This is an important concept to understand as now the rest of our application must be written with this in mind.
The pseudo code looks like the following:

while not done
check for windows system messages
process system messages
process application loop
check if user wanted to quit during the frame processing*/

void SystemClass::Run()
{
	MSG msg;
	bool done;
	bool result;

	//Initialize the message structure
	ZeroMemory(&msg, sizeof(MSG));

	//Loop until there is a quit message from the window or user.
	done = false;
	while (!done)
	{
		//handle the windows messages
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		//if window signals to end the application, exit out
		if (msg.message == WM_QUIT)
		{
			done = true;
		}
		else
		{
			//otherwise do the frame processing
			result = Frame();
			if (!result)
			{
				done = true;
			}
		}
	}
	return;
}

/*this is where all processing will be done. check the input objec to see if the user pressed escape and wants
to quit, if not, call the graphics object to do its fram processing which will render the graphics for that frame/
as the applicatio grows i'll be adding more code here*/
bool SystemClass::Frame() {

	bool result;

	//Check if the user pressed escape and wants to quit the application.
	if (Input->IsKeyDown(VK_ESCAPE))
	{
		return false;
	}

	//Do frame processing for graphics object
	result = Graphics->Frame();

	if (!result)
	{
		return false;
	}

	return true;
}

/*Directs th windows system messages, read if a key is pressed or released and pass the info
to the input object anything else will be passed back to the default message handler*/

LRESULT CALLBACK SystemClass::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	switch (umsg)
	{
		//Check if key is pressed **KEYBOARD ONLY ADD SUPORT LATER**
	case WM_KEYDOWN:
	{
		//If key is pressed, send it to the input object so it can record it's current state
		Input->KeyDown((unsigned int)wparam);
		return 0; //same as break
	}

	//Check if key has been reeased **KEYBOARD AGAIN**
	case WM_KEYUP:
	{
		//if a key is released, send it to the input object so t can unset the state for that key
		Input->KeyUp((unsigned int)wparam);
		return 0;
	}

	//Any other messages sent to the default message handler 
	default:
	{
		return DefWindowProc(hwnd, umsg, wparam, lparam);
	}

	}
}

/*Here the window will be built and used to render to. returns ScreenWidth and ScreenHeight back to
the calling functions so we can make use of them throughout the application. Create window using some default
settings to init a plain black window with no borders. if the global variabe FULL_SCREEN is true, it will draw
the window fullscreen, else draw a 800x600 window in the center of the screen

FULL_SCREEN global variable is at the top of the graphicsclass.h file if it ever needs modifying.*/

void SystemClass::InitializeWindows(int& screenWidth, int& screenHeight)
{
	WNDCLASSEX wc;
	DEVMODE dmScreenSettings;
	int posX;
	int posY;

	//Get an external pointer to this object
	ApplicationHandle = this;

	//Get the instance of this application
	hinstance = GetModuleHandle(NULL);

	//Give applcation a name
	applicationName = L"Engine"; //L prefix is needed because of LPCWSTR

								   //Setup the windows class with default settings
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC; //allows window client to redraw properly if screen size changes
	wc.lpfnWndProc = WndProc; //pointer to windows procedure
	wc.cbClsExtra = 0;// The number of extra bytes to allocate following the window-class structure.
	wc.cbWndExtra = 0; // The number of extra bytes to allocate following the window instance. 
	wc.hInstance = hinstance; //A handle to the instance that contains the window procedure for the class.

								//A handle to the class icon. This member must be a handle to an icon resource. 
								//If this member is NULL, the system provides a default icon. (24x24, 32x32 or 48x48)
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);

	wc.hIconSm = wc.hIcon; // handle to small icon (16x16) 

						   /* A handle to the class cursor. This member must be a handle to a cursor resource.
						   If this member is NULL, an application must explicitly set the cursor shape whenever the mouse moves
						   into the application's window.*/
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);

	// A handle to the class background brush. This member can be a handle to the brush to be used for painting the
	//background, or it can be a color value.
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);

	//Pointer to a null-terminated character string that specifies the resource name of the class menu, 
	//as the name appears in the resource file
	wc.lpszMenuName = NULL;

	wc.lpszClassName = applicationName; //A pointer to a null-terminated string/atom. MAX 256 or will fail.
	wc.cbSize = sizeof(WNDCLASSEX); // Size in bytes of this struct. MUST BE SET BEFORE CALLING GetClassInfoEX()

	RegisterClassEx(&wc); //Register the window class for use in calls to CreateWindow or CreateWindowE functions.

						  //Determine the resolution of clients monitor.
	screenWidth = GetSystemMetrics(SM_CXSCREEN); // both measurements are in pixles
	screenHeight = GetSystemMetrics(SM_CYSCREEN);

	//Setup screen settings depending if running fullscreen or windowed
	if (FULL_SCREEN)
	{
		//If fullscreen set the screen to maximun size of users monitor and in 32bits.
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (unsigned long)screenWidth; //same as unsigned int making sure its positive
		dmScreenSettings.dmPelsHeight = (unsigned long)screenHeight;
		dmScreenSettings.dmBitsPerPel = 32; //32 bits is default for color depth max supported is 48bits(281.5 trillion color combos)
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT; // WTF is this?????

																				  //Change settings to fullscreen
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		//Set position of window to top left corner
		posX = 0;
		posY = 0;
	}
	else {
		//if windowed set resolution to 800X600
		screenWidth = 800;
		screenHeight = 600;

		//Place window in the middle of the screen
		//Use System metrics call to calculate size of users screen and divide by 2.
		posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;
	}

	//create window with the screen settings and get handle to it
	hwnd = CreateWindowEx(WS_EX_APPWINDOW, applicationName, applicationName,
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP, posX, posY, screenWidth, screenHeight, NULL, NULL,
		hinstance, NULL);

	//Bring window up on main screen and set it as the focus
	ShowWindow(hwnd, SW_SHOW);
	SetForegroundWindow(hwnd);
	SetFocus(hwnd);

	//Hide The Mouse Cursor
	ShowCursor(false);

	return;
}

//returns the screen settings back to normal and releases the window and handles associate with it
void::SystemClass::ShutDownWindows()
{
	//Show Mouse Cursor
	ShowCursor(true);

	//Fix the display settings if leaving fullscreen
	if (FULL_SCREEN)
	{
		ChangeDisplaySettings(NULL, 0);
	}

	//Remove the window
	DestroyWindow(hwnd);
	hwnd = NULL;

	//Remove application instance
	UnregisterClass(applicationName, hinstance);
	hinstance = NULL;

	//Release the pointer to the class
	ApplicationHandle = NULL;

	return;
}

/*This is where the window sends it's messages. We tell windows the name of it when we
initialize the window class with wc.lpfnWndProc = WndProc in the InitializeWindows function above. I included it
in this class file since we tie it directly into the system class by having it send all the messages to the
MessageHandler function defined inside SystemClass. This allows us to hook the messaging functionality straight
into our class and keep the code clean*/

LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
	switch (umessage)
	{
		//check to see if the window is beeing destroyed
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}

		//Check to see if the window is being closed
		case WM_CLOSE:
		{
			PostQuitMessage(0);
			return 0;
		}

		//All other messages to be passed to message handler in SystemClass
		default:
		{
			return ApplicationHandle->MessageHandler(hwnd, umessage, wparam, lparam);
		}

	}
}