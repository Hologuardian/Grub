#ifndef GRUB_OPEN_GL_WINDOW_H
#define GRUB_OPEN_GL_WINDOW_H

#include "Logger.h"

#include "AbstractWindow.h"
#include "opengl\include\glew.h"
#include "opengl\include\glut.h"
#include "glut\include\vgl.h"
#include "LoadShaders.h"
#include "glm\glm\glm.hpp"
#include "glm\glm\gtc\matrix_transform.hpp"

class OpenGLWindow: public AbstractWindow
{
public:
	OpenGLWindow();
	~OpenGLWindow();
	void MakeWindow(int argc, char** argv);
	void SetUpdate(void (UpdateCallBack)());
	void SetDisplay(void (Display)());
	void renderPrimitive(PrimativeType prim);
	void renderModel(Model* model);
	void testDraw(glm::vec3 pos, int c, glm::vec3 cam);
	void startRender();
	void endRender();
};

#endif