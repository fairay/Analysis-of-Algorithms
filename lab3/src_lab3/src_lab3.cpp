#include <iostream>
#include <time.h>
#include <locale.h>
#include <windows.h>
#include <vector>

#include "bubble.h"
#include "merge.h"

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

void test_input(sort_func f)
{
    cout << "Сортировка массива A[N]" << endl;
    int n;
    cout << "Введите размер N: ";
    cin >> n;

    arr_t arr = create_arr(n);
    cout << "Введите массив А:\n";
    input_arr(arr, n);

    f(arr, n);
    cout << "\nОтсортированный массив:" << endl;
    print_arr(arr, n);

    free_arr(&arr);
}

void test_time(sort_func f, int n)
{
    arr_t arr = random_arr(n);

    int count = 0;
    start_counter();
    while (get_counter() < 3.0 * 1000) {
        fill_random_arr(arr, n);
        f(arr, n);
        count++;
    }
    double t = get_counter() / 1000;

    start_counter();
    for (int i = 0; i < count; i++)
        fill_random_arr(arr, n);
    t -= get_counter() / 1000;

    cout << "Выполнено " << count << " операций за " << t << " секунд" << endl;
    cout << "Время: " << t / count << endl;

    free_arr(&arr);
}

void experiments_series(vector<int>& a)
{
    for (int i : a)
    {
        cout << "\nРазмер матрицы: " << i << endl;

        cout << "Classic" << endl;
        // test_time(classic_mult, i);

        cout << "Winograd" << endl;
        // test_time(winograd_mult, i);
    }
}

int main()
{
    run_tests();

    srand(static_cast<unsigned int>(time(0)));
    setlocale(LC_ALL, "Russian");

    cout << "Программа для сортировки массива:" << endl;
    cout << "\nВыберите алгоритм:" << endl;
    cout << "1) Пузырьком" << endl;
    cout << "2) Расчёской" << endl;
    cout << "3) Слиянием" << endl;

    int n;
    cin >> n;

    switch (n)
    {
    case 1:
        test_input(bubble_sort);
        break;
    case 2:
        // test_input(winograd_mult);
        break;
    case 3:
        test_input(merge_sort);
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