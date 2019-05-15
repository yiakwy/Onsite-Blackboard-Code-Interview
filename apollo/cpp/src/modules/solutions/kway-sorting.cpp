//
//  kway-sorting.cpp
//  ApolloTeam
//
//  Created by Wang Yi on 8/5/19.
//  Started at Web 10:35 PM
//  Ended at Web 11:12 PM
//  Elapse : 32 Mins

#include <iostream>
#include <vector>
#include <math.h>
using std::vector;

#define TREE(h) ((h)->array_alike_tree())

#define LEFT(CURR) (2*(CURR+1)-1)
#define RIGHT(CURR) (2*(CURR+1))
#define PARENT(i) (floor(((i)-1) / 2))

#define LEFT_CHILD(h, i) (TREE(h)[LEFT(i)])
#define RIGHT_CHILD(h, i) (TREE(h)[RIGHT(i)])
#define TREE_AT(h, i) (TREE(h)[i])
#define TOP(h) (TREE_AT(h, 0))

template<typename ElemType>
class MinHeap {
public:
    using Type = MinHeap;
    
    MinHeap(size_t capacity)
    : capacity_(capacity),
      last_(0) {
          array_alike_tree_.resize(capacity);
    }
    
    ~MinHeap() {};
    
    void Init(ElemType* els, size_t size)
    {
        Clear();
        int i = 0;
        size = size < capacity_ ? size:capacity_;
        while (i < size) {
            insert(els[i]);
            i++;
        }
    }
    
    void Clear() {
        last_ = 0;
        array_alike_tree_.clear();
    }
    
    vector<ElemType>& array_alike_tree() {
        return array_alike_tree_;
    }
    
    void heapify(int root) {
        size_t left = LEFT(root);
        size_t right = RIGHT(root);
        size_t small, large;
        
        if (left >= capacity_ || (right < capacity_ && LEFT_CHILD(this, root) > RIGHT_CHILD(this, root)))
        {
            small = right;
            large = left;
        } else {
            large = right;
            small = left;
        }
        
        if (small < capacity_ && TREE_AT(this, root) > TREE_AT(this, small)) {
            ElemType tmp = TREE_AT(this, root);
            TREE_AT(this, root) = TREE_AT(this, small);
            TREE_AT(this, small) = tmp;
            
            heapify(small);
        }
        
    }
    
    void insert(ElemType el) {
        if (last_ < capacity_) {
            TREE_AT(this, last_) = el;
            
            // percolate up
            int curr = last_;
            last_++;
            while (curr != 0 && TREE_AT(this, PARENT(curr)) > el) {
                TREE_AT(this, curr) = TREE_AT(this, PARENT(curr));
                curr = PARENT(curr);
            }
            TREE_AT(this, curr) = el;
        }
        /*
        else {
            // max topk operation
            if (TOP(this) < el) {
                TOP(this) = el;
                heapify(0);
            }
        }
         */
    }
    
    void topKInsert(ElemType el) {
        if (last_ < capacity_) {
            insert(el);
        } else {
            if (TOP(this) < el) {
                TOP(this) = el;
                heapify(0);
            }
        }
    }
    
    ElemType pop() {
        ElemType top = TREE_AT(this, 0);
        TREE_AT(this, 0) = TREE_AT(this, last_-1);
        last_--;
        heapify(0);
        return top;
    }
    
    bool empty() {
        if (last_ <= 0) {
            return true;
        } else {
            return false;
        }
    }
    
    ElemType at(const size_t i) const {
        return array_alike_tree_[i];
    }
    
    std::string _str() const {
        std::string ret;
        for (int i=0; i < capacity_ - 1; i++) {
            ret += std::to_string(at(i)) + " ";
        }
        ret += std::to_string(at(capacity_-1));
        return ret;
    }
    
    /*
    std::ostream& dump(std::ostream& o) const {
        return o << _str();
    }
     */
    
private:
    std::vector<ElemType> array_alike_tree_;
    size_t capacity_;
    size_t last_;
};


template<typename ElemType>
std::ostream& operator<<(std::ostream& o, const MinHeap<ElemType>& heap) {
    return o << heap._str();
}

// The second try:
#include <queue>

int main(int argc, char** argv)
{
    int K = 3;
    int array[7] = {1, 23, 12, 9, 30, 2, 50};
    MinHeap<int> heap(K+1);
    
    heap.Init(array, K+1);
    
    std::cout << "Init heap with K+1 elements of array : " << heap << std::endl;
    
    for (int i=K+1; i < 7; i++) {
        heap.topKInsert(array[i]);
    }
    
    std::cout << "topK elements of array : " << heap << std::endl;
    
    int array0[7] = {2, 3, 5, 6, 8, 9, 10};
    int out[7] = {0};
    
    heap.Init(array0, K+1);
    
    // k-way sorting, position 0 which could be the minest is only afected by 1, 2, ... , k positions.
    // by reduction the we could conclude the formulation:
    int j = 0;
    for (int i=K+1; i < 7; i++) {
        out[j++] = heap.pop();
        heap.insert(array0[i]);
    }
    while (!heap.empty()) {
        out[j++] = heap.pop();
    }
    
    std::cout << "K-way sorting result of array0 : ";
    for (int i=0; i < 6; i++) {
        std::cout << std::to_string(out[i]) << " ";
    }
    std::cout << std::to_string(out[6]) << std::endl;
    
    // using STL
    std::priority_queue<int, std::vector<int>, std::greater<int>> q(array0, array0+K+1);
    
    j = 0;
    for (int i=K+1; i < 7; i++)
    {
        array0[j++] = q.top(); q.pop();
        q.push(array0[i]);
    }
    
    while (!q.empty()) {
        array0[j++] = q.top(); q.pop();
    }
    
    std::cout << "K-way in-placement sorting result of array0 using STL : ";
    for (int i=0; i < 6; i++) {
        std::cout << std::to_string(array0[i]) << " ";
    }
    std::cout << std::to_string(array0[6]) << std::endl;
}
