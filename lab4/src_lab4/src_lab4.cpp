#include <iostream>
#include <vector>
#include <memory>

#include "timer_.h"
#include "primes.h"

using namespace std;

void test_time(n_t max_n, int thread_n)
{
    int count = 0;
    start_counter();
    while (get_counter() < 3.0 * 1000)
    {
        find_primes(max_n, thread_n);
        count++;
    }
    double t = get_counter() / 1000;

    cout << "Выполнено " << count << " операций за " << t << " секунд" << endl;
    cout << "Время: " << t / count << endl;
}

void experiments_series(n_t max_n, vector<int>& thread_arr)
{
    cout << "\n------------------------------------------------\n";
    cout << "Размер: " << max_n << endl;
    for (int i : thread_arr)
    {
        cout << "\nЧисло потоков = " << i << endl;
        test_time(max_n, i);
        test_time(max_n, i);
        test_time(max_n, i);
    }
}

int main(void)
{
    srand(static_cast<unsigned int>(time(0)));
    setlocale(LC_ALL, "Russian");

    /*vector<int> a{ 1, 2, 4, 8, 16, 32, 64 };
    experiments_series(1e5, a);
    experiments_series(1e5, a);
    experiments_series(1e5, a);*/

    n_t n_max;
    size_t thread_n;
    cout << "\nПрограмма для поиска множества простых чисел" << endl;
    cout << "Введите максимальное число: ";
    cin >> n_max;

    cout << "\nВведите число потоков: ";
    cin >> thread_n;

    set<n_t> set = find_primes(n_max, thread_n);
    cout << "Результирующее множество: ";
    for (auto i : set)
        cout << i << ", ";

    return 0;
}
