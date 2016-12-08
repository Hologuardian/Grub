#ifndef TREEDECORATOR
#define TREEDECORATOR
#include "ChunkDecorator.h"

class PencilTreeDecorator : public ChunkDecorator
{
	void decorateChunkData(ChunkData* data, FastNoise noise);
};
#endif