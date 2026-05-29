#include <queue>
#include <mutex>
#include <condition_variable>

template<typename T>

class ThreadSafeQueue {
	std::queue<T> q;
	std::mutex mx;
	std::condition_varaible cv;
	size_t maxSize;

public:
	ThreadSafeQueue(size_t maxSize = 30) : maxSize(maxSize) {}

	void push(T item) {
		std::unique_lock<std::mutex> lock(mx);
		if (q.size() >= maxSize) q.pop();
		q.push(std::move(item)); //move keeps things fast by transfering ownership of items block
		cv.notify_all();
	}
	T pop() {
		std::unique_lock<std::mutex> lock(mx);
		cv.wait(lock, [&]{return !q.empty(); });
		T item = std::move(q.front());
		q.pop;
		return item;
	}
}


