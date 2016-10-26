#include <stdio.h>
#include "GrubTest.h"

Grub* NewGame;

int main(int argc, char** argv) {
	Clock::init();
	NewGame = new GrubTest();
	Grub::instance = NewGame;
	OpenGLWindow* window = NewGame->window;
	window->MakeWindow(argc, argv);
	window->SetUpdate(Grub::Update);
	window->SetDisplay(Grub::Display);
	while (true)
		;
	getchar();
	return(0);
}