#include "tas.hpp"

void spin_lock_TAS::lock()
{
	unsigned int expected = 0;
	do
	{
		expected = 0;
	}
	while(!m_spin.compare_exchange_weak(expected, 1));
}

void spin_lock_TAS::yield_lock()
{
	unsigned int expected = 0;
	do
	{
		expected = 0;
		std::this_thread::yield();
	}
	while(!m_spin.compare_exchange_weak(expected, 1));
}

void spin_lock_TAS::unlock()
{
	m_spin.store(0, std::memory_order_seq_cst);
}




