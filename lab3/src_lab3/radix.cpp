#include "radix.h"

int* create_digit_arr(int k)
{
	int* arr = create_arr(k);
	int n = 1;
	for (int i = 0; i < k; i++, n *= 10)
		arr[i] = n;
	return arr;
}

inline int count_k(int a)
{
	int k = 0;
	while (a > 0)
	{
		a /= 10;
		k++;
	}
	return k;
}

inline int get_digit(int a, int k, int* digit_arr)
{
	a %= digit_arr[k+1];
	a /= digit_arr[k];
	return a;
}

void format_arr(arr_t arr, int n, int& decr, int& k)
{
	int min_el = arr[0];
	int max_el = min_el;
	for (int i = 1; i < n; i++)
	{
		int el = arr[i];
		if (el < min_el)
			min_el = el;
		if (el > max_el)
			max_el = el;
	}

	if (min_el < 0)
	{
		decr = -min_el;
		max_el -= min_el;
		for (int i = 0; i < n; i++)
			arr[i] -= min_el;
	}
	else
	{
		decr = 0;
	}

	k = count_k(max_el);
}

void radix_sort(arr_t& arr, int n)
{
	int k, decr;
	format_arr(arr, n, decr, k);
	int c[10]; // = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int* digit_arr = create_digit_arr(k+1);
	arr_t copy = create_arr(n);
	arr_t swap_arr;

	for (int dig = 0; dig < k; dig++)
	{
		for (int i = 0; i < 10; i++)
			c[i] = 0;

		for (int i = 0; i < n; i++)
			c[get_digit(arr[i], dig, digit_arr)]++;

		int count = 0;
		for (int i = 0; i < 10; i++)
		{
			count += c[i];
			c[i] = count - c[i];
		}

		for (int i = 0; i < n; i++)
			copy[c[get_digit(arr[i], dig, digit_arr)]++] = arr[i];

		swap_arr = arr;
		arr = copy;
		copy = swap_arr;
	}

	if (decr)
		for (int i = 0; i < n; i++)
			arr[i] -= decr;

	free_arr(digit_arr);
	free_arr(copy);
}
