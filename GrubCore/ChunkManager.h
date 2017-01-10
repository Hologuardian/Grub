#ifndef GRUB_CHUNKMANAGER
#define GRUB_CHUNKMANAGER
#include "Constants.h"
#include <unordered_map>
#include <map>
#include <vector>
#include <thread>
#include "BlockingQueue.h"
#include "Window.h"
#include "ChunkRequest.h"
#include <unordered_map>
#include "ChunkUpdate.h"

class ChunkManager
{
public:

	/**
		Required to be called in order to create thread pool, uses const definition for number of threads to be generated
	*/
	static void Initialize();
	/**
		Destroys all currently generated chunks
		Attempts to clear generation request queue, but cannot garuntee chunks in mid-generation will be stopped.
	*/
	static void Clear();
	ChunkManager() = delete;
	~ChunkManager() = delete;

	/**
	Creates a chunk at the requested chunk position, requires a chunk renderer specified to generate the chunk.

	The x and z are the chunk position, which is the absolute position divided by the chunk width.
	*/
	static void RequestChunk(int x, int z, ChunkRenderer* renderer, ChunkGenerator* generator, std::vector<ChunkDecorator*>* decorators);

	/**
	Requests a specific chunk to be removed, this is not currently a threaded operation.

	The x and z are the chunk position, which is the absolute position divided by the chunk width.
	*/
	static void RemoveChunk(int x, int z);

	/**
	Creates a chunk at the requested chunk position, requires a chunk renderer specified to generate the chunk.

	The x and z are the chunk position, which is the absolute position divided by the chunk width.
	*/
	static void SetBlock(long long int x, int y, long long int z);

	/**
	Draws all chunks to the specified window pointer.
	*/
	static void DrawChunks(Window* window);

	/**
	Changes the generation seed of the requested chunks

	This will cause splits in the terrain to form
	*/
	static void SetSeed(int seed);

	/**
	Takes a chunk pointer and hashes it's position
	*/
	static long long int Hash(Chunk* chunk)
	{
		return ((long long int)chunk->data->ChunkX) + ((long long int)chunk->data->ChunkZ) * (((long long int)INT_MAX) / ((long long int)(ChunkWidth + 1)));
	}

	/**
	Takes two ints and hash them
	*/
	static long long int Hash(int x, int z)
	{
		return  ((long long int)x) + ((long long int)z) * (((long long int)INT_MAX) / ((long long int)(ChunkWidth + 1)));
	}
private:
	static void GenerateChunk();
	static void Update();
	static void CheckDeletionQueue();
	static void CheckUpdateQueue();
	static std::unordered_map<long long int, Chunk*> chunkMap;
	static std::vector<long long int> chunkList;
	static std::queue<long long int> deletionPool;
	static std::queue<ChunkUpdate*> chunkUpdateQueue;
	static std::vector<std::thread> ThreadPool;	
	static BlockingQueue<ChunkRequest> generationRequests;
	static BlockingQueue<Chunk*> finishedGeneration;
};
#endif