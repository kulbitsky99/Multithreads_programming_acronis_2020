#include "spin_tas.hpp"
#include <iostream>

void spin_lock_TAS::lock()
{
	unsigned int expected = 0;
	do
	{
		expected = 0;
	}
	while(!spin_.compare_exchange_weak(expected, 1));
}

void spin_lock_TAS::yield_lock()
{
	unsigned int expected = 0;
	do
	{
		expected = 0;
		std::this_thread::yield();
	}
	while(!spin_.compare_exchange_weak(expected, 1));
}

void spin_lock_TAS::unlock()
{
	spin_.store(0, std::memory_order_seq_cst);
}

// 141,42s user 0,06s system 385% cpu 36,694 total
// 57,82s user 95,69s system 388% cpu 39,482 total -- yield
