//
//  main.cpp
//  sample
//
//  Created by Wang Yi on 23/8/17.
//  Copyright © 2017 Wang Lei. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include <strstream>
#include <sstream>
#include <string>

#include <vector>
using std::vector;

#include "test.hpp"

#ifndef POINT_IMPL
#define POINT_IMPL
struct Point {
    double x;
    double y;
public:
    Point(double _x, double _y): x(_x), y(_y){}
};
#endif

int main(int argc, const char * argv[])
{
    int N;
    std::cout << "input number of points: ... " << std::endl;
    std::cin >> N;
    vector<Point> inp;
    vector<Point*> out;
    vector<double> item(2);
    
    std::stringstream split;
    std::string line;
    double temp;
    
    std::getline(std::cin, line);
    
    std::cout << "get points" << std::endl;
    int i=0, j;
    while (i++ < N) {
        std::getline(std::cin, line);
        split << line;
        j = 0;
        while (split >> temp) {
            item[j++] = temp;
        }
        split.clear();
        inp.push_back(Point(item[0], item[1]));
    }
    
    std::cout << "get inputs" << std::endl;
    for (auto p : inp) {
        std::cout << "(" << p.x << "," << p.y << ")" << " ";
    }
    std::cout << std::endl;
    
    out = solution(inp, N);
    
    for (auto item : out) {
        std::cout << item->x << " " << item->y << std::endl;
    }
}