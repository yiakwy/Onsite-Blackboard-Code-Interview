//
//  diff_tree.cpp
//  airbnb_P2
//
//  Created by Wang Yi on 17/4/19.
//
//
/* 
 * Input-Output libraries
 */
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
using std::stringstream;
#include <fstream>

#include <string.h>
#include <string>
using std::string;

#include <map>
using std::map;
using std::pair;
using std::make_pair;

#include <vector>
#include <algorithm>

#include "diff_tree.hpp"

// See definition in README.md
void
flip(TreeNode<int>* root, vector<int>& vals, std::unique_ptr<int[]>& inverse_query) {
    root->wfs([&](TreeNode<int>* curr, int depth) -> bool {
        if (depth % 2 == 1) {
            std::cout << format("flip %d", curr->el()) << std::endl;
            int idx = inverse_query[curr->el()];
            vals[idx] = 1 - vals[idx];
        }
        return true;
    });
}

int
diff(TreeNode<int>* root, vector<int>& initial_vals, vector<int>& final_vals, std::unique_ptr<int[]>& inverse_query)
{
    int op = 0;
    root->wfs([&](TreeNode<int>* curr, int depth) -> bool {
        int idx = inverse_query[curr->el()];
        if (initial_vals[idx] != final_vals[idx]) {
            flip(curr, initial_vals, inverse_query);
            op++;
        }
        return true;
    });
    return op;
}

int main(int argc, char** argv) {
    int N, id, val;
    const std::string DELIMITER=":";
    
    // I/O redirection
    std::ifstream f(getenv("case#1"));
    std::cin.rdbuf(f.rdbuf());
    
    std::cin >> N;
    vector<int> initial_vals, final_vals;
    
    typedef map<int, TreeNode<int>::Ptr> Trees;
    Trees trees;
    TreeNode<int>::Ptr root;
    bool first = true;

    std::unique_ptr<TreeNode<int>::Ptr[] > array(new TreeNode<int>::Ptr[N]);
    std::unique_ptr<int[]> inverse_query(new int[N]);
    
    std::string line;
    std::stringstream split;
    std::string temp;
    
    std::getline(std::cin, line);
    
    int i = 0;
    while (i < N) {
        std::getline(std::cin, line);
        split << line.substr(0, line.find(DELIMITER));
        
        // read parent
        split >> id;
        auto it = trees.find(id);
        // not find it
        TreeNode<int>::Ptr parent;
        if (it != trees.end()) {
            parent = it->second;
        } else {
            parent.reset(new TreeNode<int>(id));
            trees[id] = parent;
            inverse_query[id] = i;
            array[i++] = parent;
        }
        if (first) {
            root = parent;
            first = false;
        }
        
        // read children
        
        split.clear();
        
        split << line.substr(line.find(DELIMITER)+1);
        
        const char SEPARATOR = ',';
        char separator;
        while (split >> id) {
            TreeNode<int>::Ptr nd(new TreeNode<int>(id));
            parent->add(nd);
            trees[id] = nd;
            inverse_query[id] = i;
            array[i++] = nd;
            if (split >> separator && separator != SEPARATOR) {
                break;
            }
        }

        split.clear();
    }
    
    std::getline(std::cin, line); // empty line
    std::getline(std::cin, line);
    split << line.substr(line.find(DELIMITER)+1);
    
    while (split >> val) {
        initial_vals.push_back(val);
    }
    
    split.clear();
    
    std::getline(std::cin, line);
    
    split << line.substr(line.find(DELIMITER)+1);
    while (split >> val) {
        final_vals.push_back(val);
    }
    
    split.clear();
    
    // since the structures of root and root_mirror are exactly the same, we only have one copy of structures and use to id to access their values respectively
    int ops = diff(root.get(), initial_vals, final_vals, inverse_query);
    std::cout << ops << std::endl;
}
