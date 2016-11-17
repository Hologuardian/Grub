#ifndef GRUB_CHUNKGENERATOR
#define GRUB_CHUNKGENERATOR
#include<stdarg.h>

template <typename T, typename S>
class ChunkGenerator
{
public:
	virtual T genreateChunkData(int numArgs, ...) = 0;
};
#endif