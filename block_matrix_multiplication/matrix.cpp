#include <iostream>
#include <climits>
#include <vector>
#include <chrono>


void print_matrix(double** matrix, int N);
void generate_matrix(double** matrix, int N);
void simple_product(double** a, double** b, double** c, int N);
void find_product(double** a, double** b, double** c, int N, int s);
int block_min(int j_block, int s, int N);

long int input_retrieval(char * str)
{
	char* end;
	long int data = 0;
	data = strtol(str, &end, 10);
	if(data == LONG_MAX || data == LONG_MIN || data == 0)
	{
		printf("Invalid input. Please, check your length number!\n");
		exit(-1);
	}
	return data;
}

int main(int argc, char** argv)
{
	long int N = 0, Block = 0;
	std::cout << "Print size of matrixes and size of block to use cache effectively.\n";
	if(argc != 3)
	{
		printf("Invalid number of input arguments!\n");
		exit(-1);
	}

	N = input_retrieval(argv[1]);
	Block = input_retrieval(argv[2]);


	//allocate memory for matrixes
	double** a = new double*[N];
	double** b = new double*[N];
	double** c = new double*[N];

	for(int i = 0; i < N; i++)
	{
		a[i] = new double[N];
		b[i] = new double[N];  
		c[i] = new double[N]; 
	}

	generate_matrix(a, N);
	generate_matrix(b, N);


	//print_matrix(a, N);
	//print_matrix(b, N);

	auto start = std::chrono::system_clock::now();
	simple_product(a, b, c, N);
	auto end = std::chrono::system_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "Simple product time = " << elapsed.count() << '\n';

	start = std::chrono::system_clock::now();
	find_product(a, b, c, N, Block);
	end = std::chrono::system_clock::now();
	elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << " Block matrix time = " << elapsed.count() << '\n';

	// free
	for(int i = 0; i < N; i++)
	{
    	delete [] a[i];
    	delete [] b[i];
    	delete [] c[i];
	}
	delete [] a;
	delete [] b;
	delete [] c;

	return 0;
}


void print_matrix(double** matrix, int N)
{
	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
		{
			std::cout << matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void generate_matrix(double** matrix, int N)
{
	for(int i = 0; i < N; i++)
		for(int j = 0; j < N; j++)
		{
			matrix[i][j] = rand() % N + 1; // just as an example
		}
}

void simple_product(double** a, double** b, double** c, int N)
{
	for(int i = 0; i < N; i++)
		for(int j = 0; j < N; j++)
			for(int k = 0; k < N; k++)
				c[i][j] += a[i][k] * b[k][j];
}

void find_product(double** a, double** b, double** c, int N, int s)
{
	
	for(int j_block = 0; j_block < N; j_block += s)
	    for(int k_block = 0; k_block < N; k_block += s)
	        for(int i = 0; i < N; i++)
	            for(int j = j_block; j < block_min(j_block, s, N); j++)
	            {
	                double temp = 0;
	                for(int k = k_block; k < block_min(k_block, s, N); k++)
	                    temp += a[i][k] * b[k][j];
	                c[i][j] += temp;
	            }
}

int block_min(int j_block, int s, int N)
{
	if((j_block + s) > N)
		return N;
	else
		return (j_block + s);
}

