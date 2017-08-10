//
//  api.h
//  topk
//
//  Created by Wang Yi on 9/8/17.
//  Copyright © 2017 Wang Lei. All rights reserved.
//

#ifndef api_h
#define api_h

#include <stdlib.h>

#define Malloc(type, len) \
    (type*) malloc(sizeof(type) * len)

#define SHALLOW_CPY(data, target, shift) \
    shift = sizeof(data); \
    target = malloc(sizeof(shift)); \
    memcpy(target, data, shift);

#endif /* api_h */
