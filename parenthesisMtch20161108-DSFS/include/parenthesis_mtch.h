//
//  parenthesis_mtch.h
//  parenthesis_mtch
//
//  Created by Wang Yi on 14/11/16.
//  Copyright (c) 2016 Wang Yi. All rights reserved.
//

#ifndef __parenthesis_mtch__parenthesis_mtch__
#define __parenthesis_mtch__parenthesis_mtch__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#define Malloc(type, size) \
(type*) malloc(sizeof(type)*size)

int parenthesis_mtch(const char* array, int l);

#ifdef __cplusplus
}
#endif

#endif /* defined(__parenthesis_mtch__parenthesis_mtch__) */
