#include <stdio.h>
#include "GrubTest.h"

Grub* NewGame;

int main(int argc, char** argv) {
	Clock::init();
	NewGame = new GrubTest(argc, argv);
	Grub::instance = NewGame;
	GLWindow* window = NewGame->window;
	NewGame->Initialize();
	while (true)
		;
	getchar();
	return(0);
}