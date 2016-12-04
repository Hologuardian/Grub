#ifndef GRUB_CHUNKMESHER
#define GRUB_CHUNKMESHER
#include "GraphicPrimitive.h"
#include "ChunkData.h"

class ChunkMesher
{
public:
	virtual void MeshChunk(ChunkData* data, Primitive p) = 0;
};
#endif