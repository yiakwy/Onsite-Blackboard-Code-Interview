//
//  FastFourSum.hpp
//  ApolloTeam
//
//  Created by Wang Yi on 9/5/19.
//
//  Status: INCORRECT

#ifndef FastFourSum_hpp
#define FastFourSum_hpp

#include <unordered_map>
using std::unordered_map;
#include <vector>
using std::vector;
#include <queue>
#include <iostream>
#include <algorithm>

using Map = unordered_map<int, int>;


bool SumTwo(vector<int>& operants, int target, vector<vector<int>>& rets) {
    bool flag = false;
    Map query_cache;
    for (int i=0; i < operants.size(); i++) {
        int complement = target - operants[i];
        if (query_cache.find(complement) != query_cache.end()) {
            flag = true;
            vector<int> ret;
            ret.push_back(complement);
            ret.push_back(operants[i]);
            rets.push_back(ret);
            query_cache[complement]--;
            if (query_cache[complement] == 0) {
                query_cache.erase(complement);
            }
        }
        if (query_cache.find(operants[i]) != query_cache.end()) {
            query_cache[operants[i]]++;
        } else {
            query_cache[operants[i]] = 1;
        }
    }
    return flag;
}

bool routine(vector<int>& operants, int tosum, int target, vector<vector<int>>& rets)
{
    int i;
    bool flag = false;
    
    if (tosum == 2) {
        SumTwo(operants, target, rets);
    }
    
    for (i=0; i < operants.size(); i++) {
        if (i > 0) {
            while (operants[i] == operants[i-1]) i++;
        }
        vector<int> res(operants.begin()+i+1, operants.end());
        vector<vector<int>> right_rets;
        
        routine(res, tosum-1, target - operants[i], right_rets);
        
        if (right_rets.size() > 0) {
            for (auto right_ret : right_rets) {
                vector<int> ret;
                ret.push_back(operants[i]);
                for (auto el : right_ret) {
                    ret.push_back(el);
                }
                rets.push_back(ret);
            }
       
        }
        
    }
    
    return flag;

}

class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> rets;
        
        std::sort(nums.begin(), nums.end());
        
        routine(nums, 4, target, rets);
        return rets;
    
    }
    
};

#endif /* FastFourSum_hpp */
