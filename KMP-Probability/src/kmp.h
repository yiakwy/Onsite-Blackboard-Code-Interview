//
//  kmp.h
//  Cyclic_Moving
//
//  Created by Wang Yi on 15/5/16.
//  Copyright (c) 2016 Wang Yi. All rights reserved.
//

#ifndef __kmp__
#define __kmp__

// https://isocpp.org/wiki/faq/mixing-c-and-cpp
// we will mix cpp and c
#ifdef __cplusplus
extern "C" {
#endif
    
#include <stdio.h>
#define STRINGLIB(F) stringlib_kmp_##F

size_t pattern_find(const char* t, size_t len, const char* pttn, size_t pttn_len);
void GetNext(const char* pattern, int steps[]);
void GetNext2(const char* pttn, int steps[]);

#ifdef __cplusplus
}
#endif
    
#endif /* defined(__kmp__) */
