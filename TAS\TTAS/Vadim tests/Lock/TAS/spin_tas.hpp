#include <atomic>
#include <cassert>
#include <thread>

enum THREAD_COMP{
	THREAD_NUMBER = 109,
	ITER_NUMBER   = 200000
};

class spin_lock_TAS
{
private:
	std::atomic<unsigned int> spin_;
public:
	spin_lock_TAS(): spin_(0) {}
	~spin_lock_TAS() { assert(spin_.load() == 0);}

	void lock();
	void yield_lock();
	void unlock();
};
