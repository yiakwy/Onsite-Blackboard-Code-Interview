//
//  find_circles.cpp
//  ApolloTeam
//
//  Created by Wang Yi on 7/5/19.
//
//

#include "find_circles.hpp"
#include <iostream>
#include <memory>

typedef struct _edge_t {
    int start;
    int end;
} *Edge;

int
find_parent_by_compr(int* sets, int i) {
    if (sets[i] != -1) {
        int parent = find_parent_by_compr(sets, sets[i]);
        if (parent != i) {
            sets[i] = parent;
        }
        return parent;
    } else {
        return i;
    }
}

int
union_by_rank(int* sets, int* ranks, int left, int right) {
    int lparent = find_parent_by_compr(sets, left);
    int rparent = find_parent_by_compr(sets, right);
    
    if (lparent == rparent) {
        return lparent;
    }
    
    if (ranks[lparent] > ranks[rparent]) {
        sets[rparent] = lparent;
        return lparent;
    } else if (ranks[lparent < ranks[rparent]]) {
        sets[lparent] = rparent;
        return rparent;
    } else {
        sets[rparent] = lparent;
        ranks[lparent] += 1;
        return lparent;
    }
}

int main(int argc, char** argv)
{
    int nodes[3] = {0, 1, 2};
    int N = 3, i, j, k;
    int circles = 0;

    // unique_ptr
    Edge *edges = new Edge[N];
    
    for (i=0; i < N; i++) {
        edges[i] = new _edge_t();
        edges[i]->start = i;
        edges[i]->end = i+1;
    }
    
    int *sets = new int[N];
    int *ranks = new int[N];
    
    for (j=0; j < N; j++) {
        sets[j] = -1;
        ranks[j] = 0;
    }
    
    // find circles
    for (k=0; k < N; k++) {
        int left = edges[k]->start, right = edges[k]->end;
        union_by_rank(sets, ranks, left, right);
        
    }
    
    for (k=0; k < N; k++) {
        int parent = find_parent_by_compr(sets, k);
        if (parent == k) {
            circles++;
        }
    }
    
    std::cout << "find " << circles << " circles." << std::endl;

}
