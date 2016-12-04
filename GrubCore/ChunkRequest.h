#ifndef GRUB_CHUNKREQUEST
#define GRUB_CHUNKREQUEST
#include "Chunk.h"

class ChunkRequest
{
public:
	enum RequestType
	{
		Generation,
		Deletion,
		Save,
		Load
	};
public:
	ChunkRequest(RequestType chunkRequestType, int x, int z, Chunk* chunk)
	{
		ChunkRequest::chunkRequestType = chunkRequestType;
		ChunkRequest::ChunkX = x;
		ChunkRequest::ChunkZ = z;
		ChunkRequest::chunk = chunk;
	}

	RequestType chunkRequestType;
	int ChunkX;
	int ChunkZ;
	Chunk* chunk;
};
#endif