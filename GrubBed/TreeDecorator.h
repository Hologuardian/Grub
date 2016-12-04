#ifndef TREEDECORATOR
#define TREEDECORATOR
#include "ChunkDecorator.h"

class TreeDecorator : public ChunkDecorator
{
	void decorateChunkData(ChunkData* data, FastNoise noise);
};
#endif