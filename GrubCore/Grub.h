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
	/**
	Takes default main
	*/
	Grub(int argc, char** argv);
	~Grub();
	Window* window;
	/**
	Abstract update function, to be overridden.
	*/
	virtual void Update(float delta) = 0;
	/**
	Abstract render function, to be overridden.
	*/
	virtual void Render() = 0;
	/**
	Abstract initialize function, do any startup code in here.
	*/
	virtual void Initialize() = 0;
public:
	/**
	Static display that will call the Render function of the singleton instance.
	*/
	static void Display();
	/**
	Static update that will call the Update function of the singleton instance, as well as calculate the time since the last update.
	*/
	static void Update();
private:
};

#endif