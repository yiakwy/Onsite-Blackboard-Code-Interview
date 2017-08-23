//
//  test.cpp
//  Docker_Builder
//
//  Created by Wang Yi on 22/8/17.
//  Copyright © 2017 Wang Lei. All rights reserved.
//

// You can refer to https://jtdaugh.github.io/xcode-umich/ for multiple targets bulding using xcode IDE
// If you want to use option parser, here is a tool http://ryngonzalez.github.io/OptionHandler/
#include "test.hpp"
#include <iostream>
using namespace std;

using std::string;

#include <vector>
using std::vector;

#ifndef POINT_IMPL
#define POINT_IMPL
struct Point {
    double x;
    double y;
public:
    Point(double _x, double _y): x(_x), y(_y){}
};
#endif

int
upper_right(Point l, Point r) {
    if ((l.y - r.y) * (l.x - r.x) >= 0) {
        if (l.y >= r.y) return 1;
        else return -1;
    } else return 0;
}

#define get_ref(ob) &(*ob)

vector<Point*>
solution(vector<Point>& inp, int len){
    vector<Point*> ret;
    vector<Point*> suspect;
    for (vector<Point>::iterator it = inp.begin(); it != inp.end(); it++) {
        
        Point* p = get_ref(it);
        if (suspect.empty()){
            suspect.push_back(p);
        } else {
            for (int i=0; i < suspect.size(); i++) {
                Point* cmp = suspect[i];
                int flag = upper_right(*cmp, *p);
                if (flag == 0) {
                    suspect.push_back(p);
                } else {
                    if (flag == -1) {
                         suspect[i] = p;
                    }
                }
            }
        }
        
            }
    
    for (auto item : suspect) {
        ret.push_back(item);
    }
    
    return ret;
}