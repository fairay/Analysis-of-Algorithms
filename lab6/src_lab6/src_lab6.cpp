#include <iostream>
#include <time.h>

#include "graph.h"
#include "tests.h"
#include "timer_.h"

using namespace std;

void test_time(const vector<size_t>& size_arr)
{
    cout << "Измерение времени, муравьиный алгоритм" << endl;
    ant_config cnf = create_config(0.8, 0.6, 35, 2000);
    for (size_t m_s : size_arr)
    {
        cout << "Размер " << m_s << ":\t";
        len_matrix m = random_matrix(m_s, 200, 400, 0.0);
        cnf.q = calculate_q(m);

        int count = 0;
        start_counter();
        while (get_counter() < 3 * 1000)
        {
            ant_search(m, cnf);
            count++;
        }
        double t = get_counter() / 1000 / count;
        cout << t << endl;
    }
}

void best_config(const len_matrix& m, len_t q, len_t perfect_len)
{
    len_t min_len = 1e5;
    ant_config best_cnf;
    best_cnf.ans_t = q * 1000;
    for (double a = 0; a <= 1; a+=0.1)
    {
        double b = 1 - a;
        for (double ro = 0; ro <= 1; ro += 0.2)
        {
            ant_config cnf = create_config(a, ro, 35, q);
            len_t local_min = q * 1000;
            for (int i=0; i<3; i++)
            {
                path_t p = ant_search(m, cnf);
                len_t len = path_len(m, p);
                local_min = min(len, local_min);
            }
            // printf("%.1lf %.1lf %.1lf %zd: %.2lf %.2lf\n", a, b, ro, cnf.max_t, local_min, local_min - perfect_len);
            printf("%.1lf & %.1lf & %zd & %.0lf & %.0lf \t \\\\ \n", a, ro, cnf.max_t, local_min, local_min - perfect_len);
            if (min_len > local_min || (fabs(min_len - local_min) < 1e-5 && cnf.ans_t < best_cnf.ans_t))
            {
                min_len = local_min;
                best_cnf = cnf;
            }
        }
        printf("\\hline\n");
    }

    printf("%.1lf %.1lf %.1lf : %.2lf\n", best_cnf.a, best_cnf.b, best_cnf.ro, min_len);
}

int main()
{
    srand(static_cast<unsigned int>(time(0)));
    setlocale(LC_ALL, "Russian");

    run_tests();

    test_time(vector<size_t>{10, 20, 40, 80, 160});

    return 0;
    len_matrix m = random_matrix(10, 200, 400, 0.0);
    print_matrix(m);

    len_t len = 0;
    path_t path = brute_force(m, len);
    cout << "Path len: " << len << endl;
    print_path(path);

    best_config(m, calculate_q(m), len);


    /*path = ant_search(m, 0.3, 0.7, 0.7, 20, 30);
    cout << "Path len: " << path_len(m, path) << endl;
    print_path(path);*/
}
