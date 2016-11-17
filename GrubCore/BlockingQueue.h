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
	std::condition_variable condVar;
	std::deque<T> queue;
public:
	void push(T const& value)
	{
		std::unique_lock<std::mutex> lock(this->mutex);
		queue.push_front(value);
		this->condVar.notify_one();
	}

	T pop()
	{
		std::unique_lock<std::mutex> lock(this->mutex);
		this->condVar.wait(lock, [=] { return !this->queue.empty(); });
		T rc(std::move(this->queue.back()));
		this->queue.pop_back();
		return rc;
	}

	bool empty()
	{
		return queue.empty();
	}
};
#endif