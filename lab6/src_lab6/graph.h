#pragma once

#include <vector>
#include <random>
#include <iostream>
#include <algorithm>

using len_t = double;
using len_matrix = std::vector<std::vector<len_t>>;

using path_t = std::vector<size_t>;

len_matrix random_matrix(size_t n, len_t from, len_t to, double gap_p=0);
double calculate_q(const len_matrix& m);
void print_matrix(const len_matrix& m);

len_t path_len(const len_matrix& m, const path_t& p);
void print_path(const path_t& p);

path_t brute_force(const len_matrix& m, len_t& len);
using ant_config = struct
{
	double a, b, ro;
	size_t max_t;
	size_t ans_t;
	len_t q;
};
ant_config create_config(double a, double ro, size_t max_t, len_t q);
path_t ant_search(const len_matrix& m, ant_config& conf);
