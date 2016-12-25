#include "Constants.h"
#ifdef GRUB_DX11
#ifndef _SYSTEMCLASS_H_
#define _SYSTEMCLASS_H_

/*define WIN32_LEAN_AND_MEAN. We do this to speed up the build process, it reduces the size of the Win32 header
files by excluding some of the less used APIs.*/
#define WIN32_LEAN_AND_MEAN

/*Windows.h is included so that we can call the functions to create/destroy windows
and be able to use the other useful win32 functions.*/
#include <windows.h>


//////////////////
//Class Includes//
//////////////////
#include "InputClass.h"
#include "GraphicsClass.h"


class SystemClass
{
public:
	SystemClass();
	SystemClass(const SystemClass&); // look more into copy constructors, don't fully understand
	~SystemClass();

	//define functions
	bool Initialize();
	void ShutDown();
	void Run();

	//handles windows system messages when the app is running
	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

private:
	bool Frame();
	void InitializeWindows(int&, int&);
	void ShutDownWindows();

	//std::string *m_applicationName = new std::string(); REPLACE THIS WITH LPCWSTR IF NECESSARY
private: //DELETE IF NOT NEDED
	LPCWSTR applicationName; //LONG POINTER TO CONSTANT WIDE STRING. string is stored in a 2byte charachter.
	HINSTANCE hinstance;
	HWND hwnd;

	//class object pointers
	InputClass* Input;
	GraphicsClass* Graphics;
};


/*The WndProc function and ApplicationHandle pointer are also included in this class file
so we can re-direct the windows system messaging into our MessageHandler function inside the system class.*/

/////////////////////////
// FUNCTION PROTOTYPES //
/////////////////////////
static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

/////////////
// GLOBALS //
/////////////
static SystemClass* ApplicationHandle = 0;

#endif
#endif