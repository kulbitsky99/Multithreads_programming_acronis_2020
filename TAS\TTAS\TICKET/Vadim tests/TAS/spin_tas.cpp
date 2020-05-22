#include "spin_tas.hpp"
#include <iostream>

void spin_lock_TTAS::lock()
{
    unsigned int expected;
    do
    {
        while(spin_.load());
        expected = 0;
    }
    while(!spin_.compare_exchange_weak(expected, 1));
}

void spin_lock_TTAS::yield_lock()
{
    unsigned int expected;
    do
    {
        while(spin_.load())
            std::this_thread::yield();
        expected = 0;
    }
    while(!spin_.compare_exchange_weak(expected, 1));
}

void spin_lock_TTAS::sleep_yield_lock()
{
    unsigned int expected;
    do
    {
        while(spin_.load())
            std::this_thread::sleep_for(std::chrono::microseconds(Sleep_time));
        expected = 0;
    }
    while(!spin_.compare_exchange_weak(expected, 1));
}

void spin_lock_TTAS::exp_backoff_lock()
{
    unsigned int expected;
    unsigned int backoff_time = Min_backoff_time;
    do
    {
        while(spin_.load())
            exp_backoff(backoff_time);
            //std::this_thread::yield();
        expected = 0;
    }
    while(!spin_.compare_exchange_weak(expected, 1));
}

void spin_lock_TTAS::unlock()
{
    spin_.store(0, std::memory_order_seq_cst);
}

void spin_lock_TTAS::exp_backoff(unsigned int &backoff_time)
{
    std::this_thread::sleep_for(std::chrono::microseconds(backoff_time));
    if (backoff_time < Max_backoff_time)
    {
        backoff_time *= Exp_backoff_coeff;
    }
}
