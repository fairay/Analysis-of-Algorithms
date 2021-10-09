def classic_mult(a, b, m, n, q):
    c = [[0] * q for i in range(m)]
    for i in range(m):
        for j in range(q):
            for k in range(n):
                c[i][j] += a[i][k]*b[k][j]
    return c

