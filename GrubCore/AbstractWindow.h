#ifndef GRUB_ABSTRACT_WINDOW_H
#define GRUB_ABSTRACT_WINDOW_H
#include "Model.h"

class AbstractWindow
{
public:
	enum PrimativeType {
		NONE,
		BYTE,
		CHAR,
		INT,
		FLOAT,
		BOOLEAN
	};
	virtual ~AbstractWindow();
	virtual void renderPrimitive(PrimativeType prim) = 0;
	virtual void renderModel(Model* model) = 0;
	virtual void startRender() = 0;
	virtual void endRender() = 0;
};

#endif