#include <iostream>
#include <atomic>
#include <cassert>
#include <thread>

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


