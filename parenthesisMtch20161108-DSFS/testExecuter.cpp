//
//  main.cpp
//  parenthesis_mtch
//
//  Created by Wang Yi on 14/11/16.
//  Copyright (c) 2016 Wang Yi. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <string>
#include "parenthesis_mtch.h"

using std::string;
using std::getline;
using std::cin;

int main(int argc, const char * argv[]) {
    
    string line;
    getline(cin, line);
    parenthesis_mtch(line.c_str(), (int)line.length());
    std::cout << std::endl;
    return 0;
}
