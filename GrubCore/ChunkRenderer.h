#ifndef GRUB_CHUNKRENDERER
#define GRUB_CHUNKRENDERER
#include "Constants.h"
#include "AbstractWindow.h"

class ChunkRenderer
{
public:
	virtual void Render(AbstractWindow* window) = 0;
	virtual void RegisterQuads(Vector3 points[], Vector3 Colors[], Grubuint program) = 0;
};

#endif