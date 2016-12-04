#ifndef GRUB_CUBICCHUNKMESHER
#define GRUB_CUBICCHUNKMESHER
#include "ChunkMesher.h"
#include <vector>

class CubicChunkMesher : public ChunkMesher
{
public:
	void MeshChunk(ChunkData* data, Primitive p) override;
};
#endif