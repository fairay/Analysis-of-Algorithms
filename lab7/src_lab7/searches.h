#ifndef SEARCH_H
#define SEARCH_H

#include <iostream>
#include <vector>

using rec_t = struct
{
    size_t key;         // Card number
    unsigned int val;   // CVC
};
using rec_arr = std::vector<rec_t>;

using rec_seg = struct 
{
    int         key;
    rec_arr     records;
};
using seg_arr = std::vector<rec_seg>;
rec_t null_rec();

rec_t full_search(const rec_arr& arr, size_t key);

void sort_arr(rec_arr& arr);
rec_t binary_search(const rec_arr& arr, size_t key);

seg_arr split_arr(rec_arr& arr);
rec_t segment_search(const seg_arr& segments, size_t key);

#endif // SEARCH_H

