#include "ChunkManager.h"

std::unordered_map<long long int, Chunk*> ChunkManager::chunkMap;
std::vector<long long int> ChunkManager::chunkList;
std::queue<long long int> ChunkManager::deletionPool;
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
	for each(long long int c in chunkList)
	{
		Chunk* chunk = chunkMap[c];
		delete chunk;
		chunk = nullptr;
	}
	chunkList.clear();
	chunkMap.clear();
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
	deletionPool.push(Hash(x, z));
	return;
}

void ChunkManager::Update()
{
	while (!finishedGeneration.empty())
	{
		Chunk* chunk = finishedGeneration.pop();
		chunk->Buffer();
		long long int key = Hash(chunk);
		chunkList.push_back(key);
		if (chunkMap[key] == nullptr)
			chunkMap[key] = chunk;
		else
			Logger::Log(EMessageType::LOG_ERROR, "Chunk Hash collision at: " + std::to_string(key));
	}
	if (deletionPool.size() > 0)
	{
		for (int n = 0; n < 5; n++)
		{
			generationRequests.run = false;
			long long int key = LLONG_MAX;
			key = deletionPool.front();
			if (key != LLONG_MAX)
			{
				delete chunkMap[key];
				chunkMap[key] == nullptr;
				chunkMap.erase(key);
				for (int i = 0; i < chunkList.size(); i++)
				{
					if (chunkList[i] == key)
						chunkList.erase(chunkList.begin() + i);
				}
			}
			deletionPool.pop();
		}
	}
	else
	{
		generationRequests.run = true;
		generationRequests.condVar.notify_one();
	}
}

void ChunkManager::SetBlock(long long int x, int y, long long int z)
{

}

void ChunkManager::DrawChunks(Window* window)
{
	Update();
	for (int i = 0; i < chunkList.size(); i++)
	{
		chunkMap[chunkList[i]]->Render(window);
	}
}

void ChunkManager::SetSeed(int seed)
{
	Chunk::noise.SetSeed(seed);
}
