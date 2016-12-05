#include "Chunk.h"

FastNoise Chunk::noise;

Chunk::Chunk(int x, int z, ChunkRenderer* renderer, ChunkGenerator* generator, std::vector<ChunkDecorator*>* decorators)
{
	data = new ChunkData();
	data->ChunkX = x;
	data->ChunkZ = z;
	chunkRender = renderer;
	chunkGenerator = generator;
	chunkDecorators = decorators;
	objects = new std::vector<GameObject*>();
}

Chunk Chunk::Load(std::string File)
{
	return Chunk(0,0, nullptr, nullptr, nullptr);
}

void Chunk::Render(Window* window)
{
	chunkRender->Render(window);
}

void Chunk::Generate()
{
	chunkGenerator->generateChunkData(data, noise);
	for (int i = 0; i < chunkDecorators->size(); i++)
	{
		chunkDecorators->at(i)->decorateChunkData(data, noise);
	}
}

void Chunk::Initialize()
{
	mesher.MeshChunk(data, primitiveType);
}

void Chunk::Buffer()
{
	chunkRender->RegisterPrimitives(data->vertices, data->colors, primitiveType);
	data->DeleteBufferArrays();
}

Chunk::~Chunk()
{
	delete data;
	data = nullptr;
	delete chunkRender;
	chunkRender = nullptr;
	delete objects;
	objects = nullptr;
}
