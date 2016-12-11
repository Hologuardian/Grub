#ifndef GRUB_CHUNK
#define GRUB_CHUNK
#include "Logger.h"
#include "Constants.h"
#include "Resource.h"
#include "ChunkRenderer.h"
#include "ChunkGenerator.h"
#include "ChunkDecorator.h"
#include <vector>
#include "FastNoise.h"
#include "GraphicPrimitive.h"
#include "MarchingChunkMesher.h"
#include "CubicChunkMesher.h"
#include "ChunkData.h"
#include "GameObject.h"

class Chunk : public Resource<Chunk>
{
public:
	ChunkData* data;
	ChunkRenderer* chunkRender;
	ChunkGenerator* chunkGenerator;
	std::vector<ChunkDecorator*>* chunkDecorators;
	std::vector<GameObject*>* objects;
	static FastNoise noise;
	const Primitive primitiveType = Primitive::TRI;
	MarchingChunkMesher mesher;
	//const Primitive primitiveType = Primitive::QUAD;
	//CubicChunkMesher mesher;
public:
	Chunk() = delete;
	Chunk(int x, int z, ChunkRenderer* renderer, ChunkGenerator* generator, std::vector<ChunkDecorator*>* decorators);
	Chunk Load(std::string File) override;
	void Render(Window* window);
	void Generate();
	void Initialize();
	void Buffer();
	~Chunk();
};

#endif