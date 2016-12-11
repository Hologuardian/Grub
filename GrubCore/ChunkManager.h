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
#include "BlockingChunkVector.h"

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
	Draws all chunks to the specified window pointer.
	*/
	static void DrawChunks(Window* window);
	/**
	Changes the generation seed of the requested chunks

	This will cause splits in the terrain to form
	*/
	static void SetSeed(int seed);
private:
	static void GenerateChunk();
	static void Update();
	static BlockingChunkVector chunkList;
	static std::queue<Chunk*> deletionPool;
	static std::vector<std::thread> ThreadPool;	
	static BlockingQueue<ChunkRequest> generationRequests;
	static BlockingQueue<Chunk*> finishedGeneration;
};
#endif