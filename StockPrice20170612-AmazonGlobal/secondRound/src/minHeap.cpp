//
//  minHeap.cpp
//  topk
//
//  Created by Wang Yi on 9/8/17.
//  Copyright © 2017 Wang Lei. All rights reserved.
//

// if you are interested in generic C, I recommend to read source python.
// c `obj` implementation will be defined in Object directory; their corresponding declearation reside in `include`
#include "minHeap.hpp"
#include "logging.hpp"

void
swap(objref* left, objref* right)
{
    objref temp = *left;
    *left = *right;
    *right = temp;
}

heap*
heap_new(size_t size) {
    LOG(INFO) << "Allocating memory for heap ...";
    heap* head = (heap*)Malloc(min_heap, 1);
    CHECK(head != nullptr) << "Alloc proc for <heap> falied. exit.";
    if (head == nullptr) return nullptr;
    LOG(INFO) << "alloc at address: " << head;
    TREE(head) = Malloc(objref, size);
    CHECK(TREE(head) != nullptr) << "Alloc proc for <heap:list> failed. exit.";
    if (TREE(head) == nullptr) return nullptr;
    head->capacity = size;
    head->last = 0;
    return head;
}

void
heap_del(heap* h){
    free(TREE(h));
    free(h);
}

void
heap_heapify(heap* self, size_t p, cmpfunc cmp){
    size_t smaller, larger;
    size_t left = LEFT(p), right = RIGHT(p);
    if (left >= self->capacity || (right < self->capacity && cmp(TREE_AT(self, left),TREE_AT(self, right)) > 0)) {
        // when left is empyt or right is smaller than left
        smaller = right;
        larger = left;
    } else {
        smaller = left;
        right = larger;
    }
    
    if (smaller < self->capacity && cmp(TREE_AT(self, 0), TREE_AT(self, smaller)) > 0) {
        // the smaller is less than the curr root
        swap(&TREE_AT(self, 0), &TREE_AT(self, smaller));
        heap_heapify(self, smaller, cmp);
    }
}

void*
heap_insert(heap* self, const void* data, cmpfunc cmp) {
    size_t curr, root=0;
    heap* head = self;
    list l = TREE(head);
    objref ob = Malloc(Object, 1);
    CHECK(ob != nullptr) << "Alloc proc for <objref> falied. exit.";
    SHALLOW_CPY(data, ob->data, (ob->offset))
    
    if (head->last < head->capacity)
    {
        TREE_AT(head, head->last) = ob;
    
        // percolated up
        curr = head->last;
        head->last++;
        // for min_heap, cmp(curr, parent) == -1, percolate up
        // for max_heap, cmp(curr, parent) == 1, percolate up
        while(curr != 0 && cmp(ob, l[PARENT(curr)]) < 0) {
            l[curr] = l[PARENT(curr)];
            curr = PARENT(curr);
        }

        l[curr] = ob;
    } else {
        // espicially useful in topk operation
        if (cmp(ob, l[root]) < 0) {
            return nullptr; // reject
        } else {
            // the root must be the k+1 th largest el
            TREE_AT(head, root) = ob;
            // heapify op
            heap_heapify(self, 0, cmp);
        }
    }
    return (void*)ob;
}

// heap subclass init
min_heap*
min_heap_new(size_t size, cmpfunc cmp, const void* data[]) {
    min_heap* head = (min_heap*) heap_new(size);
    CHECK(head != nullptr) << "Alloc proc for <minheap> falied. exit.";
    if (head == nullptr) return nullptr;
    // this will define
    // binding method for objref dynamically
    head->cmp = cmp;
    head->insert = heap_insert;
    head->heapify = heap_heapify;
    if (data != nullptr) {
        int i = 0;
        while (i < size) {
            head->insert((heap*)head, data[i], cmp);
            i++;
        }
        log_heap((heap*)head, size);
    }
    return head;
}

// mini heap of size k, topk method for largest k elments
// for topk problem, the root elment will be kth smallest element; hence we have the following strategy:
// 1) if rereshly coming element is bigger than the root, discard it directly else got 2)
// 2) we must find a new postion for the elment; we wrap it in objref; and discard the current (k+1)th smallest elemnt

void
max_topk(void const** data, void** ret, size_t l, size_t k, cmpfunc cmp){
    size_t i;
    min_heap* head = nullptr;
    if (k < l) {
        head = (min_heap*)min_heap_new(k, cmp, data);
        CHECK(head != nullptr) << "Alloc proc for <topk> falied. exit.";
        if (head == nullptr) exit(1);
        *ret = (void*)head;
    } else {
        head = (min_heap*)min_heap_new(l, cmp, data);
        CHECK(head != nullptr) << "Alloc proc for <topk> falied. exit.";
        if (head == nullptr) exit(1);
        *ret = (void*)head;
        return;
    }
    
    // once allocated, we loop through the rest of elements using provided cmp
    for (i=k; i<l; i++) {
        LOG(INFO) << "loop through, the current el is " << *(int*)data[i];
        heap_insert((heap*)head, data[i], cmp);
        log_heap((heap*)head, k);
    }
    
}

void
log_heap(heap* h, size_t size){
    list l = TREE(h);
    size_t i;
    LOG(INFO) << "the heap is: ";
    for(i=0; i<size; i++) {
        std::cout << *(int*)l[i]->data << " ";
    }
    std::cout << std::endl;
}
