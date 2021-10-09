#include "tests.h"
// Сравнение результата умножения разными способами
bool _cmp_funcs(mat_t a, mat_t b, int m, int n, int q)
{
	mat_t c1 = classic_mult(a, b, m, n, q);
	mat_t c2 = winograd_mult(a, b, m, n, q);
	bool flag = cmp_matrix(c1, c2, m, q);
	free_mat(&c1, m, q);
	free_mat(&c2, m, q);
	return flag;
}

// Матрицы с размером 1x1
void _size_one_test()
{
	mat_t a = create_mat(1, 1);
	mat_t b = create_mat(1, 1);

	a[0][0] = 0;
	b[0][0] = 1;
	if (!_cmp_funcs(a, b, 1, 1, 1))
	{
		std::cout << __FUNCTION__ << " - FAILED\n";
		return;
	}

	a[0][0] = 3;
	b[0][0] = 4;
	if (!_cmp_funcs(a, b, 1, 1, 1))
	{
		std::cout << __FUNCTION__ << " - FAILED\n";
		return;
	}

	free_mat(&a, 1, 1);
	free_mat(&b, 1, 1);

	std::cout << __FUNCTION__ << " - OK\n";
}
// Нулевые матрицы
void _void_test()
{
	mat_t a = random_matrix(3, 2);
	mat_t b = void_matrix(2, 1);
	if (!_cmp_funcs(a, b, 3, 2, 1))
	{
		std::cout << __FUNCTION__ << " - FAILED\n";
		return;
	}
	free_mat(&a, 3, 2);
	a = void_matrix(3, 2);
	if (!_cmp_funcs(a, b, 3, 2, 1))
	{
		std::cout << __FUNCTION__ << " - FAILED\n";
		return;
	}
	free_mat(&a, 3, 2);
	free_mat(&b, 2, 1);
	std::cout << __FUNCTION__ << " - OK\n";
}
// Квадратные матрицы
void _square_test()
{
	mat_t a = random_matrix(4, 4);
	mat_t b = random_matrix(4, 4);

	if (!_cmp_funcs(a, b, 4, 4, 4))
	{
		std::cout << __FUNCTION__ << " - FAILED\n";
		return;
	}

	free_mat(&a, 4, 4);
	free_mat(&b, 4, 4);
	std::cout << __FUNCTION__ << " - OK\n";
}
// Матрицы нечётного размера
void _odd_test()
{
	mat_t a = random_matrix(5, 3);
	mat_t b = random_matrix(3, 7);

	if (!_cmp_funcs(a, b, 5, 3, 7))
	{
		std::cout << __FUNCTION__ << " - FAILED\n";
		return;
	}

	free_mat(&a, 5, 3);
	free_mat(&b, 3, 7);
	std::cout << __FUNCTION__ << " - OK\n";
}

void run_tests()
{
	_size_one_test();
	_void_test();
	_square_test();
	_odd_test();
}