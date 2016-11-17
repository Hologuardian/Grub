#ifndef GRUB_GRUB_H
#define GRUB_GRUB_H

#include "Input.h"
#include <stdio.h>
#include "Clock.h"
#include "Logger.h"
#include "GLWindow.h"

class Grub
{
public:
	static Grub* instance;
public:
	Grub(int argc, char** argv);
	~Grub();
	GLWindow* window;
	virtual void Update(float delta) = 0;
	virtual void Render() = 0;
	virtual void Initialize() = 0;
public:
	static void Display();
	static void Update();
private:
};

#endif