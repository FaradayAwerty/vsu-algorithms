#include <cstdlib>
#include <cstdio>

#define SIZE 100000000l

void linear_search(long long int *arr,
		long long int len,
		long long int val,
		long long int &index,
		long long int &num);
void linear_search_with_barrier(long long int *arr,
		long long int len,
		long long int val,
		long long int &index,
		long long int &num);
void binary_search(long long int *arr,
		long long int len,
		long long int val,
		long long int &index,
		long long int &num);
long long int binary_search_recursive(long long int *arr,
		long long int left,
		long long int right,
		long long int val,
		long long int &num);
void generate_array(long long int *arr, long long int size);
void print_array(long long int *arr, long long int istart, long long int num);

int main()
{
	long long int *arr = (long long int*)calloc(SIZE, sizeof(*arr));

	generate_array(arr, SIZE);
	print_array(arr, 0, 100);
	print_array(arr, SIZE/2 - 50, 100);
	print_array(arr, SIZE-100, 100);

	long long int elements_to_find[] = {0, SIZE-1, SIZE/2, -100};
	long long int index, count;

	// row 1
	for(int i = 0; i < 4; i++) {
		linear_search(arr, SIZE, elements_to_find[i], index, count);
		printf("%10ld ", count);
	}
	puts("");

	// row 2
	for(int i = 0; i < 4; i++) {
		linear_search_with_barrier(arr, SIZE, elements_to_find[i], index, count);
		printf("%10ld ", count);
	}
	puts("");

	// row 3
	for(int i = 0; i < 4; i++) {
		binary_search(arr, SIZE, elements_to_find[i], index, count);
		printf("%10ld ", count);
	}
	puts("");

	// row 3
	for(int i = 0; i < 4; i++) {
		count = 0;
		index = binary_search_recursive(arr, 0, SIZE, elements_to_find[i], count);
		printf("%10ld ", count);
	}
	puts("");

	free(arr);
	return 0;
}

void print_array(long long int *arr, long long int istart, long long int num)
{
	for(long long int i = istart; i < istart+num; i++) {
		printf("%10ld ", arr[i]);
		if(i%10 == 9)
			puts("");
	}
	puts("");
}

void generate_array(long long int *arr, long long int size)
{
	for(long long int i = 0; i < size; i++)
		arr[i] = i;
}

void linear_search(long long int *arr,
		long long int len,
		long long int val,
		long long int &index,
		long long int &num)
{
	num = 0;
	index = 0;
	while(index < len && arr[index] != val) {
		index += 1;
		num += 2; // if condition is true then there was two comparisons
	}

	num += 1+2; // comparison bellow and two comparisons from loop
	if(index == len) {
		index = -1;
		num -= 1; // if index==len then the second comparison in loop didn't happen
	}
}

void linear_search_with_barrier(long long int *arr,
		long long int len,
		long long int val,
		long long int &index,
		long long int &num)
{
	long long int old_val = arr[len-1];
	arr[len-1] = val;

	num = 0;
	index = 0;
	while(arr[index] != val) {
		index += 1;
		num += 1; // if condition is true then there was one comparison
	}
	num += 1; // comparison from loop

	num += 1; // comparison bellow
	if(index == len) {
		num += 1; // comparison bellow
		if(old_val != val)
			index = -1;
	}
	arr[len-1] = old_val;
}

void binary_search(long long int *arr,
		long long int len,
		long long int val,
		long long int &index,
		long long int &num)
{
	num = 0;
	index = -1;
	long long int left = 0, right = len, mid;
	while(left < right)
	{
		num +=1; // comparison above
		mid = (left+right)/2;

		num += 1; // comparison bellow
		if(arr[mid] == val) {
			index = mid;
			return;
		}

		num += 1; // comparison bellow
		if(val < arr[mid]) {
			right = mid;
		} else {
			left = mid+1;
		}
	}
	num +=1; // comparison that stops the loop
}

long long int binary_search_recursive(long long int *arr,
		long long int left,
		long long int right,
		long long int val,
		long long int &num)
{
	long long int mid = (left+right)/2;
	num += 3; // at most 3 comparisons bellow
	if(arr[mid] == val) {
		num -= 2; // next two comparisons won't happen
		return mid;
	} else if (mid == left || mid == right) {
		num -= 1; // next comparison won't happen
		return -1;
	} else if(val < arr[mid]) {
		return binary_search_recursive(arr, left, mid, val, num);
	} else {
		return binary_search_recursive(arr, mid, right, val, num);
	}
}

