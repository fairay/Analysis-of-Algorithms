#include <iostream>
#include <time.h>

#include "graph.h"
#include "tests.h"

using namespace std;

void best_config(const len_matrix& m, len_t q)
{
    len_t min_len = 1e5;
    ant_config best_cnf;
    best_cnf.ans_t = q * 1000;
    for (double a = 0; a <= 1; a+=0.1)
    {
        double b = 1 - a;
        for (double ro = 0; ro <= 1; ro += 0.1)
        {
            ant_config cnf = create_config(a, ro, 30, q);
            len_t local_min = q * 1000;
            for (int i=0; i<3; i++)
            {
                path_t p = ant_search(m, cnf);
                len_t len = path_len(m, p);
                local_min = min(len, local_min);
            }
            printf("%.1lf %.1lf %.1lf : %.2lf\n", a, b, ro, local_min);
            if (min_len > local_min || (fabs(min_len - local_min) < 1e-5 && cnf.ans_t < best_cnf.ans_t))
            {
                min_len = local_min;
                best_cnf = cnf;
            }
        }
        printf("\n");
    }

    printf("%.1lf %.1lf %.1lf : %.2lf\n", best_cnf.a, best_cnf.b, best_cnf.ro, min_len);
}

int main()
{
    srand(static_cast<unsigned int>(time(0)));
    setlocale(LC_ALL, "Russian");

    run_tests();

    len_matrix m = random_matrix(10, 1, 100, 0.0);
    print_matrix(m);

    // best_config(m, calculate_q(m));

    len_t len = 0;
    path_t path = brute_force(m, len);
    cout << "Path len: " << len << endl;
    print_path(path);

    /*path = ant_search(m, 0.3, 0.7, 0.7, 20, 30);
    cout << "Path len: " << path_len(m, path) << endl;
    print_path(path);*/
}
