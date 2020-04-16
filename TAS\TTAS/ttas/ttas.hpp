#include <iostream>
#include <atomic>
#include <cassert>
#include <thread>

enum TTAS_CONFIGS
{
	Min_backoff_time   	= 200,
	Max_backoff_time   	= (2^10) * Min_backoff_time,
	Exp_backoff_coeff 	= 2,
	Sleep_time 			= 100
};

class spin_lock_TTAS
{
private:
	std::atomic<unsigned int> m_spin;
	static void exp_backoff(unsigned int &backoff_time);
public:
	spin_lock_TTAS(): m_spin(0) {}
	~spin_lock_TTAS() { assert(m_spin.load() == 0);}

	void lock();
	void yield_lock();
	void sleep_yield_lock();
	void exp_backoff_lock();
	void unlock();
};


