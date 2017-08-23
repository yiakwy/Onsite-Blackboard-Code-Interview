//
//  main.cpp
//  P2
//
//  Created by Wang Yi on 23/8/17.
//  Copyright © 2017 Wang Lei. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include <string>
using std::string;
#include <sstream>
using std::stringstream;

#include <vector>
using std::vector;

int min_as_pivot(vector<int> &inp, int start, int end, int* min)
{
    int i, min_id=start;
    *min = inp[start];
    for (i=start + 1; i < end; i++) {
        if (*min < inp[i]) {
            min_id = i;
            *min = inp[i];
        }
    }
    return min_id;
}

inline int triple_max(int a, int b, int c){
    int max_1 = a < b? b:a;
    int max_2 = max_1 < c?c:max_1;
    return max_2;
}

int main_routine(vector<int> &inp, int start, int end){
    
    if (end - start == 1 || end - start <= 0) {
        return inp[start] * inp[start];
    }
    
    int min;
    int pivot = min_as_pivot(inp, start, end, &min);
    
    int left = main_routine(inp, start, pivot);
    int right = main_routine(inp, pivot+1, end);
    return triple_max(left, right, min * (end - start));
}

int
solution(vector<int> &inp, int len) {
    return main_routine(inp, 0, len);
}

int main(int argc, const char * argv[]) {
    int N;
    std::cout << "input number of el" << std::endl;
    std::cin >> N;
    
    std::string line;
    std::stringstream split;
    
    vector<int> inp(N);
    int out;
    
    int temp;
    int i=0;
    // if inp string is larger than MAX(int), use array[int] to represent, but I think we don't need to disscuss the problem here.
    std::getline(std::cin, line); // discard '\n'
    std::getline(std::cin, line);
    
    split << line;
    
    while (split >> temp) {
        inp[i++] = temp;
    }
    
    out = solution(inp, N);
    std::cout << out << std::endl;
}
