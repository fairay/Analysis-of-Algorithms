#ifndef PRIMES_H
#define PRIMES_H

#include <set>
#include <thread>
#include <mutex>
#include <vector>
#include <math.h>

using n_t = size_t;

std::set<n_t> find_primes(n_t max_n, int thread_n);

#endif // PRIMES_H
