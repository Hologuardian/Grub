#include "SystemClass.h"

SystemClass::SystemClass()
{
	/*Initialize the object pointers to null. This is important because if the initiaization of the objects
	fail, then the ShutDown function further on will attempt to clean up those objects. If the objects
	are not null, then it assumes they were valid created objects and that they need to be cleaned up*/

}

SystemClass::SystemClass(const SystemClass& other)
{

}

/*all object destruction called in ShutDown(), this is because I can't trust this to always be called when
needed. Certain Windows Functions like ExitThread() are known for not calling your class destructors resulting 
in memory leaks.*/
SystemClass::~SystemClass()
{

}

/*Does all the setup for the application. It first calls InitializeWindows which will create the Window 
for our application to use. It also creates and Initializes both the input and graphics Objects that the 
application will use for handling user input and rendering graphics to the screen*/

bool::SystemClass::Initialize()
{
	int screenWidth;
	int screenHeight;
	bool result;

	//Initialize width and height to 0 before sending the variables to the function
	screenWidth = 0;
	screenHeight = 0;

	//Initialize the Windows API
	InitiaizeWindows(screenWidth, screenHeight);

	return true;
}

/*Does the cleanup. It shuts down and releases everything associated with the graphics and input object.
As well as shut down the window and cleans up the handles associated with it.*/

void SystemClass::ShutDown()
{
	ShutDownWindows();

	return;
}

/*The application will loop and do all the application processing until we decide to quit.
The application processing is done in the Frame funtion which is called each loop.
This is an important concept to understand as now the rest of our application must be written with this
in mind. The pseudo code look lie the following:

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

	//Loop until there is a quit message from the window user.
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

/*This is where all the processing will be done.*/
bool SystemClass::Frame()
{
	bool result;

	result = Frame();

	if (!result)
	{
		return false;
	}

	return true; 
}

/*Directs the windows system messages, read if a key is pressed or released and pass the info
to the input object, anything else will be passed back to the default message handler*/
LRESULT CALLBACK SystemClass::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	switch (umsg)
	{
		//Check if key is pressed ***KEYBOARD SUPPORT ONLY FIX LATER***
		case WM_KEYDOWN:
		{

		}

	}
}