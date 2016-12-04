#ifndef GRUB_CHUNKGENERATOR
#define GRUB_CHUNKGENERATOR
#include<cstdarg>
#include "ChunkData.h"
#include "Constants.h"
#include "FastNoise.h"

class ChunkGenerator
{
public:
	virtual void generateChunkData(ChunkData* data, FastNoise noise) = 0;
};
#endif