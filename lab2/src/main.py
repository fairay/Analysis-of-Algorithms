from classic import *
from winograd import *

import random
import time

f_arr = [classic_mult, winograd_mult]


def print_matrix(a):
    for row in a:
        print('\t'.join(map(str, row)))


def random_matrix(m, n):
    c = [[0] * n for i in range(m)]
    for i in range(m):
        for j in range(n):
            c[i][j] = random.randint(-10, 10)
    return c


def test_input(f):
    print("Умножение матрицы A[MxN], B[NxQ]")
    m, n, q = map(int, input("Введите размеры M, N, Q: ").split())
    a = [0] * m
    b = [0] * n

    print("Введите матрицу A:")
    for i in range(m):
        a[i] = list(map(int, input().split()))
        if len(a[i]) != n: return

    print("\nВведите матрицу B:")
    for i in range(n):
        b[i] = list(map(int, input().split()))
        if len(b[i]) != q: return

    c = f(a, b, m, n, q)
    print("\nРезультирующая матрица С[MxQ]")
    print_matrix(c)


def test_time(func, n):
    print("\nРазмер матрицы:", n)
    a = random_matrix(n, n)
    b = random_matrix(n, n)

    begin_t = time.process_time()
    count = 0
    while time.process_time() - begin_t < 1.0:
        func(a, b, n, n, n)
        count += 1

    t = time.process_time() - begin_t
    print("Выполнено {:} операций за {:} секунд".format(count, t))
    print("Время: {:7.4} секунд".format(t / count))


def main():
    print("Программа для умножения матриц\n")
    print(
        "Выберете алгоритм:\n"
        "1) Классический\n"
        "2) Винограда")
    alg_n = int(input())
    if alg_n < 1 or alg_n > len(f_arr):
        print("Ошибка: Неизвестный алгоритм")
        return
    f = f_arr[alg_n - 1]

    test_input(f)


if __name__ == '__main__':
    test_time(winograd_mult, 300)
    # main()
