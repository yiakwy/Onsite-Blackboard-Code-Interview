//
//  exceptions.cpp
//  KMP
//
//  Created by Wang Yi on 15/3/17.
//  Copyright © 2017 Wang yiak.co. All rights reserved.
//

#include "exceptions.hpp"

//[Not user defined --Dynguss]
template<class E> inline void throw_exception(E const & e)
{
    throw e;
}