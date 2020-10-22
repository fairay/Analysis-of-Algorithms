#ifndef MATRIX_H
#define MATRIX_H

#include <memory>
#include <iostream>
#include <random>

constexpr double EPS = 1e-5;
typedef double* arr_t;
typedef double** mat_t;
using mult_f = mat_t (*)(mat_t a, mat_t b, int m, int n, int q, int thread_n);

mat_t create_mat(int m, int n);
void print_mat(mat_t mat, int m, int n);
void fill_mat(mat_t mat, int m, int n);
void free_mat(mat_t* mat, int m, int n);

mat_t random_matrix(int m, int n);
mat_t void_matrix(int m, int n);
bool cmp_matrix(mat_t a, mat_t b, int m, int n);

arr_t create_arr(int n);
void free_arr(arr_t* arr);

#endif // MATRIX_H

