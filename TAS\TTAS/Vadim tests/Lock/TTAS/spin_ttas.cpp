#include "spin_ttas.hpp"
#include <iostream>
#include <unistd.h>
void Spin_lock_tas::lock(){
	uint32_t expected(0);
	do
	{
		/* First test the lock without invalidating
            any cache lines */
		while(spin_.load())
			std::this_thread::yield();
		expected = 0;
	}while(spin_.exchange(1, std::memory_order_acquire));
}

void Spin_lock_tas::unlock(){
	uint32_t desired(0);
	spin_.store(desired, std::memory_order_seq_cst);
}

// exchange
//  139,97s user 0,36s system 358% cpu 39,115 total
//  49,47s user 100,30s system 362% cpu 41,327 total -- yield

//  compare_exchange_weak()
//  144,57s user 0,14s system 365% cpu 39,629 total
//  48,76s user 95,64s system 345% cpu 41,801 total -- yield

void Spin_lock_tas::exp_lock(){
	size_t delay_time = MIN_DELAY_TIME;
    while (true)
    {
        while(spin_.load())
			std::this_thread::yield();
 
        if (spin_.exchange(1, std::memory_order_acquire))
            backoff_exp(delay_time); // Couldn't acquire lock => back-off
        else
            break; // Acquired lock => done
    }
	
}


void Spin_lock_tas::backoff_exp(size_t &delay_time)
{
    usleep(delay_time);
    if (delay_time < MAX_DELAY_TIME)
    {
        delay_time *= DELAY_MULTIPLIER;
    }
}

// exp: 52,80s user 102,76s system 362% cpu 42,868 total

void Spin_lock_tas::pause_lock(){
	size_t delay_time = MIN_DELAY_TIME;
    while (true)
    {
        while(spin_.load())
			std::this_thread::yield();
 
        if (spin_.exchange(1, std::memory_order_acquire))
            backoff_exp_pause(delay_time); // Couldn't acquire lock => back-off
        else
            break; // Acquired lock => done
    }
}

void Spin_lock_tas::yield_sleep()
{
	std::this_thread::sleep_for(std::chrono::microseconds(500));
}


void Spin_lock_tas::backoff_exp_pause(size_t &delay_time)
{
    asm("pause");
    if (delay_time < MAX_DELAY_TIME)
    {
        delay_time *= DELAY_MULTIPLIER;
    }
    else{
    	yield_sleep();
    }
}

