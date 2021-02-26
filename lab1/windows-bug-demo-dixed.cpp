#include <iostream>	// input output
#include <cstdlib>	// for random numbers
#include <ctime>	// also for random numbers

#define SIZE 100000000l

int main()
{
	long long int *arr = (long long int*)calloc(SIZE, sizeof(*arr));
	if(arr == NULL) {
		puts("Failed to allocate memory to array");
		return 1;
	}


	free(arr);
	return 0;
}
