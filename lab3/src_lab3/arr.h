#ifndef ARR_H
#define ARR_H

#include <iostream>
#include <stdio.h>

typedef int content_t;
typedef content_t* arr_t;
typedef void(*sort_func)(arr_t&, int);

arr_t create_arr(int n);
void print_arr(arr_t arr, int n);
void input_arr(arr_t arr, int n);
void free_arr(arr_t& arr);

arr_t copy_arr(arr_t source, int n);
arr_t random_arr(int n, content_t min_val=0, content_t max_val = -1);
void fill_random_arr(arr_t arr, int n, content_t min_val=0, content_t max_val=-1);
bool is_equal_arr(arr_t arr1, arr_t arr2, int n);

#endif // ARR_H