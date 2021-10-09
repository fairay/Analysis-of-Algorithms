#include "classic.h"

#pragma optimize( "", off )
mat_t classic_mult(mat_t a, mat_t b, int m, int n, int q)
{
    mat_t c = create_mat(m, q);

    for (int i = 0; i < m; i++)
        for (int j = 0; j < q; j++)
        {
            c[i][j] = 0;
            for (int k = 0; k < n; k++)
                c[i][j] += a[i][k] * b[k][j];
        }
    return c;
}
#pragma optimize( "", on )