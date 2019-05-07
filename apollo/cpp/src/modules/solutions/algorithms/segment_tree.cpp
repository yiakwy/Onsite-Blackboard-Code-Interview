//
//  segmetn_tree.cpp
//  ApolloTeam
//
//  Created by Wang Yi on 5/5/19.
//
//

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
using std::stringstream;
#include <fstream>

#include <string.h>
#include <string>
using std::string;

#include "segment_tree.hpp"

int main(int argc, char** argv)
{
    int N, val, i=0;
    
    // if (getenv("case#1")) {
        // I/0 redirection
        std::cout << "Input file: "<< getenv("case#1") << std::endl;
        std::ifstream f(getenv("case#1"));
        std::cin.rdbuf(f.rdbuf());
    // }

    double *array, *init_vals;
    std::string line;
    std::stringstream split;
    
    std::cin >> N;
    
    array = new double[N];
    init_vals = new double[N];
    for (int j=0; j < N; j++) {
        init_vals[j] = 0;
    }
    
    std::getline(std::cin, line); // empty line
    std::getline(std::cin, line);
    split << line;
    
    while (i < N) {
        split >> val;
        array[i++] = val;
    }
    
    split.clear();
    TreeNode* root = new TreeNode(0, N, init_vals);
    root->insert_impl(0, N, array); //  build array
    
    std::cout << "Sum of values for given array = " << root->sum(0, 3) << std::endl;
    
    array[1] = 10; // +7
    root->insert_impl(1, 10);
    
    std::cout << "Sum of values in range [0, 3) = " << root->sum(0, 3) << std::endl;
    
    array[0] = 2; // +1
    array[2] = 6; // +1
    root->insert_impl(0, 2, array);
    
    std::cout << "Sum of values in range [0, 3) = " << root->sum(0, 3) << std::endl;
    
}
