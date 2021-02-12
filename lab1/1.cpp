#include <cstdio>
#include <cstdlib>
#include <ctime>

#define SIZE 100000000l

// функции подсчета сравнений в соответствующих алгоритмах поиска
long long linear_search(int *arr, long long len, int val);
long long linear_search_with_barrier(int *arr, long long len, int val);
long long binary_search(int *arr, long long len, int val);
long long binary_search_recursive(int *arr, long long left, long long right, int val);

void random_fill(int *arr, long long len, int min, int max);
void fill_ordered(int *arr, long long len, int min, int max);
void print_arr(int *arr, long long len);

int main()
{
	int *arr = (int*)calloc(SIZE, sizeof(*arr));
	if(arr == NULL) {
		puts("Failed to allocate memory to array");
		return 1;
	}

	fill_ordered(arr, SIZE, -1000, 1000);
	printf("%d %d %d\n", arr[0], arr[SIZE/2], arr[SIZE-1]);
	printf("\t%10d\t%10d\t%10d\t%10d\n\t%10d\t%10d\t%10d\t%10d\n\t%10d\t%10d\t%10d\t%10d\n\t%10d\t%10d\t%10d\t%10d\n",
		linear_search(arr, SIZE, arr[0]), linear_search(arr, SIZE, arr[SIZE-1]),
		linear_search(arr, SIZE, arr[SIZE/2]), linear_search(arr, SIZE, 2000),

		linear_search_with_barrier(arr, SIZE, arr[0]), linear_search_with_barrier(arr, SIZE, arr[SIZE-1]),
		linear_search_with_barrier(arr, SIZE, arr[SIZE/2]), linear_search_with_barrier(arr, SIZE, 2000),

		binary_search(arr, SIZE, arr[0]), binary_search(arr, SIZE, arr[SIZE-1]),
		binary_search(arr, SIZE, arr[SIZE/2]), binary_search(arr, SIZE, 2000),

		binary_search_recursive(arr, 0, SIZE, arr[0]), binary_search_recursive(arr, 0, SIZE, arr[SIZE-1]),
		binary_search_recursive(arr, 0, SIZE, arr[SIZE/2]), binary_search_recursive(arr, 0, SIZE, 2000));

	free(arr);

	return 0;
}

long long linear_search(int *arr, long long len, int val)
{
	int count = 0;

	int i = 0;
	while(true) {
		count++;
		if(!(i < len))
			break;

		count++;
		if(!(arr[i] != val))
			break;

		i++;
	}

	count++;
	if(i == len) {
		// return -1
		return count;
	}

	// return i
	return count;
}

long long linear_search_with_barrier(int *arr, long long len, int val)
{
	int count = 0;

	int old_val = arr[len-1];
	arr[len-1] = val;

	int i = 0;
	while(true) {
		count++;
		if(!(arr[i] != val))
			break;
		i++;
	}

	count += 2;
	if(i != len-1 || old_val == arr[len-1]) {
		//return i;
		return count;
	}
	arr[len-1] = old_val;

	//return -1;
	return count;
}

long long binary_search(int *arr, long long len, int val)
{
	int count = 0;

	int left = 0, right = len, mid;
	while(true) {
		count++;
		if(!(left < right))
			break;

		mid = (left+right)/2;

		count++;
		if(arr[mid] == val) {
			//return mid;
			return count;
		} else {
			count++;
			if(val < arr[mid])
				right = mid-1;
			else
				left = mid+1;
		}
	}
	//return -1;
	return count;
}

long long binary_search_recursive(int *arr, long long left, long long right, int val)
{
	int count = 0;

	int mid = (left+right)/2;

	count++;
	if(arr[mid] == val)
		//return mid;
		return count;

	count++;
	if (mid == left || mid == right)
		//return -1;
		return count;
	else {
		count++;
		if(val < arr[mid])
			//return binary_search_recursive(arr, left, mid, val);
			return count + binary_search_recursive(arr, left, mid, val);
		else
			//return binary_search_recursive(arr, mid, right, val);
			return count + binary_search_recursive(arr, mid, right, val);
	}
}

void random_fill(int *arr, long long len, int min, int max)
{
	srand(time(NULL));
	for(long long i = 0; i < len; i++)
		arr[i] = rand() % (max - min + 1) + min;
}

void fill_ordered(int *arr, long long len, int min, int max)
{
	srand(time(NULL));
	for(long long i = 0; i < len; i++) {
		arr[i] = min + (max-min) * i / len;
	}
}

void print_arr(int *arr, long long len)
{
	for(long long i = 0; i < len; i++) {
		printf("\t%d", arr[i]);
		if(i%10 == 9)
			printf("\n");
	}
}

