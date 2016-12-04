#ifndef GRUB_MARCHINGCHUNKMESHER
#define GRUB_MARCHINGCHUNKMESHER
#include "ChunkMesher.h"
#include <vector>
#include "SimpleVertex.h"

class MarchingChunkMesher : public ChunkMesher
{
public:
	void MeshChunk(ChunkData* data, Primitive p) override;
};
#endif