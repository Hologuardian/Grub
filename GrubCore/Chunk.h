#ifndef GRUB_CHUNK
#define GRUB_CHUN
#include "Logger.h"
#include "Constants.h"
#include "Resource.h"
#include "ChunkRenderer.h"
#include <vector>
#include "FastNoise/FastNoise.h"

class Chunk : public Resource<Chunk>
{
public:
	int ChunkX;
	int ChunkZ;
	std::vector<float>* ChunkData;
	ChunkRenderer* chunkRender;
	std::vector<Vector3>* pos;
	std::vector<Vector3>* colors;
	static FastNoise noise;
public:
	Chunk() = delete;
	Chunk(int x, int z, ChunkRenderer* renderer);
	Chunk Load(std::string File) override;
	void Render(AbstractWindow* window);
	void Generate();
	void Initialize();
	void Buffer();
	~Chunk();
};

#endif