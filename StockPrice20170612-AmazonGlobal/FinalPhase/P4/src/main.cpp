//
//  main.cpp
//  StockAnalyze
//
//  Created by Wang Yi on 13/6/17.
//  Copyright © 2017 Wang Lei. All rights reserved.
//

#include <iostream>
#include "stock_analyzer.hpp"

int main(int argc, const char * argv[]) {
    double stocks[] = {10, 8, 5, 9, 8, 6, 7, 12, 9}; //{-2, -3, 4, -1, -2, 1, 5, -3};
    int len = sizeof(stocks) / sizeof(double);
    double* diff = array2accumulated<double>(stocks, len);
    double ret = max_seq_sum(0, diff, len-1);
    std::cout << "final max revenue is: " << ret << std::endl;
    delete[] diff;
    return 0;
}
