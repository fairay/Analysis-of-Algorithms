#include "searches.h"
rec_t null_rec()
{
    rec_t rec;
    rec.key = 0;
    rec.val = 10000;
    return rec;
}

rec_t full_search(const rec_arr& arr, size_t key)
{
	for (int i = 0; i < arr.size(); i++)
		if (arr[i].key == key)
			return arr[i];
	return null_rec();
}

void sort_arr(rec_arr& arr)
{
    for (int i = 0; i < arr.size() - 1; i++)
        for (int j = 0; j < arr.size() - i - 1; j++)
            if (arr[j].key > arr[j + 1].key)
                std::swap(arr[j], arr[j + 1]);
}
rec_t binary_search(const rec_arr& arr, size_t key)
{
    int left = 0;
    int right = arr.size() - 1;
    while (left <= right)
    {
        int mid = (left + right) / 2;
        if (key == arr[mid].key)
            return arr[mid];
        if (key < arr[mid].key)
            right = mid - 1;  
        else                  
            left = mid + 1;   
    }
    return null_rec();
}

seg_arr split_arr(rec_arr& arr)
{
    seg_arr segments;
    for (int i = 0; i < 10; i++)
    {
        rec_seg temp_seg;
        temp_seg.key = i;

        segments.push_back(temp_seg);
    }

    for (int i = 0; i < arr.size(); i++)
        segments[arr[i].key % 10].records.push_back(arr[i]);
    return segments;
}
rec_t segment_search(const seg_arr& segments, size_t key)
{
    int seg_n = -1;
    for (int i=0; i<segments.size(); i++)
        if (segments[i].key == key % 10)
        {
            seg_n = i;
            break;
        }
    
    if (seg_n == -1)
        return null_rec();

    const rec_arr& arr = segments[seg_n].records;
    return full_search(arr, key);
}

