#ifndef GRUB_CHUNKREQUEST
#define GRUB_CHUNKREQUEST
#include "Chunk.h"
#include "ChunkUpdate.h"

class ChunkRequest
{
public:
	enum RequestType
	{
		Generation,
		Deletion,
		Update,
		Save,
		Load
	};
public:
	ChunkRequest(RequestType chunkRequestType, Chunk* chunk)
	{
		ChunkRequest::chunkRequestType = chunkRequestType;
		ChunkRequest::ChunkX = 0;
		ChunkRequest::ChunkZ = 0;
		ChunkRequest::chunk = chunk;
	}
	ChunkRequest(RequestType chunkRequestType, ChunkUpdate* chunkUpdate, int ChunkX, int ChunkZ)
	{
		ChunkRequest::chunkRequestType = chunkRequestType;
		ChunkRequest::ChunkX = ChunkX;
		ChunkRequest::ChunkZ = ChunkZ;
		ChunkRequest::update = chunkUpdate;
	}

	ChunkRequest(RequestType chunkRequestType, int ChunkX, int ChunkZ)
	{
		ChunkRequest::chunkRequestType = chunkRequestType;
		ChunkRequest::ChunkX = ChunkX;
		ChunkRequest::ChunkZ = ChunkZ;
		ChunkRequest::chunk = chunk;
	}

	RequestType chunkRequestType;
	int ChunkX;
	int ChunkZ;
	Chunk* chunk;
	ChunkUpdate* update;
};
#endif