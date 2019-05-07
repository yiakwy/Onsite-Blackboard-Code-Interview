//
//  linear_scanning.hpp
//  ApolloTeam
//
//  Keywords: Z-Buffer with front-to-back sorting, Scanline Rendering algorithm.
//
//  The algorithm was developed in late 1960s and mostly stemed from UTH graphics group for devices with no frame buffer memory and "it generates each pixel just-in-time as it scans out ot the display"
//
//  Other algorithms include FloodFill (which I used with grid and tile data structures to develop 3d PointsCloud segmentation utilities without HDMap), pixle color assignment through binded polygons (also called rasterization, common in webgl and other rendering engine)
//
//  For graphics utities for rendering, see src/modules/gl. Currently we use opengl and vtk as backends. For scene graph and other uitlies support, like quaternion, kdtree, I planned to use webgl html5 as frontend and c++ server as backend to provide computed data for rendering. For more details see <thirdpairties/network> where I develop grpc based network framework for that purpose.
//
//  For simplicity, I developed the program independantly, i.e. input polygon and ouput populated pixels. For demo purposes then you can use 2d gl programmes to access gpu for rendering the shape.
//
//  To learn how it works inside gl programes, see older gl driver's rasterization implementation. https://www.scratchapixel.com/lessons/3d-basic-rendering/rasterization-practical-implementation/rasterization-stage
//
//  Ref: Wikipedia,
//       Computational Geometry,
//       Computer Graphics with OpenGL (UTH e-book),
//       GeeksforGeeks: https://www.geeksforgeeks.org/scan-line-polygon-filling-using-opengl-c/
//                      https://www.jianshu.com/p/d9be99077c2b
//
//  Author: Lei Wang (yiak.wy@gmail.com)
//  Created by Wang Yi on 17/4/19.
//
//
//
#ifndef LINEAR_SCANNING_HPP_
#define LINEAR_SCANNING_HPP_

#include <vector>
using std::vector;

#include <memory>

namespace SolutionAlgorithms {

struct Window {
    int width;
    int height;
};

typedef struct _edge_bucket_t {
    
    typedef _edge_bucket_t Type;
    typedef _edge_bucket_t* eb_ptr;
    
    int ymax;
    int offset;
    float x; // the current position x value along the scanning line
    float dx; // inverse of
    _edge_bucket_t* next;
    bool is_stational;
    
    _edge_bucket_t(): next(nullptr), is_stational(false) {
        
    }
    
    eb_ptr
    insert(eb_ptr edge) {
        edge->next = next;
        next = edge;
        return this;
    }
    
    eb_ptr
    remove(eb_ptr edge) {
        eb_ptr parent, curr; // the parent should be a sentinel standing at head.
        parent = this;
        curr = parent->next;
        while (curr != nullptr)
        {
            if (curr == edge) { // find it
                parent->next = edge->next;
                edge->next = nullptr;
                return edge;
            }
            
            parent = curr;
            curr = curr->next;
        }
        return nullptr;
    }
    
    eb_ptr
    insertSortByAttrs(eb_ptr edge) {
        eb_ptr parent, curr;
        parent = this;
        curr = parent->next;
        
        auto is_intended_pos = [&](eb_ptr self, eb_ptr other) -> int {
            if (self == nullptr) {
                return false;
            }
            if (other->x > self->x) {
                return true;
            } else if (other->x == self->x && other->dx > self->x) {
                return true;
            } else {
                return false; // find it
            }
        };
        
        while (is_intended_pos(curr, edge))
        {
            parent = curr;
            curr = curr->next;
        }
        
        if (is_intended_pos(curr, edge)) {
            edge->next = curr->next;
            curr->next = edge;
        } else {
            parent->next = edge;
        }
        return this;
    }
    
}* Edge;

class Point
{
public:
    explicit Point() {}
    virtual ~Point() = default;
    
    virtual double x() = 0;
    virtual double y() = 0;
    virtual double z() = 0;
};

class Pixel2D : public Point
{
public:
    explicit Pixel2D() : Point(), row_(-1), col_(-1) {}
    
    explicit Pixel2D(int x, int y) : row_(y), col_(x) {
    
    }
    
    virtual ~Pixel2D() {
    
    }
    
    double x() override {
        return col_;
    }
    
    double y() override {
        return row_;
    }
    
    double z() override {
        return 0;
    }
    
    int row() {
        return row_;
    }
    
    int col() {
        return col_;
    }
    
    void setX(int x) {
        col_ = x;
    }
    
    void setY(int y) {
        row_ = y;
    }
    
private:
    int row_;
    int col_;
    
};

class AABB {
public:
    virtual ~AABB() = default;
};

class AABBPixel2D : public AABB {
public:
    explicit AABBPixel2D() {
    
    }
    explicit AABBPixel2D(Pixel2D& bottomRight, Pixel2D& topLeft) {
        this->bottomRight = bottomRight;
        this->topLeft = topLeft;
    }
    
    Pixel2D bottomRight;
    Pixel2D topLeft;
};

typedef vector<Pixel2D> Polygon;

/*
 COMMENT:
 First collect all of polygon edges except horizontal ones. Since we are using scanning lines, we only care about x position of an edge and use numeric differential method to compute the whole scanning line interiors.
 
 The intuitive thinking about why we use such method to boost , as far as I am concerned, is that as we moving scanning lines up, we can use <x = x + dx> to compute intersections which is much cheaper commpared with linear algebra.
 
 */
vector<Pixel2D>
ScanlineRenderer(Polygon polygon, Window window);

}

#endif /*linear_scanning_hpp*/
