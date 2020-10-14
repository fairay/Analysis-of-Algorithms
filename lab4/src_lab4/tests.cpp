#include "tests.h"

using namespace std;

// Сравнение множеств
bool cmp_sets(vector<set<n_t>>& all_results)
{
	int res_size = all_results.size();
	for (int i = 0; i < res_size -1; i++)
		if (all_results[i].size() != all_results[i + 1].size())
			return false;

	for (auto n : all_results[0])
		for (int i = 1; i < res_size; i++)
			all_results[i].erase(n);
	all_results[0].clear();

	for (int i = 0; i < res_size-1; i++)
		if (all_results[i].size() != all_results[i + 1].size())
			return false;
	return true;
}

// Сравнение разультата работы при разном количестве потоков
void _test_threads(void)
{
	std::string msg;
	msg = __FUNCTION__;		msg += " - OK";

	n_t max_n = 1000;
	vector<set<n_t>> all_results;

	for (int i = 0; i < 20; i++)
		all_results.push_back(find_primes(max_n, i+1));

	if (!cmp_sets(all_results)) 
	{
		msg = __FUNCTION__;		msg += " - FAILED";
	}

	std::cout << msg << std::endl;
}

// Тест при максимальном числе = 2
void _test_2(void)
{
	std::string msg;
	msg = __FUNCTION__;		msg += " - OK";

	vector<set<n_t>> all_results;

	all_results.push_back(set<n_t>{2});
	all_results.push_back(find_primes(2, 1));

	if (!cmp_sets(all_results))
	{
		msg = __FUNCTION__;		msg += " - FAILED";
	}

	std::cout << msg << std::endl;
}

// Тест при максимальном числе = 200
void _test_200(void)
{
	std::string msg;
	msg = __FUNCTION__;		msg += " - OK";

	vector<set<n_t>> all_results;

	all_results.push_back(set<n_t>{2, 3, 5, 7, 11, 13, 17, 19, 23,
		29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89,
		97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151,
		157, 163, 167, 173, 179, 181, 191, 193, 197, 199});
	all_results.push_back(find_primes(200, 1));

	if (!cmp_sets(all_results))
	{
		msg = __FUNCTION__;		msg += " - FAILED";
	}

	std::cout << msg << std::endl;
}

void run_tests()
{
	_test_threads();
	_test_2();
	_test_200();
}