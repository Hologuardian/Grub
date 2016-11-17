#ifndef GRUB_OPEN_GL_WINDOW_H
#define GRUB_OPEN_GL_WINDOW_H

#include "AbstractWindow.h"
#include "Logger.h"
#include "GLCamera.h"

#include "opengl\include\glew.h"
#include "opengl\include\glut.h"
#include "glut\include\vgl.h"
#include "LoadShaders.h"
#include "glm\glm\glm.hpp"
#include "glm\glm\gtc\matrix_transform.hpp"

class OpenGLWindow: public AbstractWindow
{
public:
	GLCamera* camera;
	OpenGLWindow();
	~OpenGLWindow();
	void MakeWindow(int argc, char** argv) override;
	void SetUpdate(void (UpdateCallBack)()) override;
	void SetDisplay(void (Display)()) override;
	void SetKeyDownInput(void(*KeyboardDown)(unsigned char key, int x, int y)) override;
	void SetKeyUpInput(void(*KeyboardUp)(unsigned char key, int x, int y)) override;
	void SetMouseClickInput(void(*Click)(int button, int state, int x, int y)) override;
	void SetMouseMoveInput(void(*Move)(int x, int y)) override;
	void SetMouseDragInput(void(*Drag)(int x, int y)) override;
	void SetSpecialKeyDownInput(void(*SpecialDown)(int key, int x, int y)) override;
	void SetSpecialKeyUpInput(void(*SpecialUp)(int key, int x, int y)) override;
public:
	void renderPrimitive(PrimativeType prim, Grubuint VAO, int start, int length);
	void renderModel(Model* model);
	void testDraw(glm::vec3 pos, int c);
	void startRender();
	void endRender();
	void begin();
	Camera* GetCamera();
};

#endif