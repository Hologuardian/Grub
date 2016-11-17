#ifndef GRUB_CHUNKRENDERER
#define GRUB_CHUNKRENDERER
#include "Constants.h"
#include "Window.h"
#include<vector>

class ChunkRenderer
{
public:
	virtual void Render(Window* window) = 0;
	virtual void RegisterQuads(const std::vector<Vector3>* const points, const std::vector<Vector3>* const Colors) = 0;
	virtual ~ChunkRenderer() {};
};

#endif