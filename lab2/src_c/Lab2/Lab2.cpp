#include <iostream>
#include <time.h>
#include <locale.h>
#include <windows.h>
#include <vector>

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

void experiments_series(vector<int> &a)
{
    for (int i : a)
    {
        cout << "\nРазмер матрицы: " << i << endl;

        cout << "Classic" << endl;
        test_time(classic_mult, i);

        cout << "Winograd" << endl;
        test_time(winograd_mult, i);
    }
}

int main()
{
    srand(static_cast<unsigned int>(time(0)));
    setlocale(LC_ALL, "Russian");

    cout << "Программа для умножения матриц:" << endl;
    cout << "\nВыберите алгоритм:" << endl;
    cout << "1) Классический" << endl;
    cout << "2) Винограда" << endl;

    int n;
    cin >> n;

    switch (n)
    {
    case 1:
        test_input(classic_mult);
        break;
    case 2:
        test_input(winograd_mult);
        break;
    default:
        cout << "Некорректный ввод" << endl;
        return -1;
    }

    /*
    run_tests();

    vector<int> a{ 50, 100, 200, 400, 800};
    vector<int> a{ 51, 101, 201, 401, 801 };
    experiments_series(a);
    experiments_series(a);
    */

    return 0;
}
