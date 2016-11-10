#ifndef GRUB_CHUNK
#define GRUB_CHUN
#include "Logger.h"
#include "Constants.h"
#include "Resource.h"
#include "ChunkRenderer.h"

class Chunk : public Resource<Chunk>
{
public:
	int ChunkX;
	int ChunkZ;
	float*** ChunkData;
	ChunkRenderer* chunkRender;

public:
	Chunk() = delete;
	Chunk(int x, int z, ChunkRenderer* renderer);
	Chunk Load(std::string File) override;
	void Render(AbstractWindow* window);
	void Buffer(Grubuint program);
	~Chunk();
};

#endif