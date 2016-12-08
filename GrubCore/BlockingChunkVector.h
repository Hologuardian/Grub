#ifndef GRUB_BLOCKINGCHUNKVECTOR
#define GRUB_BLOCKINGCHUNKVECTOR
#include "Chunk.h"
#include <condition_variable>
#include <vector>
#include "Window.h"

class BlockingChunkVector : public std::vector<Chunk*>
{
private:
	std::mutex mutex;
	std::condition_variable condVar;
public:
	/**
	Pushes an item onto the queue, thread safe.
	*/
	void push_back(Chunk* const& value)
	{
		std::unique_lock<std::mutex> lock(this->mutex);
		std::vector<Chunk*>::push_back(value);
		this->condVar.notify_one();
	}

	void erase(int index)
	{
		std::unique_lock<std::mutex> lock(this->mutex);
		std::vector<Chunk*>::erase(begin() + index);
		this->condVar.notify_one();
	}

	/*void erase(Chunk* object)
	{
		std::unique_lock<std::mutex> lock(this->mutex);
		for (int i = 0; i < size(); i++)
		{
			Chunk* obj = this->at(i);
			if (obj == object)
			{
				std::vector<Chunk*>::erase(begin() + i);
				return;
			}
		}
		this->condVar.notify_one();
	}*/

	void erase(int x, int z)
	{
		std::unique_lock<std::mutex> lock(this->mutex);
		for (int i = 0; i < size(); i++)
		{
			Chunk* chunk = get(i);
			if (chunk->data->ChunkX == x && chunk->data->ChunkZ == z)
			{
				delete chunk;
				chunk = nullptr;
				std::vector<Chunk*>::erase(begin() + i);
			}
		}
		this->condVar.notify_one();
	}

	void DrawAll(Window* window)
	{
		std::unique_lock<std::mutex> lock(this->mutex);
		for (int i = 0; i < size(); i++)
		{
			get(i)->Render(window);
		}
		this->condVar.notify_one();
	}

	Chunk* get(int index)
	{
		return std::vector<Chunk*>::at(index);
	}

	Chunk* get(int x, int z)
	{
		for (int i = 0; i < size(); i++)
		{
			Chunk* chunk = get(i);
			if (chunk->data->ChunkX == x && chunk->data->ChunkZ == z)
			{
				return chunk;
			}
		}
		return 0;
	}

	int size()
	{
		return std::vector<Chunk*>::size();
	}
};
#endif