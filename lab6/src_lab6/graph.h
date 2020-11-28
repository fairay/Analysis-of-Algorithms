#pragma once

#include <vector>
#include <random>
#include <iostream>
#include <algorithm>

using len_t = double;
using len_matrix = std::vector<std::vector<len_t>>;

using path_t = std::vector<size_t>;

len_matrix random_matrix(size_t n, len_t from, len_t to, double gap_p=0);
void print_matrix(const len_matrix& m);

len_t path_len(const len_matrix& m, const path_t& p);
void print_path(const path_t& p);

path_t brute_force(const len_matrix& m, len_t& len);
path_t ant_search(const len_matrix& m, double a, double b, double ro, size_t max_t, len_t q);
