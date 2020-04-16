#include <atomic>
#include <cassert>
#include <thread>

enum THREAD_COMP{
	//THREAD_NUMBER    = 400,
	ITER_NUMBER      = 200000,
	MIN_DELAY_TIME   = 200,
	MAX_DELAY_TIME   = MIN_DELAY_TIME << 8,
	DELAY_MULTIPLIER = 2
};

class Spin_lock_tas{
public:
	Spin_lock_tas():
		spin_(0){};
	~Spin_lock_tas()
	{
		assert(spin_.load() == 0);
	};
	void lock();
	void exp_lock();
	void pause_lock();
	void unlock();
private:
	std::atomic<unsigned int> spin_;
	static void backoff_exp(size_t &delay_time);
	static void backoff_exp_pause(size_t &delay_time);
	static void yield_sleep();
};