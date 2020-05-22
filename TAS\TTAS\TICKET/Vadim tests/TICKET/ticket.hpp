#include <atomic>
#include <cassert>
#include <thread>

enum TTAS_CONFIGS
{
	ITER_NUMBER      = 100000,
	Min_backoff_time   	= 200,
	Max_backoff_time   	= (2^8) * Min_backoff_time,
	Exp_backoff_coeff 	= 2,
	Sleep_time 			= 500
};

class ticket_lock
{
private:
	std::atomic_size_t now_serving = {0};
	std::atomic_size_t next_ticket = {0};
public:
	void lock();
	void yield_lock();
	void unlock();
};
