#ifndef GRUB_CHUNKRENDERER
#define GRUB_CHUNKRENDERER
#include "Constants.h"
#include "Window.h"
#include <vector>
#include "GraphicPrimitive.h"

class ChunkRenderer
{
public:
	/**
	Draws the chunk to the specified window.
	*/
	virtual void Render(Window* window) = 0;
	/**
	Registers all of the data required sent from the chunk file, this is put into the buffer to be drawn.
	*/
	virtual void RegisterPrimitives(const std::vector<Vector3>* const points, const std::vector<Vector3>* const Colors, Primitive p) = 0;
	virtual ~ChunkRenderer() {};

	Primitive prim;
};

#endif