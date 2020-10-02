#include "bubble.h"

void bubble_sort(arr_t arr, int n)
{
	content_t temp;
	for (int i=1; i<n; i++)
		for (int j=0; j<n-i; j++)
			if (arr[j] > arr[j + 1])
			{
				temp = arr[j + 1];
				arr[j + 1] = arr[j];
				arr[j] = temp;
			}
}
