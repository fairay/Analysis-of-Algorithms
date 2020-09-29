#include "winograd.h"

#pragma optimize( "", off )
arr_t calc_mi(mat_t a, int m, int n)
{
	arr_t mi = create_arr(m);
	for (int i = 0; i < m; i++)
	{
		mi[i] = 0;
		for (int k = 1; k < n; k += 2)
			mi[i] += a[i][k] * a[i][k - 1];
	}
	return mi;
}

arr_t calc_mj(mat_t b, int n, int q)
{
	arr_t mj = create_arr(q);
	for (int j = 0; j < q; j++)
	{
		double mjj = 0; 
		for (int k = 1; k < n; k += 2)
			mjj += b[k][j] * b[k - 1][j];
		mj[j] = mjj;
	}
	return mj;
}

mat_t winograd_mult(mat_t a, mat_t b, int m, int n, int q)
{
	mat_t c = create_mat(m, q);
	arr_t mj = calc_mj(b, n, q);

	for (int i = 0; i < m; i++)
	{
		double mi_i = 0;
		for (int k = 1; k < n; k += 2)
			mi_i += a[i][k] * a[i][k - 1];

		for (int j = 0; j < q; j++)
		{
			double cij = -(mi_i + mj[j]);
			int k = 1;
			int k1 = 0;
			for (; k < n; k += 2, k1 += 2)
				cij +=	(a[i][k] + b[k1][j]) *
						(a[i][k1] + b[k][j]);
			c[i][j] = cij;
		}
	}

	if (n % 2)
	{
		int n_minus1 = n - 1;
		for (int i = 0; i < m; i++)
			for (int j = 0; j < q; j++)
				c[i][j] += a[i][n_minus1] * b[n_minus1][j];
	}

	free_arr(&mj);
	return c;
}


/*
arr_t calc_mi(mat_t a, int m, int n)
{
	arr_t mi = create_arr(m);
	for (int i = 0; i < m; i++)
	{
		mi[i] = 0;
		for (int k = 0; k < n / 2; k++)
			mi[i] += a[i][2*k] * a[i][2*k + 1];
	}
	return mi;
}

arr_t calc_mj(mat_t b, int n, int q)
{
	arr_t mj = create_arr(q);
	for (int j = 0; j < q; j++)
	{
		mj[j] = 0;
		for (int k = 0; k < n / 2; k++)
			mj[j] += b[2*k][j] * b[2*k + 1][j];
	}
	return mj;
}

mat_t winograd_mult(mat_t a, mat_t b, int m, int n, int q)
{
	mat_t c = create_mat(m, q);
	arr_t mi = calc_mi(a, m, n);
	arr_t mj = calc_mj(b, n, q);

	for (int i = 0; i < m; i++)
		for (int j = 0; j < q; j++)
		{
			c[i][j] = -(mi[i] + mj[j]);
			for (int k = 0; k < n / 2; k++)
				c[i][j] +=	(a[i][2*k] + b[2*k + 1][j]) *
							(a[i][2*k + 1] + b[2*k][j]);
		}

	if (n % 2)
		for (int i = 0; i < m; i++)
			for (int j = 0; j < q; j++)
				c[i][j] += a[i][n-1] * b[n-1][j];

	return c;
}
*/

#pragma optimize( "", on )