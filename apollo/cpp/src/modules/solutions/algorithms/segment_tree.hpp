//
//  segmetn_tree.hpp
//  ApolloTeam
//
//  Created by Wang Yi on 5/5/19.
//
//

#ifndef segment_tree_hpp
#define segment_tree_hpp

#include <map>
using std::map;
using std::pair;
using std::make_pair;

#include "utils/api.h"

#ifndef TREE_NODE_IMPL
#define TREE_NODE_IMPL
class TreeNode {
    
private:
    int start_;
    int end_;
    int mid_;
    double sum_;
    double* array_;
public:
    
    TreeNode(int start, int end, double* array)
    : start_(start),
    end_(end),
    sum_(0.f),
    array_(array) {
        if (end - start <= 1) {
            is_leaf_node = true;
        }
        mid_ = (end + start) / 2;
    }
    
    ~TreeNode() {
        delete left;
        delete right;
        left = nullptr;
        right = nullptr;
    }
    
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    bool is_leaf_node = false;
public:
    
    void
    UpdateSum(double diff) {
        sum_ += diff;
    }
    
    void
    UpdateSum(int s, int e, double* arr) {
        double sum = 0.0;
        for (int i=s; i < e; i++) {
            sum+=arr[i] - array_[i];
        }
        UpdateSum(sum);
    }
    
    bool does_contains(int i) {
        if (i >= start_ && i < end_) {
            return true;
        } else {
            return false;
        }
    }
    
    bool inside(int l, int r) {
        if (l <= start_ && r >= end_) {
            return true;
        } else {
            return false;
        }
    }
    
    bool outside(int l , int r) {
        if (l >= end_ || r <= start_) {
            return true;
        } else {
            return false;
        }
    }
    
    void
    insert_impl(int i, double val) {
        if (!does_contains(i)) {
            return;
        }
        
        double diff = val - array_[i];
        
        if (is_leaf_node) {
            COMMON_LOG_INFO << format("Updating Tree.at(%d) from %f to %f", i, array_[i], array_[i]+diff) << std::endl;
            array_[i] += diff;
            UpdateSum(diff);
            return;
        }
        
        UpdateSum(diff);
        if (i < mid_) {
            if (!left) {
                left = new TreeNode(start_, mid_, array_);
            }
            left->insert_impl(i, val);
        } else {
            if (!right) {
                right = new TreeNode(mid_, end_, array_);
            }
            right->insert_impl(i, val);
        }
        
    }
    
    void
    insert_impl(int s, int e, double* arr) {
        if (outside(s, e)) {
            return;
        }
        
        double diff = arr[s] - array_[s];
        
        if (is_leaf_node) {
            COMMON_LOG_INFO << format("Updating Tree.at(%d) from %f to %f", s, array_[s], array_[s]+diff) << std::endl;
            array_[s] += diff;
            UpdateSum(diff);
            return;
        }
        
        UpdateSum(s, e, arr);
        if (s <= mid_) {
            if (!left) {
                left = new TreeNode(start_, mid_, array_);
            }
            left->insert_impl(s>start_?s:start_, mid_, arr);
            if (!right) {
                right = new TreeNode(mid_, end_, array_);
            }
            right->insert_impl(mid_, e<end_?e:end_, arr);
        } else {
            if (!right) {
                right = new TreeNode(mid_, end_, array_);
            }
            right->insert_impl(s, e<end_?e:end_, arr);
        }
        
    }
    
    double
    sum(int s, int e) {
        if (outside(s, e)) {
            return 0.f;
        }
        
        if (inside(s, e)) {
            return sum_;
        }
        
        if (is_leaf_node) {
            return array_[s];
        }
        
        // internal nodes must have left and right children
        return left->sum(s, e) + right->sum(s, e);
    }
    
};


class LinearTreeNode {
    
};
#endif


#endif /* segment_tree_hpp */
