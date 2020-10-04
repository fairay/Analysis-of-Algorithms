#include "merge.h"
#pragma optimize( "", off )

void merge_sort(arr_t& arr, int n)
{
	content_t temp;
	for (int i = 1; i < n; i += 2)
		if (arr[i - 1] > arr[i])
		{
			temp = arr[i - 1];
			arr[i - 1] = arr[i];
			arr[i] = temp;
		}

	arr_t copy = create_arr(n);
	arr_t swap_arr;
	for (int merge_size = 2; merge_size < n; merge_size *= 2)
	{
		int i = 0;
		for (; i+merge_size < n; i += merge_size * 2)
		{
			int center = i + merge_size;
			int left;
			if (center + merge_size > n)
				left = n;
			else
				left = center + merge_size;

			int j = i;
			int k1 = i;
			int k2 = center;
			while (k1 < center && k2 < left)
			{
				if (arr[k1] < arr[k2])
				{
					copy[j] = arr[k1];
					k1++;
				} 
				else 
				{
					copy[j] = arr[k2];
					k2++;
				}
				j++;
			}

			if (k1 == center)
				for (; k2 < left; k2++, j++)
					copy[j] = arr[k2];
			else 
				for (; k1 < center; k1++, j++)
					copy[j] = arr[k1];
		}

		if (i + merge_size >= n && i < n)
		{			
			for (int j = i; j < n; j++)
				copy[j] = arr[j];
		}
		
		swap_arr = arr;
		arr = copy;
		copy = swap_arr;
	}

	free_arr(copy);
}

#pragma optimize( "", on )
