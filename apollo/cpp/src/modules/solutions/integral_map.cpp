//
//  integral_map.cpp
//  ApolloTeam
//
//  Created by Wang Yi on 19/6/19.
//
//

#include <iostream>

#include <vector>
using std::vector;

struct _aabb_t;
struct _point_t;

#define N 10

typedef struct _point_t {
    int r = 0;
    int c = 0;
    
    _point_t() {}
    _point_t(int r, int c) {
        this->r = r;
        this->c = c;
    }
    
    void from(int r, int c) {
        this->r = r;
        this->c = c;
    }
    
    bool isInside(_aabb_t& range);
} Pixel2D;

typedef struct _aabb_t {
    Pixel2D topLeft;
    Pixel2D bottomRight;
    
    Pixel2D centre;
    int width;
    int height;
    
    _aabb_t() {}
    _aabb_t(Pixel2D& topLeft, Pixel2D& bottomRight)
    {
        from(topLeft, bottomRight);
    }
    void from(Pixel2D& topLeft, Pixel2D& bottomRight)
    {
        this->topLeft = topLeft;
        this->bottomRight = bottomRight;
        
        this->centre.from((topLeft.r + bottomRight.r)/2.0, (topLeft.c +bottomRight.c)/2.0);
        
        width = bottomRight.c - topLeft.c;
        height = bottomRight.r - topLeft.r;
        
    }
    
    bool contains(Pixel2D& p) {
        return p.isInside(*this);
    }
    
    // adpated for this problem, using monotonic increasing features.
    bool contains(int map[N][N], int v) {
        int min = map[topLeft.r][topLeft.c];
        int max = map[bottomRight.r][bottomRight.c];
        if (v >= min && v <= max) {
            return true;
        }
        return false;
    }
    
    bool isNotSubdivided() {
        if (width <= 1 || height <= 1) {
            return true;
        } else {
            return false;
        }
    }
    
} AABB2D;

bool Pixel2D::isInside(_aabb_t &range) {
    if (r >=range.topLeft.r && r <= range.bottomRight.r &&
        c >=range.topLeft.c && c <= range.bottomRight.c) {
        return true;
    }
    return false;
}


template<typename Object>
struct _node_t {
    vector<_node_t*> nodes;
    vector<Object> objs; // for intersected objects to be inserted
    int qt_capacity = 5;
    int numOfnodes = 4;
    AABB2D range;
    
    _node_t(Pixel2D& topLeft, Pixel2D& bottomRight) {
        range.from(topLeft, bottomRight);
    }
    
    void subdivided() {
        
        int subheight = range.height / 2.0;
        int subwidth = range.width / 2.0;
        Pixel2D topLeft;
        Pixel2D bottomRight;
        _node_t* nd;
        
        // topLeft
        topLeft.from(range.topLeft.r, range.topLeft.c);
        bottomRight.from(topLeft.r + subheight, topLeft.c + subwidth);
        nd = new _node_t(topLeft, bottomRight);
        nodes.push_back(nd);
        
        // topRight
        topLeft.from(range.topLeft.r, range.topLeft.c + subwidth);
        bottomRight.from(topLeft.r + subheight, topLeft.c + subwidth);
        nd = new _node_t(topLeft, bottomRight);
        nodes.push_back(nd);
        
        // bottomLeft
        topLeft.from(range.topLeft.r + subheight, range.topLeft.c);
        bottomRight.from(topLeft.r + subheight, topLeft.c + subwidth);
        nd = new _node_t(topLeft, bottomRight);
        nodes.push_back(nd);
        
        // bottomRight
        topLeft.from(range.topLeft.r + subheight, range.topLeft.c + subwidth);
        bottomRight.from(topLeft.r + subheight, topLeft.c + subwidth);
        nd = new _node_t(topLeft, bottomRight);
        nodes.push_back(nd);
    }
    
    bool query(int I[N][N], int v) {
        if (!range.contains(I, v)) {
            return false;
        }
        
        if (range.isNotSubdivided()) {
            for (int i=range.topLeft.r; i <= range.bottomRight.r; i++)
            {
                for (int j=range.topLeft.c; j <= range.bottomRight.c; j++) {
                    if (I[i][j] == v) {
                        std::cout << "Find v = " << v << " at <" << i << "," << j << ">" << std::endl;
                        return true;
                    }
                }
            }
            return false;
        }
        
        subdivided();
        
        bool ret = false;
        for (auto nd : nodes) {
            if (nd->range.contains(I, v)) {
                ret = nd->query(I, v);
                if (ret) {
                    return true;
                }
            }
        }
        return false;
    }
    
    ~_node_t() {
        for (auto nd : nodes) {
            delete nd;
        }
        
    }
    
};

typedef _node_t<int> QuadNode;

class Solution {
public:
    bool quadFind(int map[N][N], int row, int col, int v)
    {
        Pixel2D a(0, 0);
        Pixel2D b(row-1, col-1);
        QuadNode root(a, b);
        bool ret = root.query(map, v);
        return ret;
    }

};

int main(int argc, char** argv)
{
    int pixelVal = 13;
    int map[N][N];
    int k=0;
    
    for (int i=0; i < 10; i++) {
        for (int j=0; j < 10; j++) {
            map[i][j] = k++;
        }
    }
    
    Solution sol;
    bool ret = sol.quadFind(map, N, N, pixelVal);
    
    return 0;
}
