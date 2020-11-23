#include "tests.h"

using namespace std;

rec_t test1(rec_arr& arr, size_t key)
{
    return full_search(arr, key);
}
rec_t test2(rec_arr& arr, size_t key)
{
    sort_arr(arr);
    return binary_search(arr, key);
}
rec_t test3(rec_arr& arr, size_t key)
{
    seg_arr sarr = split_arr(arr);
    return segment_search(sarr, key);
}


bool _cmp_rec(const rec_t& r1, const rec_t& r2)
{
	return (r1.key == r2.key) && (r1.val == r2.val);
}

bool _test_all(rec_arr& arr, size_t key, rec_t res)
{
    test_f test_f_arr[3] = { test1, test2, test3 };
    rec_t test_out;

    for (int i = 0; i < 3; i++)
    {
        test_out = test_f_arr[i](arr, key);
        if (!_cmp_rec(test_out, res))
            return false;
    }
    return true;
}

void _find_missing(rec_arr& arr)
{
    if (_test_all(arr, 1012, null_rec()))
        cout << __FUNCTION__ << " - OK\n";
    else
        cout << __FUNCTION__ << " - FAILED\n";
}
void _find_first(rec_arr& arr)
{
    if (_test_all(arr, arr[0].key, arr[0]))
        cout << __FUNCTION__ << " - OK\n";
    else
        cout << __FUNCTION__ << " - FAILED\n";
}
void _find_last(rec_arr& arr)
{
    size_t last = arr.size() - 1;
    if (_test_all(arr, arr[last].key, arr[last]))
        cout << __FUNCTION__ << " - OK\n";
    else
        cout << __FUNCTION__ << " - FAILED\n";
}

void run_tests(rec_arr& arr)
{
    cout << "Running tests:" << endl;
    _find_missing(arr);
    _find_first(arr);
    _find_last(arr);
    cout << endl;
}