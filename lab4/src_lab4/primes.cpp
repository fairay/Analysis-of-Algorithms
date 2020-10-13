#include "primes.h"

using namespace std;
std::mutex set_mtx;

inline bool is_prime_n(n_t n)
{
    double max_check = sqrt(n + 1);
    for (n_t i = 2; i < max_check; i++)
        if (n % i == 0)
            return false;
    return true;
}

void thread_proc(set<n_t>& set, n_t start_n, n_t end_n, int step)
{
    for (n_t i = start_n; i <= end_n; i += step)
        if (is_prime_n(i))
        {
            set_mtx.lock();
            set.insert(i);
            set_mtx.unlock();
        }
}

set<n_t> find_primes(n_t max_n, int thread_n)
{
    set<n_t> set;
    vector<thread> thread_arr;

    n_t start_n;
    for (int i = 0; i < thread_n; i++)
    {
        start_n = static_cast<n_t>(i) + 2;
        thread_arr.push_back(thread(thread_proc, ref(set), start_n, max_n, thread_n));
    }

    for (int i = 0; i < thread_n; i++)
        thread_arr[i].join();

    return set;
}
