//
//  lambda.hpp
//  common
//
//  Created by Lei Wang 王磊 on 2018/12/17.
//

#ifndef lambda_hpp
#define lambda_hpp

#include <stdio.h>
#include <vector>
#include <algorithm>
#include <functional>

template < typename T, class UnaryPredictor>
std::vector< T > filter_func(const std::vector< T >& sequence, UnaryPredictor __pred)
{
    std::vector< T > result;
    
    for(auto it = sequence.begin(); it != sequence.end(); ++it)
        if(__pred(*it))
            result.push_back(*it);
    
    return result;
}

template < typename T, class UnaryOperator>
std::vector< T > map_func(const std::vector< T >& sequence, UnaryOperator __mapper)
{
    std::vector< T > result;
    
    for(auto it = sequence.begin(); it != sequence.end(); ++it)
        result.push_back(__mapper(*it));
    
    return result;
}

#endif /* lambda_hpp */
