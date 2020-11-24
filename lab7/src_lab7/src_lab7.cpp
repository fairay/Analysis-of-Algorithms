#include <iostream>
#include <fstream>

#include "tests.h"
#include "timer_.h"
#include "searches.h"

using namespace std;

rec_arr scan_file(string f_name, size_t rec_n)
{
    rec_arr arr;
    ifstream f_in(f_name);
    if (!f_in.is_open())
        return arr;

    for (int i = 0; i < rec_n; i++)
    {
        rec_t temp_rec;

        f_in >> temp_rec.key >> temp_rec.val;
        arr.push_back(temp_rec);
    }

    f_in.close();
    return arr;
}

void test_time1(rec_arr& arr)
{
    cout << "Поиск полным перебором:" << endl;
    double min_t = 1E9;
    double max_t = 0;
    double sum_t = 0;

    for (int i = 0; i < arr.size(); i++)
    {
        size_t key = arr[i].key;
        int count = 0;
        start_counter();
        while (get_counter() < 0.02 * 1000) 
        {
            full_search(arr, key);
            count++;
        }
        double t = get_counter() / 1000 / count;
        sum_t += t;
        min_t = min(t, min_t);
        max_t = max(t, max_t);
    }

    int count = 0;
    start_counter();
    while (get_counter() < 0.1 * 1000)
    {
        full_search(arr, 51);
        count++;
    }
    double mis_t = get_counter() / 1000 / count;

    cout << "Среднее время:\t" << sum_t / arr.size() << endl;
    cout << "Минимальное время:\t" << min_t << endl;
    cout << "Максимальное время:\t" << max_t << endl;
    cout << "Несуществующий ключ:\t" << mis_t << endl;
}
void test_time2(rec_arr& arr)
{
    cout << "Бинарный поиск:" << endl;
    sort_arr(arr);
    double min_t = 1E9;
    double max_t = 0;
    double sum_t = 0;

    for (int i = 0; i < arr.size(); i++)
    {
        size_t key = arr[i].key;
        int count = 0;
        start_counter();
        while (get_counter() < 0.02 * 1000)
        {
            binary_search(arr, key);
            count++;
        }
        double t = get_counter() / 1000 / count;
        // cout << i << " : " << t << endl;
        sum_t += t;
        min_t = min(t, min_t);
        max_t = max(t, max_t);
    }

    int count = 0;
    start_counter();
    while (get_counter() < 0.1 * 1000)
    {
        binary_search(arr, 51);
        count++;
    }
    double mis_t = get_counter() / 1000 / count;

    cout << "Среднее время:\t" << sum_t / arr.size() << endl;
    cout << "Минимальное время:\t" << min_t << endl;
    cout << "Максимальное время:\t" << max_t << endl;
    cout << "Несуществующий ключ:\t" << mis_t << endl;
}
void test_time3(rec_arr& arr)
{
    cout << "Сегментный поиск:" << endl;
    seg_arr sarr = split_arr(arr);
    double min_t = 1E9;
    double max_t = 0;
    double sum_t = 0;

    for (int i = 0; i < arr.size(); i++)
    {
        size_t key = arr[i].key;
        int count = 0;
        start_counter();
        while (get_counter() < 0.02 * 1000)
        {
            segment_search(sarr, key);
            count++;
        }
        double t = get_counter() / 1000 / count;
        // cout << i << " : " << t << endl;
        sum_t += t;
        min_t = min(t, min_t);
        max_t = max(t, max_t);
    }

    int count = 0;
    start_counter();
    while (get_counter() < 0.1 * 1000)
    {
        segment_search(sarr, 51);
        count++;
    }
    double mis_t = get_counter() / 1000 / count;

    cout << "Среднее время:\t" << sum_t / arr.size() << endl;
    cout << "Минимальное время:\t" << min_t << endl;
    cout << "Максимальное время:\t" << max_t << endl;
    cout << "Несуществующий ключ:\t" << mis_t << endl;
}

int main(void)
{
    setlocale(LC_ALL, "Russian");
    rec_arr arr = scan_file("../data.txt", 100);
    run_tests(arr);

    arr = scan_file("../data.txt", 1500);

    printf("Выберете действие:\n");
    printf("1) Поиск полным перебором\n");
    printf("2) Бинарный поиск\n");
    printf("3) Поиск по сегментам\n");
    printf("4) Замер времени\n");

    size_t choose;
    cin >> choose;

    if (1 <= choose && choose <= 3)
    {
        size_t key;
        test_f test_f_arr[3] = { test1, test2, test3 };

        cout << "Введите номер карты: ";
        cin >> key;
        rec_t res = test_f_arr[choose - 1](arr, key);

        if (res.key)
            printf("Найдена карта № %Iu CVC:%03u\n", res.key, res.val);
        else
            printf("Карта не найдена\n");
    }
    else if (choose == 4)
    {
        test_time1(arr);
        test_time2(arr);
        test_time3(arr);
    }
    else
        printf("Неизвестное действие");

    rec_t res;
    size_t key = arr[101].key;
    seg_arr sarr = split_arr(arr);
    res = segment_search(sarr, key);
    cout << "Result:" << res.key << " = " << res.val << endl;

    return 0;
}
