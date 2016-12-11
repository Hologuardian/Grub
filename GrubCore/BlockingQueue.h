#ifndef GRUB_BLOCKINGQUEUE
#define GRUB_BLOCKINGQUEUE
#include <queue>
#include <condition_variable>
#include <deque>

template <typename T>
class BlockingQueue
{
private:
	std::mutex mutex;
	std::deque<T> queue;
public:
	std::condition_variable condVar;
	bool run = true;
	/**
	Pushes an item onto the queue, thread safe.
	*/
	void push(T const& value)
	{
		std::unique_lock<std::mutex> lock(this->mutex);
		queue.push_front(value);
		this->condVar.notify_one();
	}

	/**
	Pops an item from the queue, will lock the thread until an item is recieved.
	*/
	T pop()
	{
		std::unique_lock<std::mutex> lock(this->mutex);
		this->condVar.wait(lock, [=] { return !this->queue.empty(); });
		this->condVar.wait(lock, [=] { return this->run == true; });
		T rc(std::move(this->queue.back()));
		this->queue.pop_back();
		return rc;
	}

	/**
	Clears the queue, not thread safe.
	*/
	bool empty()
	{
		return queue.empty();
	}

	int size()
	{
		return queue.size();
	}
};
#endif