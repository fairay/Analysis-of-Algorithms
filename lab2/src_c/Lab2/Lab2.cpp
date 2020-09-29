#include <iostream>
#include <time.h>
#include <locale.h>
#include <windows.h>

#include "classic.h"
#include "winograd.h"
#include "tests.h"

using namespace std;

double PCFreq = 0.0;
__int64 CounterStart = 0;

void start_counter()
{
    LARGE_INTEGER li;
    QueryPerformanceFrequency(&li);

    PCFreq = double(li.QuadPart) / 1000.0;

    QueryPerformanceCounter(&li);
    CounterStart = li.QuadPart;
}
double get_counter()
{
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return double(li.QuadPart - CounterStart) / PCFreq;
}

void test_input(mat_t (*f)(mat_t, mat_t, int, int, int))
{
    cout << "Умножение матрицы A[MxN], B[NxQ]\n";
    int m, n, q;
    cout << "Введите размеры M, N, Q: ";
    cin >> m >> n >> q;

    mat_t a = create_mat(m, n);
    mat_t b = create_mat(n, q);
    cout << "Введите матрицу A:\n";
    fill_mat(a, m, n);
    cout << "\nВведите матрицу B:\n";
    fill_mat(b, n, m);

    mat_t c = f(a, b, m, n, q);
    cout << "\nРезультирующая матрица С[MxQ]\n";
    print_mat(c, m, q);

    free_mat(&a, m, n);
    free_mat(&b, n, q);
    free_mat(&c, m, q);
}

void test_time(mat_t(*f)(mat_t, mat_t, int, int, int), int n)
{
    cout << "\nРазмер матрицы: " << n << endl;
    mat_t a = random_matrix(n, n);
    mat_t b = random_matrix(n, n);
    mat_t c;

    int count = 0;
    start_counter();
    while (get_counter() < 3.0 * 1000) {
        c = f(a, b, n, n, n);
        free_mat(&c, n, n);
        count++;
    }

    double t = get_counter() / 1000;
    cout << "Выполнено " << count << " операций за " << t << " секунд" << endl;
    cout << "Время: " << t / count << endl;

    free_mat(&a, n, n);
    free_mat(&b, n, n);
}

int main()
{
    srand(static_cast<unsigned int>(time(0)));
    setlocale(LC_ALL, "Russian");

    run_tests();

    // test_input(winograd_mult);
    test_time(winograd_mult, 500);
    test_time(classic_mult, 500);
    // Результирующая матрица С[MxQ]
        // 30, 00   36, 00   42, 00
        // 66, 00   81, 00   96, 00
        // 102, 00  126, 00  150, 00
    return 0;
}
