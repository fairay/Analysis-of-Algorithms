#ifndef CLASSIC_H
#define CLASSIC_H

#include "matrix.h"

mat_t std_mult(mat_t a, mat_t b, int m, int n, int q, int thread_n=1);
mat_t std_mult_thread1(mat_t a, mat_t b, int m, int n, int q, int thread_n);
mat_t std_mult_thread2(mat_t a, mat_t b, int m, int n, int q, int thread_n);

#endif // CLASSIC_H