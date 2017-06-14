//
//  stock_analyzer.hpp
//  StockAnalyze
//
//  Created by Wang Yi on 13/6/17.
//  Copyright © 2017 Wang Lei. All rights reserved.
//

#ifndef stock_analyzer_hpp
#define stock_analyzer_hpp

#include <stdio.h>
#include <stdlib.h>
#include "functional.hpp"

double longest_seq_sum(int start, double price_diff[], int len, int* stop);
double max_seq_sum(int start, double price_diff[], int len);

template<typename T>
T*
array2accumulated(T* array, size_t len)
{
    T* ret = new T[len-1];
    size_t  i;
    for (i = 0; i < len-1; i++)
    {
        ret[i] = array[i+1] - array[i];
    }
    return ret;
}


#endif /* stock_analyzer_hpp */
