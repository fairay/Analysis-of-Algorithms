#include "arr.h"

arr_t create_arr(int n)
{
	return new content_t[n];
}

void print_arr(arr_t arr, int n)
{
	for (int i = 0; i < n; i++)
		printf("%d ",arr[i]);
	printf("\n");
}

void input_arr(arr_t arr, int n)
{
	for (int i = 0; i < n; i++)
		std::cin >> arr[i];
}

void free_arr(arr_t* arr)
{
	delete* arr;
	*arr = nullptr;
}


arr_t copy_arr(arr_t source, int n)
{
	arr_t dest = create_arr(n);
	for (int i = 0; i < n; i++)
		dest[i] = source[i];
	return dest;
}

arr_t random_arr(int n)
{
	arr_t arr = create_arr(n);
	for (int i = 0; i < n; i++)
		arr[i] = rand() % (2*n) - n;
	return arr;
}

void fill_random_arr(arr_t arr, int n)
{
	for (int i = 0; i < n; i++)
		arr[i] = rand() % (2 * n) - n;
}

bool is_equal_arr(arr_t arr1, arr_t arr2, int n)
{
	for (int i = 0; i < n; i++)
		if (arr1[i] != arr2[i]) return false;
	return true;
}