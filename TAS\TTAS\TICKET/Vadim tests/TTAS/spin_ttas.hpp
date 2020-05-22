#include <atomic>
#include <cassert>
#include <thread>

enum TTAS_CONFIGS
{
	ITER_NUMBER      = 200000,
	Min_backoff_time   	= 200,
	Max_backoff_time   	= (2^8) * Min_backoff_time,
	Exp_backoff_coeff 	= 2,
	Sleep_time 			= 500
};

class spin_lock_TTAS
{
private:
	std::atomic<unsigned int> spin_;
	void exp_backoff(unsigned int &backoff_time);
public:
	spin_lock_TTAS(): spin_(0) {}
	~spin_lock_TTAS() { assert(spin_.load() == 0);}

	void lock();
	void yield_lock();
	void sleep_yield_lock();
	void exp_backoff_lock();
	void unlock();
};