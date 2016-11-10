#ifndef GRUB_ABSTRACT_WINDOW_H
#define GRUB_ABSTRACT_WINDOW_H
#include "Model.h"
#include "Constants.h"
#include "Camera.h"

class AbstractWindow
{
public:
	enum PrimativeType {
		NONE,
		QUAD,
		TRI,
		TRIFAN,
		POLY
	};
	Grubuint program;
	virtual ~AbstractWindow();
	virtual void renderPrimitive(PrimativeType prim, Grubuint VAO, int start, int length) = 0;
	virtual void renderModel(Model* model) = 0;
	virtual void startRender() = 0;
	virtual void endRender() = 0;
	virtual void begin() = 0;
	virtual Camera* GetCamera() = 0;
};

#endif