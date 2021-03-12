#include <cstdio>
#include <cstdlib>

#define WIDTH 15
#define HEIGHT 255

void linear_search(int *arr, int width, int height, int val, int &i, int &j);
void linear_search_with_barrier(int *arr, int width, int height, int val, int &i, int &j);
void generate_array(int *arr, int width, int height);
void print_array(int *arr, int width, int height);

int main()
{
	int *arr = (int*)calloc(WIDTH*HEIGHT, sizeof(*arr));
	generate_array(arr, WIDTH, HEIGHT);
	print_array(arr, WIDTH, HEIGHT);

	int i, j;
	linear_search(arr, WIDTH, HEIGHT, -10, i, j);
	printf("%d %d\n", i, j);

	linear_search_with_barrier(arr, WIDTH, HEIGHT, -10, i, j);
	printf("%d %d\n", i, j);

	return 0;
}

void generate_array(int *arr, int width, int height)
{
	for(int j = 0; j < height; j++)
		for(int i = 0; i < width; i++)
			arr[j*width + i] = 2*j - 3*i;
}

void print_array(int *arr, int width, int height)
{
	for(int j = 0; j < height; j++) {
		for(int i = 0; i < width; i++)
			printf("%6d", arr[j*width + i]);
		puts("");
	}
}

void linear_search(int *arr, int width, int height, int val, int &i, int &j)
{
	for(j = 0; j < height; j++)
		for(i = 0; i < width; i++)
			if(arr[j*width + i] == val)
				return;
	i = -1;
	j = -1;
}

void linear_search_with_barrier(int *arr, int width, int height, int val, int &i, int &j)
{
	int old_val = arr[width*height-1];
	arr[width*height-1] = val;

	int k = 0;
	while(arr[k] != val)
		k++;

	arr[width*height-1] = old_val;

	i = k % width;
	j = k / width;

	if(i == width*height-1 && old_val != val) {
		i = -1;
		j = -1;
	}

}

