#ifndef GRUB_CHUNKDATA
#define GRUB_CHUNKDATA
#include <vector>
#include "Constants.h"

class ChunkData
{
public:
	ChunkData()
	{
		values = new std::vector<unsigned int>();
		vertices = new std::vector<Vector3>();
		colors = new std::vector<Vector3>();
	}

	~ChunkData()
	{
		delete values;
		delete vertices;
		delete colors;
	}

	void DeleteBufferArrays()
	{
		delete vertices;
		vertices = nullptr;
		delete colors;
		colors = nullptr;
	}
	std::vector<unsigned int>* values;
	std::vector<Vector3>* vertices;
	std::vector<Vector3>* colors;
	int ChunkX;
	int ChunkZ;
};
#endif