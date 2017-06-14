//
//  functional.hpp
//  StockAnalyze
//
//  Created by Wang Yi on 13/6/17.
//  Copyright © 2017 Wang Lei. All rights reserved.
//

#ifndef functional_hpp
#define functional_hpp

#include <stdio.h>
#include <stdlib.h>

#define Malloc(type, len) \
(type*) malloc(sizeof(type)*len)

#define FOR(i, s) \
for(i=0; i < s; i++) {
#define END ;}

template <typename  _Ar, typename _Tp, class _BinaryOperation>
_Tp
reduce_array(_Ar __array, int len, _Tp __init, _BinaryOperation __binary_op)
{
    int curr=0;
    for (; curr < len; curr++){
        __init = __binary_op(__init, *__array++);
    }
    return __init;
}

template <typename _Ar, typename _Tp, class UnaryPredicate>
_Ar
filter_array(_Ar __array, int len, _Tp __default, UnaryPredicate __pred)
{
    int i, j;
    _Ar ret = Malloc(_Tp, len);
    FOR(i, len)
    ret[i] = __default;
    END
    
    i = 0;
    FOR(j, len)
    if (__pred(__array[j]))
        ret[i++] = __array[j];
    END
    
    return ret;
}

#endif /* functional_hpp */
