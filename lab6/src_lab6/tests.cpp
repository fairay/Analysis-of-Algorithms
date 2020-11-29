#include "tests.h"

using namespace std;


bool _no_way()
{
    cout << __FUNCTION__;
    len_t len = 0;
    path_t path;
    len_matrix m = random_matrix(7, 1, 9, 0.99);

    len = 0;
    path = brute_force(m, len);
    if (len || path.size()) return false;

    ant_config cnf = create_config(0.5, 0.5, 20, calculate_q(m));
    path = ant_search(m, cnf);
    if (path.size())    return false;
    return true;
}

bool _same_way()
{
    cout << __FUNCTION__;
    len_t len = 0;
    path_t path;
    len_matrix m = random_matrix(7, 1, 9, 0.99);

    len = 0;
    path = brute_force(m, len);
    if (len || path.size()) return false;

    ant_config cnf = create_config(0.5, 0.5, 20, calculate_q(m));
    path = ant_search(m, cnf);
    if (path.size())    return false;
    return true;
}

bool _size_two()
{
    cout << __FUNCTION__;
    len_t len = 0;
    path_t path;
    len_matrix m = random_matrix(2, 1, 9);

    len_t ans = m[1][0] + m[0][1];
    len = 0;
    path = brute_force(m, len);
    if (len != ans || path.size() != 3) return false;

    ant_config cnf = create_config(0.5, 0.5, 20, calculate_q(m));
    path = ant_search(m, cnf);
    if (path.size())    return false;
    return true;
}



using test_f = bool(*)(void);
void run_tests()
{
    cout << "Running tests:" << endl;

    test_f f_arr[] = { _no_way, _same_way, _size_two, _rnd_matrix };

    for (size_t i = 0; i < 4; i++)
    {
        if (f_arr[i])
            cout << " - PASSED\n";
        else
            cout << " - FAILED\n";
    }



    cout << endl;
}