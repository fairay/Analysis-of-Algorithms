#include <iostream>
#include <time.h>

#include "graph.h"

using namespace std;

void best_config(const len_matrix& m)
{
    path_t min_path;
    len_t min_len = 1e5;
    double a1, b1, ro1;
    for (double a = 0; a < 1; a+=0.1)
    {
        double b = 1 - a;
        for (double ro = 0; ro < 1; ro += 0.095)
        {
            path_t p = ant_search(m, a, b, ro, 100, 30);
            len_t len = path_len(m, p);
            printf("%.1lf %.1lf %.1lf : %.2lf\n", a, b, ro, len);
            if (min_len > len)
            {
                min_path = p;
                min_len = len;
                a1 = a; b1 = b; ro1 = ro;
            }
        }
        printf("\n");
    }

    printf("%.1lf %.1lf %.1lf : %.2lf\n", a1, b1, ro1, min_len);
    print_path(min_path);
}

int main()
{
    srand(static_cast<unsigned int>(time(0)));
    setlocale(LC_ALL, "Russian");

    len_matrix m = random_matrix(10, 1, 10, 0.5);
    print_matrix(m);

    best_config(m);

    len_t len = 0;
    path_t path = brute_force(m, len);
    cout << "Path len: " << len << endl;
    print_path(path);

    path = ant_search(m, 0.3, 0.7, 0.7, 20, 30);
    cout << "Path len: " << path_len(m, path) << endl;
    print_path(path);
}
