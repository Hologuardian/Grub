#ifndef GRUB_GRUB_H
#define GRUB_GRUB_H

#include <stdio.h>
#include "Clock.h"
#include "Logger.h"
#include "OpenGLWindow.h"

class Grub
{
public:
	static Grub* instance;
public:
	Grub();
	~Grub();
	OpenGLWindow* window;
	virtual void Update(float delta) = 0;
	virtual void Render() = 0;
	virtual void Initialize() = 0;
public:
	static void Display();
	static void Update();
private:
};

#endif