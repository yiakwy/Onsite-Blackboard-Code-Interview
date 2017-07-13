//
//  monkey_step.cpp
//  monkey_step
//
//  Created by Wang Yi on 13/7/17.
//  Copyright © 2017 Wang Lei. All rights reserved.
//

#include "monkey_step.hpp"

int
find_max(vector<int> &A) {
    int max = INT_MIN;
    for (auto el : A) {
        if (max < el) max = el;
    }
    return max;
}

int solution(vector<int> &A, int D) {
    size_t N = A.size();
    int T = find_max(A);
    
    int i, k=N, tmin, ret=-1;
    set<int> visited;
    stack<int> s;
    int search = 0;
    
    if (T < 0) {return -1;};
    if (D > N) {return 1;};
    
    for (i=1; i <= D; i++)
    {
        k = N;
        s.push(k-i);
        tmin = A[k-i];
        
        while (!s.empty()) {
            
            k = s.top(); s.pop();
            
            if (k < 0) {
                
                if (ret > tmin ||  ret == -1) {
                    ret = tmin;
                    std::cout << "find a result " << tmin << std::endl;
                }
                
                // we reach the end of this solution
                continue;
            }
            
            if (visited.find(k) != visited.end()) {visited.insert(k);}
            
            // we must have tmin >= A[k]
            if (tmin < A[k])
                tmin = A[k];
            
            if (tmin > ret && ret != -1)
                // truncate
                continue;
            
            for (int j=D; j >=1; j--) {
                s.push(k - j);
            }
            
        }
        
    }
    
    return ret;
}
