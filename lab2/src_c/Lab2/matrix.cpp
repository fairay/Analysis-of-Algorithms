#include "matrix.h"

mat_t create_mat(int m, int n)
{
	mat_t mat = new double* [m];
	for (int i = 0; i < m; i++)
		mat[i] = new double[n];
	return mat;
}

void print_mat(mat_t mat, int m, int n)
{
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
			printf("%.2lf\t", mat[i][j]);
		printf("\n");
	}
}

void fill_mat(mat_t mat, int m, int n)
{
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			std::cin >> mat[i][j];
}

void free_mat(mat_t* mat, int m, int n)
{
	for (int i = 0; i < m; i++)
		delete (*mat)[i];
	delete (*mat);
	*mat = nullptr;
}


mat_t random_matrix(int m, int n) 
{
	mat_t mat = create_mat(m, n);
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			mat[i][j] = rand() % 20 - 10;
	return mat;
}

mat_t void_matrix(int m, int n)
{
	mat_t mat = create_mat(m, n);
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			mat[i][j] = 0;
	return mat;
}

bool cmp_matrix(mat_t a, mat_t b, int m, int n)
{
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			if (fabs(a[i][j] - b[i][j]) > EPS)
				return false;
	return true;
}


arr_t create_arr(int n)
{
	return new double[n];
}
void free_arr(arr_t* arr)
{
	delete *arr;
	*arr = nullptr;
}