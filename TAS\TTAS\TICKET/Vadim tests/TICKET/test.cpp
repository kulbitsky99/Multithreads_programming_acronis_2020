#include "ticket.hpp"
#include <vector>
#include <iostream>
#include <climits>

long int ReadArg(char * str);
void Count_to_mln(int id);

ticket_lock m_lock;

int main(int argc, char** argv)
{
	if(argc < 2){
		std::cout << "Number of threads argument required!\n";
		exit(EXIT_FAILURE);
	}
	long thread_number = ReadArg(argv[1]);
	// std::cout << thread_number << std::endl;
	std::vector<std::thread> threads;
	// std::cout << "spawning " << thread_number << " threads that count to 1 million...\n";
	for (int i(0); i < thread_number; ++i)
		threads.push_back(std::thread(Count_to_mln, i));
  	for (auto& th : threads)
  		th.join();

	return 0;
}

long int ReadArg(char * str)
{
	char* endptr;
	errno = 0;

	long int number = strtol(str, &endptr, 10);

	
	if ((errno == ERANGE && (number == LONG_MAX || number == LONG_MIN)) || (errno != 0 && number == 0)) 
	{
       		perror("strtol");
        	exit(EXIT_FAILURE);
   	}

	if (endptr == str)
	{
        	fprintf(stderr, "Error!\n");
        	exit(EXIT_FAILURE);
   	}
	if (*endptr != '\0')
	{
        	fprintf(stderr, "Error!\n");
        	exit(EXIT_FAILURE);
   	}

	return number;
}


void Count_to_mln(int id){
	// Spin_lock_tas m_lock;
	m_lock.yield_lock();
	// std::cout << "Thread " << id << " came to job" << std::endl;
	// fflush(stdout);

	for (volatile int i(0); i < ITER_NUMBER; ++i) {}  

	/*std::cout << "Thread " << id << " finished job" << std::endl;
	fflush(stdout);*/
	m_lock.unlock();
}
