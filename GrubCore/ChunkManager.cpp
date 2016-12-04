#include "ChunkManager.h"

std::vector<Chunk*> ChunkManager::chunkList;
std::vector<std::thread> ChunkManager::ThreadPool;
BlockingQueue<ChunkRequest> ChunkManager::generationRequests;
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
		ChunkRequest request = generationRequests.pop();
		switch (request.chunkRequestType)
		{
		case ChunkRequest::Generation:
			request.chunk->Generate();
			request.chunk->Initialize();
			finishedGeneration.push(request.chunk);
			break;
		case ChunkRequest::Deletion:
			delete request.chunk;
			request.chunk = nullptr;
			break;
		}
	}
}

void ChunkManager::RequestChunk(int x, int z, ChunkRenderer* renderer, ChunkGenerator* generator, std::vector<ChunkDecorator*>* decorators)
{
	Chunk* chunk = new Chunk(x, z, renderer, generator, decorators);
	generationRequests.push(ChunkRequest(ChunkRequest::Generation, x, z, chunk));
}

void ChunkManager::RemoveChunk(int x, int z)
{
	for (int i = 0; i < chunkList.size(); i++)
	{
		Chunk* chunk = chunkList[i];
		if (chunk->data->ChunkX == x && chunk->data->ChunkZ == z)
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

void ChunkManager::DrawChunks(Window* window)
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
