#include <cstdio>
#include <cstdlib>
#include <ctime>

#define SIZE 100000000l

int linear_search(int *arr, long long len, int val);
int linear_search_with_barrier(int *arr, long long len, int val);
int binary_search(int *arr, long long len, int val);
int binary_search_recursive(int *arr, long long left, long long right, int val);
void random_fill(int *arr, long long len, int min, int max);
void print_arr(int *arr, long long len);

int main()
{
	int *arr = (int*)calloc(SIZE, sizeof(*arr));
	if(arr == NULL) {
		puts("Failed to allocate memory to array");
		return 1;
	}

	int min, max;
	printf("min element: ");
	scanf("%d", &min);
	printf("max element: ");
	scanf("%d", &max);
	random_fill(arr, SIZE, min, max);

	int elem;
	printf("element to find: ");
	scanf("%d", &elem);

	int index = linear_search(arr, SIZE, elem);
	if(index == -1) {
		puts("element not found");
		return 0;
	}
	printf("%d\n", index);
	print_arr(arr, index+1);

	free(arr);

	return 0;
}

int linear_search(int *arr, long long len, int val)
{
	int i = 0;
	while(i < len && arr[i] != val)
		i++;
	if(i == len)
		return -1;
	return i;
}

int linear_search_with_barrier(int *arr, long long len, int val)
{
	int old_val = arr[len-1];
	arr[len-1] = val;
	int i = 0;
	while(arr[i] != val)
		i++;
	if(i != len-1 || old_val == arr[len-1])
		return i;
	arr[len-1] = old_val;
	return -1;
}

int binary_search(int *arr, long long len, int val)
{
	int left = 0, right = len, mid;
	while(left < right) {
		mid = (left+right)/2;
		if(arr[mid] == val)
			return mid;
		else if(val < arr[mid])
			right = mid-1;
		else
			left = mid+1;
	}
	return -1;
}

int binary_search_recursive(int *arr, long long left, long long right, int val)
{
	int mid = (left+right)/2;
	if(arr[mid] == val)
		return mid;
	else if (mid == left || mid == right)
		return -1;
	else if(val < arr[mid])
		return binary_search_recursive(arr, left, mid, val);
	else
		return binary_search_recursive(arr, mid, right, val);
}

void random_fill(int *arr, long long len, int min, int max)
{
	srand(time(NULL));
	for(long long i = 0; i < len; i++)
		arr[i] = rand() % (max - min + 1) + min;
}

void print_arr(int *arr, long long len)
{
	for(long long i = 0; i < len; i++) {
		printf("\t%d", arr[i]);
		if(i%10 == 9)
			printf("\n");
	}
}

