#include "tests.h"
// Сравнение работы функций со стандартной
bool _cmp_funcs(arr_t arr, int n)
{
	bool flag = true;
	sort_func f_arr[] = { bubble_sort, merge_sort, radix_sort };
	arr_t std_arr = copy_arr(arr, n);
	std::sort(std_arr, std_arr + n);

	for (int i = 0; i < 3 && flag; i++)
	{
		arr_t my_arr = copy_arr(arr, n);
		f_arr[i](my_arr, n);
		flag = is_equal_arr(std_arr, my_arr, n);
		free_arr(my_arr);
	}

	free_arr(std_arr);
	return flag;
}

// Массив размером 1
void _size_one_test()
{
	std::string msg;
	msg = __FUNCTION__;		msg += " - OK";

	arr_t arr = create_arr(1);
	arr[0] = 42;

	if (!_cmp_funcs(arr, 1))
	{
		msg = __FUNCTION__;		msg += " - FAILED";
	}

	std::cout << msg << std::endl;
	free_arr(arr);
}
// Массив одинаковых элементов
void _same_test()
{
	std::string msg;
	msg = __FUNCTION__;		msg += " - OK";

	int n = 10;
	arr_t arr = create_arr(n);
	for (int i = 0; i < n; i++)
		arr[i] = 42;

	if (!_cmp_funcs(arr, n))
	{
		msg = __FUNCTION__;		msg += " - FAILED";
	}

	std::cout << msg << std::endl;
	free_arr(arr);
}
// Отсортированный массив
void _sorted_test()
{
	std::string msg;
	msg = __FUNCTION__;		msg += " - OK";

	int n = 100;
	arr_t arr = random_arr(n);
	std::sort(arr, arr + n);

	if (!_cmp_funcs(arr, n))
	{
		msg = __FUNCTION__;		msg += " - FAILED";
	}

	std::cout << msg << std::endl;
	free_arr(arr);
}
//  Отсортированный в обратном порядке массив
void _reverce_sorted_test()
{
	std::string msg;
	msg = __FUNCTION__;		msg += " - OK";

	int n = 100;
	arr_t arr = random_arr(n);
	std::sort(arr, arr + n);
	std::reverse(arr, arr + n);

	if (!_cmp_funcs(arr, n))
	{
		msg = __FUNCTION__;		msg += " - FAILED";
	}

	std::cout << msg << std::endl;
	free_arr(arr);
}

void run_tests()
{
	_size_one_test();
	_same_test();
	_sorted_test();
	_reverce_sorted_test();
}