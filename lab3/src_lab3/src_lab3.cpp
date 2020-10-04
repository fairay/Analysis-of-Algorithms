#include <iostream>
#include <time.h>
#include <locale.h>
#include <windows.h>
#include <vector>

#include "bubble.h"
#include "merge.h"
#include "radix.h"

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

    free_arr(arr);
}

void test_time(sort_func f, int n)
{
    arr_t arr = random_arr(n);

    int count = 0;
    start_counter();
    while (get_counter() < 3.0 * 1000) 
    {
        fill_random_arr(arr, n, -10000, 10000);
        f(arr, n);
        count++;
    }
    double t = get_counter() / 1000;

    start_counter();
    for (int i = 0; i < count; i++)
        fill_random_arr(arr, n, -10000, 10000);
    t -= get_counter() / 1000;

    cout << "Выполнено " << count << " операций за " << t << " секунд" << endl;
    cout << "Время: " << t / count << endl;

    free_arr(arr);
}

void experiments_series(vector<int>& a)
{
    cout << "\n------------------------------------------------";
    for (int i : a)
    {
        cout << "\n\nРазмер массива: " << i << endl;

        cout << "\nСортировка пузырьком:" << endl;
        // test_time(bubble_sort, i);

        cout << "\nПоразрядная сортировка:" << endl;
        test_time(radix_sort, i);

        cout << "\nСортировка слиянием:" << endl;
        test_time(merge_sort, i);
    }
}

int main()
{
    srand(static_cast<unsigned int>(time(0)));
    setlocale(LC_ALL, "Russian");

    run_tests();
    vector<int> a{ 20, int(1e2), int(1e3), int(1e4), int(1e6)};
    // vector<int> a{ int(1e5) };
    experiments_series(a);
    experiments_series(a);
    experiments_series(a);
    /*experiments_series(a);
    experiments_series(a);
    experiments_series(a);
    experiments_series(a);*/

    cout << "Программа для сортировки массива:" << endl;
    cout << "\nВыберите алгоритм:" << endl;
    cout << "1) Пузырьком" << endl;
    cout << "2) Поразрядно" << endl;
    cout << "3) Слиянием" << endl;

    int n;
    cin >> n;

    switch (n)
    {
    case 1:
        test_input(bubble_sort);
        break;
    case 2:
        test_input(radix_sort);
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