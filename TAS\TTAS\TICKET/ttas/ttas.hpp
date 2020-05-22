#include <iostream>
#include <atomic>
#include <cassert>
#include <thread>

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


