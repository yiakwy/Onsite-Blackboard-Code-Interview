//
//  main.cpp
//  topk
//
//  Created by Wang Yi on 9/8/17.
//  Copyright © 2017 Wang Lei. All rights reserved.
//

#include <iostream>
#include "minHeap.hpp"
#include "logging.hpp"
#define N 10
#define K 3

#define Object_Value(ob) \
    *(int*)(ob->data)

int
min_heap_cmp(objref left, objref right){
    if (Object_Value(left) > Object_Value(right)) {
        return  1;
    } else if (Object_Value(left) == Object_Value(right)) {
        return  0;
    } else {
        return -1;
    }
}

int main(int argc, const char * argv[]) {
    globalInit(argc, argv);
    int data[N] = {3, 1, 6, 5, 7, 4, 8, 9, 10, 11};
    void** inp = Malloc(void*, N);
    int i;
    for (i=0; i< N; i++) {
        inp[i] = (void*)(&data[i]);
    }
    
    heap* ret = nullptr;
    max_topk((const void**)inp, (void**)&ret, N, K, min_heap_cmp);
    
    CHECK(ret != nullptr) << "Empty Result! Something wrong here ...";
    for (i=0; i<K ; i++) {
        std::cout << *(int*)(TREE_AT(ret, i)->data) << " ";
    }
    std::cout << std::endl;
    return 0;
}
