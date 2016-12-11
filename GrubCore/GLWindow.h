#include "Window.h"
#ifdef GRUB_USEOPENGL
#ifndef GRUB_OPEN_GL_WINDOW_H
#define GRUB_OPEN_GL_WINDOW_H

#include "Logger.h"
#include "GLCamera.h"

#include "opengl\include\glew.h"
#include "opengl\include\glut.h"
#include "glut\include\vgl.h"
#include "LoadShaders.h"
#include "glm\glm\glm.hpp"
#include "glm\glm\gtc\matrix_transform.hpp"

class GLWindow: public Window
{
public:
	GLCamera* camera;
	GLWindow();
	~GLWindow();
	void MakeWindow(int argc, char** argv) override;
	
	//Main Loop functions
	void SetUpdate(void (UpdateCallBack)()) override;
	void SetDisplay(void (Display)()) override;
	//Starts up the main loops
	void begin();

	//Input functions
	void SetKeyDownInput(void(*KeyboardDown)(unsigned char key, int x, int y)) override;
	void SetKeyUpInput(void(*KeyboardUp)(unsigned char key, int x, int y)) override;
	void SetMouseClickInput(void(*Click)(int button, int state, int x, int y)) override;
	void SetMouseMoveInput(void(*Move)(int x, int y)) override;
	void SetMouseDragInput(void(*Drag)(int x, int y)) override;
	void SetSpecialKeyDownInput(void(*SpecialDown)(int key, int x, int y)) override;
	void SetSpecialKeyUpInput(void(*SpecialUp)(int key, int x, int y)) override;
public:
	void renderPrimitive(Primitive prim, Grubuint VAO, int start, int length);
	void renderModel(Model* model);
	void testDraw(glm::vec3 pos, int c);
	//Clears specific GL bits
	void startRender();
	//Flushes the GLbuffer to draw to screen
	void endRender();
	Camera* GetCamera();
};

#endif
#endif