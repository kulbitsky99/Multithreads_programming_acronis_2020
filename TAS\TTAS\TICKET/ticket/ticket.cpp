#include "ticket.hpp"

void ticket_lock::lock()
{
	const auto ticket = next_ticket.fetch_add(1);
	while (now_serving.load() != ticket);
}

void ticket_lock::yield_lock()
{
    const auto ticket = next_ticket.fetch_add(1);
    while (now_serving.load() != ticket)
    {
        std::this_thread::yield();
    }
}

void ticket_lock::unlock()
{
	const auto successor = now_serving.load() + 1;
	now_serving.store(successor);
}




