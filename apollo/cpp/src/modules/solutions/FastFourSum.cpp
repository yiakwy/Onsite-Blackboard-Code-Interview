//
//  FastFourSum.cpp
//  ApolloTeam
//
//  Created by Wang Yi on 9/5/19.
//
//

#include "FastFourSum.hpp"

int main(int argc, char** argv)
{
    Solution solver;
    std::vector<int> nums = {1, 0, -1, 0, -2, 2};
    int target = 0;
    
    vector<vector<int>> rets = solver.fourSum(nums, target);
    for (auto ret : rets) {
        for (auto i : ret) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }
}
