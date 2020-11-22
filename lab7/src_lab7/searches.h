#ifndef SEARCH_H
#define SEARCH_H

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


#endif // SEARCH_H

