#include <cstdio>
#include <cstdlib>

#define WIDTH 15
#define HEIGHT 255

bool bin(int *arr, int x1, int x2, int y1, int y2, int val);
void generate_array(int *arr, int width, int height);
void print_array(int *arr, int width, int height);

int main()
{
	int *arr = (int*)calloc(WIDTH*HEIGHT, sizeof(*arr));
	generate_array(arr, WIDTH, HEIGHT);
	//print_array(arr, WIDTH, HEIGHT);

	if(bin(arr, 0, WIDTH, 0, HEIGHT, 100))
		puts("lol");

	return 0;
}

void generate_array(int *arr, int width, int height)
{
	for(int j = 0; j < height; j++)
		for(int i = 0; i < width; i++)
			arr[j*width + i] = (2*j + 3*i) / 5;
}

void print_array(int *arr, int width, int height)
{
	for(int j = 0; j < height; j++) {
		for(int i = 0; i < width; i++)
			printf("%6d", arr[j*width + i]);
		puts("");
	}
}

bool bin(int *arr, int x1, int x2, int y1, int y2, int val)
{
	if(arr[y1*WIDTH + x1] == val ||
		arr[y1*WIDTH + x2] == val ||
		arr[y2*WIDTH + x1] == val ||
		arr[y2*WIDTH + x2] == val)
		return true;

	if(x1 == x2 || y1 == y2)
		return false;

	return bin(arr, x1, (x1+x2)/2, y1, (y1+y2)/2, val) ||
		bin(arr, (x1+x2)/2, x2, y1, (y1+y2)/2, val) ||
		bin(arr, x1, (x1+x2)/2, (y1+y2)/2, y2, val) ||
		bin(arr, (x1+x2)/2, (y1+y2)/2, x2, y2, val);
}

