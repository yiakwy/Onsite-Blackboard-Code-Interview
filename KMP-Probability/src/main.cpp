//
//  main.cpp
//  KMP_Prob
//
//  Created by Wang Yi on 19/3/17.
//  Copyright © 2017 Wang Yiyiak.co. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <string>
using std::string;

#include "kmp.h"
#include "logging.hpp"
#include "programming.hpp"

int main(int argc, const char * argv[]) {
    
    globalInit(argc, argv);
    
    string txt, pttn;
    txt = "HERE IS A SIMPLE EXAMPLE";
    pttn = "EXAMPLE";
    //pttn =  "ABACABABC";
    // pattern_find(txt.c_str(), txt.length(), pttn.c_str(), pttn.length());
    
    int l = 6;
    double pb;
    
    pttn = "ABB";
    kmp_pb solver(l, pttn.c_str(), pttn.length(), 2);
    pb = solver.P(0, 0, l);
    
    LOG(INFO) << boost::format("Given a text M of length %1%, the probability of string <P> : %2% in <M> is: %3%") % l % pttn % pb << std::endl;
    
    pttn = "BBA";
    kmp_pb solver2(l, pttn.c_str(), pttn.length(), 2);
    pb = solver2.P(0, 0, l);
    
    LOG(INFO) << boost::format("Given a text M of length %1%, the probability of string <P> : %2% in <M> is: %3%") % l % pttn % pb << std::endl;
    return 0;
}
