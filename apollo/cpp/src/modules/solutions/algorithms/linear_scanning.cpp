#include "linear_scanning.hpp"

vector<Pixel2D>
ScanlineRenderer(Polygon polygon, Window window) {
    vector<Pixel2D> populated;
    std::unique_ptr<Edge[]>  ET(new Edge[window.height]); // Edge Table
    
    Edge AET = new _edge_bucket_t(); // Active Edge Table
    
    Pixel2D bottomRight = polygon[0];
    Pixel2D topLeft = polygon[0];
    Pixel2D curr;
    Pixel2D before;
    Pixel2D after;
    
    // initialization
    for (int i=0; i < polygon.size(); i++) {
        auto idx = [&](int i) -> int {
            return (i+polygon.size()) % polygon.size();
        };
        Pixel2D p_pre = polygon[idx(i-1)];
        Pixel2D p = polygon[i];
        Pixel2D p_succ = polygon[idx(i+1)];
        
        Edge edge = new _edge_bucket_t();
        
        int offset, ymax;
        float x, dx, k;
        
        // discard horizontal lines
        if (p_succ.y() == p.y()) {
            continue;
        }
        
        if (p.y() > p_succ.y()) {
            ymax = p.y();
            x = p_succ.x();
            offset = p_succ.y();
        } else {
            ymax = p_succ.y();
            x = p.x();
            offset = p.y();
        }
        
        k = (p_succ.y() - p.y()) * 1.0f / (p_succ.x() - p.x());
        dx = 1.0f / k;
        
        if ((p_succ.y() > p.y() && p_pre.y() > p.y()) ||
            (p_succ.y() < p.y() && p_pre.y() < p.y())) {
            edge->is_stational = true;
        }
        
        // verify point if with stational value w.r.t y
        edge->ymax = ymax;
        edge->offset = offset;
        edge->x = x;
        edge->dx = dx;
        
        
        // AABB computing
        if (bottomRight.x() < x) {
            bottomRight.setX(x);
        }
        
        if (topLeft.x() > x) {
            topLeft.setX(x);
        }
        
        if (bottomRight.y() > offset) {
            bottomRight.setY(offset);
        }
        
        if (topLeft.y() < offset) {
            topLeft.setY(offset);
        }
        
        // store the edge
        if (ET[p.row()] == nullptr) {
            Edge sentinel = new _edge_bucket_t();
            ET[p.row()] = sentinel;
        }
        
        ET[p.row()]->insert(edge);
        
    }
    
    // The programe commpletes once all edges removed from ET. Filling start from bottom scanline until to the top.
    for (int row = bottomRight.y(); row < topLeft.y(); row++)
    {
        // insert all ET[row] edges started from scan line row
        while (ET[row]->next)
        {
            Edge edge = ET[row]->next;
            
            ET[row]->remove(edge);
            AET->insertSortByAttrs(edge);
            
        }
        
        // collected inner points by alternating intersection segments
        Edge parent, edge = AET->next;
        parent = edge;
        int count = 0;
        while (edge != nullptr) {
            if ( edge->is_stational ){
                count += 2;
            } else {
                count += 1;
            }
            
            if (count % 2 == 0) {
                if (edge->is_stational) {
                    populated.push_back(Pixel2D(edge->x, row));
                } else {
                    // counted pixels between
                    for (int x = parent->x; x < edge->x; x++) {
                        populated.push_back(Pixel2D(x, row));
                    }
                }
                parent = edge->next;
            }
            
            edge = edge->next;
            
        }
        
        // deleted edges with row=edge->ymax from AET and increment x by dx
        parent = AET, edge = AET->next;
        while(edge->next)
        {
            if (edge->ymax == row)
            {
                // there is no more possibility to produce new intersections
                Edge removed = edge;
                
                parent->next = removed->next;
                removed->next = nullptr;
                
                edge = edge->next;
                delete removed;
            } else {
                edge->x += edge->dx;
            }
            edge = edge->next;
        }
        
    }
    
    return populated;
    
}
