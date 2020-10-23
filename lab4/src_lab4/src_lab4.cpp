#include <iostream>
#include <vector>
#include <memory>

#include <mutex>
#include "timer_.h"
#include "tests.h"
#include "std_mul.h"

using namespace std;

void test_input(mult_f f, int thread_n)
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

    mat_t c = f(a, b, m, n, q, thread_n);
    cout << "\nРезультирующая матрица С[MxQ]\n";
    print_mat(c, m, q);

    free_mat(&a, m, n);
    free_mat(&b, n, q);
    free_mat(&c, m, q);
}

void test_time(mult_f f, int n, int thread_n)
{
    mat_t a = random_matrix(n, n);
    mat_t b = random_matrix(n, n);
    mat_t c;

    int count = 0;
    start_counter();
    while (get_counter() < 3.0 * 1000) {
        c = f(a, b, n, n, n, thread_n);
        free_mat(&c, n, n);
        count++;
    }
    double t = get_counter() / 1000;

    start_counter();
    for (int i = 0; i < count; i++)
    {
        c = create_mat(n, n);
        free_mat(&c, n, n);
    }
    t -= get_counter() / 1000;

    cout << "Выполнено " << count << " операций за " << t << " секунд" << endl;
    cout << "Время: " << t / count << endl;

    free_mat(&a, n, n);
    free_mat(&b, n, n);
}

void experiments_series(vector<int>& a)
{
    int n = 500;
    cout << "Размер матриц " << n << "x" << n << endl;
    for (int i : a)
    {
        cout << "=======================================" << endl;
        cout << "\nКоличество потоков: " << i << endl;

        cout << "Стандартное умножение(многопоточно по строкам)" << endl;
        test_time(std_mult_thread1, n, i);
        cout << "Стандартное умножение(многопоточно по столбцам)" << endl;
        test_time(std_mult_thread2, n, i);

        cout << "\nСтандартное умножение(многопоточно по строкам)" << endl;
        test_time(std_mult_thread1, n, i);
        cout << "Стандартное умножение(многопоточно по столбцам)" << endl;
        test_time(std_mult_thread2, n, i);

        cout << "=======================================" << endl;
    }
    cout << "Стандартное умножение (однопоточно)" << endl;
    test_time(std_mult, n, 1);
}


int main(void)
{
    mult_f f_arr[] = { std_mult, std_mult_thread1, std_mult_thread2 };
    srand(static_cast<unsigned int>(time(0)));
    setlocale(LC_ALL, "Russian");

    run_tests();

    vector<int> a{ 1, 2, 4, 8, 16, 32 };
    experiments_series(a);
    experiments_series(a);
    experiments_series(a);

    size_t f_n;
    int thread_n = 1;
    cout << "\nПрограмма для умножения матриц" << endl;
    cout << "Выберите алгоритм:\n\
0) Стандартное умножение\n\
1) Стандартное умножение (многопоточно по строкам)\n\
2) Стандартное умножение (многопоточно по столбцам)" << endl;

    cin >> f_n;

    if (f_n) {
        cout << "\nВведите число потоков: ";
        cin >> thread_n;
    }

    test_input(f_arr[f_n], thread_n);

    return 0;
}