#include "tests.h"

using namespace std;

// Сравнение работы функций
bool _cmp_funcs(mat_t a, mat_t b, int m, int n, int q, int thread_n)
{
	mat_t c0 = std_mult(a, b, m, n, q, thread_n);
	mat_t c1 = std_mult_thread1(a, b, m, n, q, thread_n);
	mat_t c2 = std_mult_thread2(a, b, m, n, q, thread_n);
	bool flag = cmp_matrix(c0, c1, m, q);
	if (flag)
		flag = cmp_matrix(c1, c2, m, q);
	free_mat(&c0, m, q);
	free_mat(&c1, m, q);
	free_mat(&c2, m, q);
	return flag;
}

// Размер матриц = 1
void _test_size_one()
{
	mat_t a = create_mat(1, 1);
	mat_t b = create_mat(1, 1);

	a[0][0] = 0;
	b[0][0] = 1;
	if (!_cmp_funcs(a, b, 1, 1, 1, 1))
	{
		std::cout << __FUNCTION__ << " - FAILED\n";
		return;
	}

	a[0][0] = 3;
	b[0][0] = 4;
	if (!_cmp_funcs(a, b, 1, 1, 1, 16))
	{
		std::cout << __FUNCTION__ << " - FAILED\n";
		return;
	}

	free_mat(&a, 1, 1);
	free_mat(&b, 1, 1);

	std::cout << __FUNCTION__ << " - OK\n";
}

// Пустые матрицы
void _test_void()
{
	mat_t a = random_matrix(3, 2);
	mat_t b = void_matrix(2, 1);
	if (!_cmp_funcs(a, b, 3, 2, 1, 1))
	{
		std::cout << __FUNCTION__ << " - FAILED\n";
		return;
	}
	free_mat(&a, 3, 2);

	a = void_matrix(3, 2);
	if (!_cmp_funcs(a, b, 3, 2, 1, 1))
	{
		std::cout << __FUNCTION__ << " - FAILED\n";
		return;
	}
	free_mat(&a, 3, 2);
	free_mat(&b, 2, 1);
	std::cout << __FUNCTION__ << " - OK\n";
}

// 
void _test_threads()
{
	mat_t a = random_matrix(50, 50);
	mat_t b = random_matrix(50, 50);
	
	for (int i = 1; i <= 16; i++)
	{
		if (!_cmp_funcs(a, b, 50, 50, 50, i))
		{
			std::cout << __FUNCTION__ << " - FAILED\n";
			break;
		}
	}

	free_mat(&a, 50, 50);
	free_mat(&b, 50, 50);

	std::cout << __FUNCTION__ << " - OK\n";
}

void run_tests()
{
	_test_size_one();
	_test_void();
	_test_threads();
}