#ifndef TESTCHUNKGENERATOR
#define TESTCHUNKGENERATOR
#include "ChunkGenerator.h"

class TestChunkGenerator : public ChunkGenerator
{
	void generateChunkData(ChunkData* data, FastNoise noise);
};
#endif