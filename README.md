# Multithreads_programming_acronis_2020

## cas_list.c

Program creates single connected list with ability to add elements to the forward position(like `push()` in stack) and to any positions in a list. There is iterator `for_each()` to pass through list elements too. This program is designed to be used in multithread programming. It adds elements to a list *atomically* with the help of primitive `atomic_compare_exchange_weak()` in C11 language. 

Check later updates with defence from ABA collisions and lock-free structures.

## tas/ttas spin_locks; ticket_lock

Simple realization of different locks:

	- Test and set lock(and yield lock)
	- Test and test and set lock(and yield_lock, sleep_yield_lock, exponential_backoff_lock)
	- Ticket lock(and yield lock)

See the pictures in TAS/TTAS folders

## block_matrix_mutiplication

Carry out multiplication of big matrixes with right usage of cache lines(loaded for the CPU cache data should be used effectively)

### Results 
For input parameters: `size` = 512 * 512, `block` = 32.

	[x] Simple product time = 1540 us
	[x] Block matrix time = 956 us

Check the graph working_time_in_us(size of matrix side) in `block_matrix_mutiplication`	folder (yellow - simple product; blue - block product).

