//
//  minHeap.hpp
//  topk
//
//  Created by Wang Yi on 9/8/17.
//  Copyright © 2017 Wang Lei. All rights reserved.
//

#ifndef minHeap_hpp
#define minHeap_hpp

#ifdef __cplusplus
extern "C" {
#endif
#include <stddef.h>
#include <math.h>
#include "api.h"

    typedef struct _obj {
        void* data;
        size_t offset;
    } Object;
    typedef Object* objref;
    typedef objref * list;
    
    void
    swap(objref, objref);
// in case of some special usage like : get address of `this` pointer
    #define get_address(objref) (&(*objref))
    #define attribute(ref, bytes) (reinterpret_cast<char*>(ref) + (bytes))
    
typedef struct _heap {
    size_t capacity;
    size_t last;
    list array_alike_tree;
} heap;

typedef int (*cmpfunc)(objref, objref);
// API, in case of modifying the codes in the future
#define LEFT(CURR) (2*((CURR)+1) - 1)
#define RIGHT(CURR) (2*((CURR)+1))
#define PARENT(CURR) ((CURR-1)/2)
    
#define TREE(h) ((h)->array_alike_tree)
#define TREE_AT(h, i) (((h)->array_alike_tree)[i])
#define LEFT_LEAF(h,CURR) ((TREE(h))[LEFT(CURR)])
#define RIGHT_LEAF(h, CURR) ((TREE(h))[RIGHT(CURR)])

// go or C style object oriented programming (OOP); some interviewers don't understand oop well, SO here I will give you a deep explanation:
// before 1990, we don't C++ alike languages, we use `union`, `reinterpret_cast`, memory `offset` to compute shared behaviors of instances of classes which implements some protocle or interface.
// In objectiveC or Go, we don't have class binding, and concepts like "virtual method" to deal with duplicated operation upon memory, or "visiting controling" . Instead, we use receiver and message passing to bind a method to an instance of some class.
    typedef void  (*heapifyfunc)(heap* , size_t, cmpfunc);
    typedef void*  (*insertfunc)(heap* , const void*, cmpfunc);
    typedef int     (*allocator)(heap* , size_t);
    typedef int    (*destructor)(heap*);

#ifndef _Heap_Interface
#define _Heap_Interface      \
        heapifyfunc heapify; \
         insertfunc insert;  \
          allocator init;    \
         destructor del;
#endif
    
    typedef struct _min_heap {
        int capacity;
        size_t last;
        void** array_alike_tree;
        // implements "heap protocol"
        _Heap_Interface
        cmpfunc cmp;
    } min_heap;
    
    void
    max_topk(void const** data, void** ret, size_t l, size_t k, cmpfunc cmp);
    void
    log_heap(heap* h, size_t size);

#ifdef __cplusplus
}
#endif
    
#endif /* minHeap_hpp */
