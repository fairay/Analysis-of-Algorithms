def calcMi(a, m, n):
    mi = [0] * m
    for i in range(m):
        k = 0
        while k < n:
            mi[i] += a[i][k] * a[i][k + 1]
            k += 2
        # for k in range(int(n/2)):
        #     mi[i] += a[i][2*k] * a[i][2*k+1]
    return mi


def calcMj(b, n, q):
    mj = [0] * q
    for j in range(q):
        k = 0
        while k < n:
            mj[j] += b[k][j] * b[k + 1][j]
            k += 2
        # for k in range(int(n/2)):
        #     mj[j] += b[2*k][j] * b[2*k+1][j]
    return mj


def winograd_mult(a, b, m, n, q):
    c = [[0] * q for i in range(m)]
    mi = calcMi(a, m, n)
    mj = calcMj(b, n, q)

    for i in range(m):
        j = 0
        while j < q:

            c[i][j] = -(mi[i] + mj[j])
            k = 0
            while k < n:
                c[i][j] += (a[i][k] + b[k + 1][j]) * \
                           (a[i][k + 1] + b[k][j])
                k += 2
            # for k in range(0, n):
                # c[i][j] += (a[i][2*k] + b[2*k+1][j]) *\
                #            (a[i][2*k+1] + b[2*k][j])
            j += 1

    if n % 2 == 1:
        for i in range(m):
            for j in range(q):
                c[i][j] += a[i][n-1] * b[n-1][j]

    return c


"""

def calcMi(a, m, n):
    mi = [0] * m
    for i in range(m):
        for k in range(int(n/2)):
            mi[i] += a[i][2*k] * a[i][2*k+1]
    return mi


def calcMj(b, n, q):
    mj = [0] * q
    for j in range(q):
        for k in range(int(n/2)):
            mj[j] += b[2*k][j] * b[2*k+1][j]
    return mj


def winograd_mult(a, b, m, n, q):
    c = [[0] * q for i in range(m)]
    mi = calcMi(a, m, n)
    mj = calcMj(b, n, q)

    for i in range(m):
        for j in range(q):
            c[i][j] = -(mi[i] + mj[j])
            for k in range(0, n, 2):
                c[i][j] += (a[i][2*k] + b[2*k+1][j]) *\
                           (a[i][2*k+1] + b[2*k][j])

    if n % 2 == 1:
        for i in range(m):
            for j in range(q):
                c[i][j] += a[i][n-1] * b[n-1][j]

    return c
    
"""
