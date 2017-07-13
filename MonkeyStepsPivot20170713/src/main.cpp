//
//  main.cpp
//  monkey_step
//
//  Created by Wang Yi on 13/7/17.
//  Copyright © 2017 Wang Lei. All rights reserved.
//

#include <iostream>
#include "monkey_step.hpp"

int main(int argc, const char * argv[]) {
    // insert code here...
    vector<int> A = {1, -1, -1, 2, 0, 5};
    int D = 3;
    int ret = solution(A, D);
    std::cout << "we got " << ret << " seconds"
              << " where the expected answer is " << 1 << std::endl
              << "i.e. at second '2', jump to position 0, 3, 4, finally 6" << std::endl
    << "      start 0  1  2  3  4  5  end " << std::endl
    << " t= 2       ok -  - ok ok  -  end " << std::endl;
    return 0;
}
