#include <iostream>
#include <fstream>


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
        cout << temp_rec.key << " " << temp_rec.val << endl;
        arr.push_back(temp_rec);
    }

    f_in.close();
    return arr;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    rec_arr arr = scan_file("../data.txt", 150);
    cout << arr.size() << endl;

    printf("Выберете действие:\n");
    printf("1) Поиск полным перебором\n");
    printf("2) Бинарный поиск\n");
    printf("3) Поиск по сегментам\n");
    printf("4) Замер времени\n");

    size_t choose;
    cin >> choose;
}
