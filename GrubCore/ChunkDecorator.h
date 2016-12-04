#ifndef GRUB_CHUNKDECORATOR
#define GRUB_CHUNKDECORATOR
#include<cstdarg>
#include "ChunkData.h"
#include "Constants.h"
#include "FastNoise.h"

class ChunkDecorator
{
public:
	virtual void decorateChunkData(ChunkData* data, FastNoise noise) = 0;
};
#endif