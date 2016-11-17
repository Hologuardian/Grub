#include "ChunkManager.h"

std::vector<Chunk*> ChunkManager::chunkList;
std::vector<std::thread> ChunkManager::ThreadPool;
BlockingQueue<Chunk*> ChunkManager::generationRequests;
BlockingQueue<Chunk*> ChunkManager::finishedGeneration;

void ChunkManager::Initialize()
{
	for (int i = 0; i < ThreadPoolSize; i++)
	{
		ThreadPool.push_back(std::thread(ChunkManager::GenerateChunk));
	}
}

void ChunkManager::Clear()
{
	for each(Chunk* chunk in chunkList)
	{
		delete chunk;
		chunk = nullptr;
	}
	chunkList.clear();
}

void ChunkManager::GenerateChunk()
{
	while (true)
	{
		Chunk* toGen = generationRequests.pop();
		toGen->Generate();
		toGen->Initialize();
		finishedGeneration.push(toGen);
	}
}

void ChunkManager::RequestChunk(int x, int z, ChunkRenderer* renderer)
{
	Chunk* chunk = new Chunk(x, z, renderer);
	generationRequests.push(chunk);
}

void ChunkManager::RemoveChunk(int x, int z)
{
	for (int i = 0; i < chunkList.size(); i++)
	{
		Chunk* chunk = chunkList[i];
		if (chunk->ChunkX == x && chunk->ChunkZ == z)
			chunkList.erase(chunkList.begin() + i);
	}
}

void ChunkManager::Update()
{
	while (!finishedGeneration.empty())
	{
		Chunk* chunk = finishedGeneration.pop();
		chunk->Buffer();
		chunkList.push_back(chunk);
	}
}

void ChunkManager::DrawChunks(AbstractWindow* window)
{
	Update();
	for each(Chunk* chunk in chunkList)
	{
		chunk->Render(window);
	}
}

void ChunkManager::SetSeed(int seed)
{
	Chunk::noise.SetSeed(seed);
}
