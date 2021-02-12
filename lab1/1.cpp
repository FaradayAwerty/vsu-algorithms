#include <cstdio>
#include <cstdlib>
#include <ctime>

#define SIZE 100000000l

// возвращает количество сравнений
// при поиске элемента со значением `val` в массиве `arr`
// если элемент не найден, возвращает -1
long long linear_search(int *arr, long long len, int val);

// возвращает количество сравнений
// при поиске элемента со значением `val` в массиве `arr`
// если элемент не найден, возвращает -1
long long linear_search_with_barrier(int *arr, long long len, int val);

// возвращает количество сравнений
// при поиске элемента со значением `val` в упорядоченном массиве `arr`
// если элемент не найден, возвращает -1
long long binary_search(int *arr, long long len, int val);

// возвращает количество сравнений
// при поиске элемента со значением `val` в упорядоченном массиве `arr`
// если элемент не найден, возвращает -1
long long binary_search_recursive(int *arr, long long left, long long right, int val);

// заполняет массив `arr` случайными целыми числами в отрезке [min; max]
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
	random_fill(arr, SIZE, -50, 50);

	int elem;
	printf("element to find: ");
	scanf("%d", &elem);
	printf("%d %d\n", linear_search(arr, SIZE, elem),
			linear_search_with_barrier(arr, SIZE, elem));

	free(arr);

	return 0;
}

long long linear_search(int *arr, long long len, int val)
{
	int count = 0; // счетчик количества сравнений

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
	int count = 0; // счетчик количества сравнений

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
	int count = 0; // счетчик количества сравнений

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
			if(val < arr[mid]) {
				right = mid-1;
			} else
				left = mid+1;
		}
	}
	//return -1;
	return count;
}

long long binary_search_recursive(int *arr, long long left, long long right, int val)
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

