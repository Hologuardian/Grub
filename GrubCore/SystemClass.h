#ifndef _SYSTEMCLASS_H_
#define _SYSTEMCLASS_H_

/*Speeds up build process, reduces size of win32 header by excluding less used API's*/
#define WIN32_MEAN_AND_LEAN

#include <windows.h>

class SystemClass
{
public:
	SystemClass();
	SystemClass(const SystemClass&); // Copy constructors
	~SystemClass();

	//define functions
	bool Initialize();
	void ShutDown();
	void Run();

	//handles windows system messages when the app is running
	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

private:
	bool Frame();
	void InitiaizeWindows(int&, int&);
	void ShutDownWindows();

private:
	LPCWSTR applicationName; //Long Pointer to constant wide string, the string is stored in a 2byte character array
	HINSTANCE hInstance; 
	HWND hwnd;

	//class object pointers
	
};

/*The WndProc function and ApplicationHandle pointer are also included in this class file so we can 
re-direct the windows system messaging into our MessageHandler functon inside the SystemClass*/

/////////////////////////
// FUNCTION PROTOTYPES //
/////////////////////////
static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

///////////
//Globals//
///////////
static SystemClass* applicationHandle = 0;

#endif
