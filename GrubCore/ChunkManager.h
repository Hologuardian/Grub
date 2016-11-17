#ifndef GRUB_CHUNKMANAGER
#define GRUB_CHUNKMANAGER
#include "Constants.h"
#include "Chunk.h"
#include <unordered_map>
#include <map>
#include <vector>
#include <thread>
#include "BlockingQueue.h"
#include "Window.h"

class ChunkManager
{
public:
	static void Initialize();
	static void Clear();
	ChunkManager() = delete;
	~ChunkManager() = delete;
	static void GenerateChunk();
	static void RequestChunk(int x, int z, ChunkRenderer* renderer);
	static void RemoveChunk(int x, int z);
	static void Update();
	static void DrawChunks(Window* window);
	static void SetSeed(int seed);
private:
	static std::vector<Chunk*> chunkList;
	static std::vector<std::thread> ThreadPool;	
	static BlockingQueue<Chunk*> generationRequests;
	static BlockingQueue<Chunk*> finishedGeneration;
};
#endif