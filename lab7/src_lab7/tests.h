#ifndef TESTS_H
#define TESTS_H

#include "searches.h"
#include <iostream>

using test_f = rec_t(*)(rec_arr& arr, size_t key);
rec_t test1(rec_arr& arr, size_t key);
rec_t test2(rec_arr& arr, size_t key);
rec_t test3(rec_arr& arr, size_t key);

void run_tests(rec_arr& arr);

#endif // TESTS_H
