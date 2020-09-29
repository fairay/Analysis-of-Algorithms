#ifndef WINOGRAD_H
#define WINOGRAD_H

#include "matrix.h"

mat_t winograd_mult(mat_t a, mat_t b, int m, int n, int q);

#endif // !WINOGRAD_H
