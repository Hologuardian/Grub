#include "ChunkManager.h"

BlockingChunkVector ChunkManager::chunkList;
std::queue<Chunk*> ChunkManager::deletionPool;
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
			chunkList.erase(request.ChunkX, request.ChunkZ);
			break;
		}
	}
}

void ChunkManager::RequestChunk(int x, int z, ChunkRenderer* renderer, ChunkGenerator* generator, std::vector<ChunkDecorator*>* decorators)
{
	Chunk* chunk = new Chunk(x, z, renderer, generator, decorators);
	generationRequests.push(ChunkRequest(ChunkRequest::Generation, chunk));
}

void ChunkManager::RemoveChunk(int x, int z)
{
	generationRequests.run = false;
	Chunk* chunk = chunkList.get(x, z);
	deletionPool.push(chunk);
	return;
}

void ChunkManager::Update()
{
	while (!finishedGeneration.empty())
	{
		Chunk* chunk = finishedGeneration.pop();
		chunk->Buffer();
		chunkList.push_back(chunk);
	}
	for (int n = 0; n < 25; n++)
	{
		if (deletionPool.size() > 0)
		{
			Chunk* chunk = deletionPool.front();
			if (chunk)
				chunkList.erase(chunk->data->ChunkX, chunk->data->ChunkZ);
			deletionPool.pop();
		}
		else
		{
			generationRequests.run = true;
			generationRequests.condVar.notify_one();
		}
	}
}

void ChunkManager::SetBlock(long x, int y, long z)
{

}

void ChunkManager::DrawChunks(Window* window)
{
	Update();
	chunkList.DrawAll(window);
}

void ChunkManager::SetSeed(int seed)
{
	Chunk::noise.SetSeed(seed);
}
