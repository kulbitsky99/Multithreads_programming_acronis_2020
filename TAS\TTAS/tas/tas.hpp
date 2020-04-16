#include <iostream>
#include <atomic>
#include <cassert>
#include <thread>

class spin_lock_TAS
{
private:
	std::atomic<unsigned int> m_spin;
public:
	spin_lock_TAS(): m_spin(0) {}
	~spin_lock_TAS() { assert(m_spin.load() == 0);}

	void lock();
	void yield_lock();
	void unlock();
};


