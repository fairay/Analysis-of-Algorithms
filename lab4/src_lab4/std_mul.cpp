#include "std_mul.h"

#pragma optimize( "", off )
#include <thread>
#include <mutex>

using namespace std;
std::mutex mtx;

mat_t std_mult(mat_t a, mat_t b, int m, int n, int q, int)
{
    mat_t c = create_mat(m, q);

    for (int i = 0; i < m; i++)
        for (int j = 0; j < q; j++)
        {
            double res = 0;
            for (int k = 0; k < n; k++)
                res += a[i][k] * b[k][j];
            c[i][j] = res;
        }
    return c;
}



void _mult_thread(mat_t& c, mat_t& a, mat_t& b, int m, int n, int q, int start, int step)
{
    for (int i = start; i < m; i+= step)
        for (int j = 0; j < q; j++)
        {
            double res = 0;
            for (int k = 0; k < n; k++)
                res += a[i][k] * b[k][j];
            mtx.lock();
            c[i][j] = res;
            mtx.unlock();
        }
}

mat_t std_mult_thread1(mat_t a, mat_t b, int m, int n, int q, int thread_n)
{
    mat_t c = create_mat(m, q);

    vector<thread> thread_arr;
    for (int i = 0; i < thread_n; i++)
        thread_arr.push_back(thread(_mult_thread, ref(c), ref(a), ref(b),
                                    m, n, q, i, thread_n));

    for (int i = 0; i < thread_n; i++)
        thread_arr[i].join();

    return c;
}



void _mult_thread2(mat_t& c, mat_t& a, mat_t& b, int m, int n, int q, int start, int step)
{
    for (int i = 0; i < m; i++)
        for (int j = start; j < q; j+=step)
        {
            double res = 0;
            for (int k = 0; k < n; k++)
                res += a[i][k] * b[k][j];
            mtx.lock();
            c[i][j] = res;
            mtx.unlock();
        }
}

mat_t std_mult_thread2(mat_t a, mat_t b, int m, int n, int q, int thread_n)
{
    mat_t c = create_mat(m, q);

    vector<thread> thread_arr;
    for (int i = 0; i < thread_n; i++)
        thread_arr.push_back(thread(_mult_thread2, ref(c), ref(a), ref(b),
                                    m, n, q, i, thread_n));

    for (int i = 0; i < thread_n; i++)
        thread_arr[i].join();

    return c;
}


#pragma optimize( "", on )