//
//  stock_analyzer.cpp
//  StockAnalyze
//
//  Created by Wang Yi on 13/6/17.
//  Copyright © 2017 Wang Lei. All rights reserved.
//

#include "stock_analyzer.hpp"
#define MAX(a, b) ((a)>(b)?(a):(b))

template<typename T>
int
find_first_ne(int start, T arr[], int len)
{
    if (arr[start] >= 0)
    {
        int j = start+1;
        while (arr[j] >=0 && j < len) j++;
        if (j >= len) return len;
        return j;
    }
    else return start;
}

template<typename T>
int
find_first_po(int start, T arr[], int len)
{
    if (arr[start] < 0)
    {
        int k = start+1;
        while (arr[k] < 0 && k < len) k++;
        if (k >= len) return len;
        return k;
    }
    else return start;
}

double
longest_seq_sum(int start, double price_diff[], int len, int* stop)
{
    double ret, bridge, tail_sum, first_chunk;
    int j, k, next_stop;
    if (start - len >= 0) return 0;
    if (len - start == 1)
    {
        *stop = len-1;
        return price_diff[start]; //MAX(0, price_diff[start]);
    }
    j = find_first_ne<double>(start, price_diff, len);
    first_chunk = reduce_array(price_diff + start, j - start, 0.0,
                               [](double pre, double curr){return pre + curr;});
    k = find_first_po<double>(j, price_diff, len);
    
    tail_sum = longest_seq_sum(k, price_diff, len, &next_stop);
    bridge = j < len?reduce_array<double*, double>(price_diff + j, k - j, 0.0,
                                                 [](double pre, double curr){return pre + curr;}) : 0;
    if (tail_sum + bridge >= 0 && bridge != 0) {
        // we can connect price_diff[start .. ne_next(i)=j] with price_diff[po_next(j)=k .. stop]
        *stop = next_stop;
        return first_chunk + bridge + tail_sum;
    } else {
        *stop = k;
        return first_chunk;
    }
    
    return ret;
}

double
max_seq_sum(int start, double price_diff[], int len)
{
    int pivot;
    double first_chunk;
    if (start - len >= 0) return 0;
    if (len - start == 1) return price_diff[start];
    
    start = find_first_po<double>(start, price_diff, len);
    first_chunk = longest_seq_sum(start, price_diff, len, &pivot);
    return MAX(first_chunk, max_seq_sum(pivot, price_diff, len));
}

