//
//  FastFourSum.hpp
//  ApolloTeam
//
//  Created by Wang Yi on 9/5/19.
//
//

#ifndef FastFourSum_hpp
#define FastFourSum_hpp

#include <unordered_map>
using std::unordered_map;
// #include <map>
// using std::map;
#include <vector>
using std::vector;
#include <queue>
#include <iostream>
#include <algorithm>

using Map = unordered_map<int, int>;
// using Map = map<int, int>;

void merge(vector<int>& left, vector<int>& right, vector<int>ret) {
    int i=0, j=0;
    ret.resize(4);
    vector<int>::iterator p = ret.begin();
    while (true) {
        if (i == left.size())  {std::copy(right.begin()+j, right.end(), p); return;}
        if (j == right.size()) {std::copy(left.begin()+i, left.end(), p); return;}
        *p++ = left[i] < right[j] ? left[i++] : right[j++];
    }
    
}

#define NOT_AVAILABLE -1

void twoSum(vector<int>& array, int target, Map& query, vector<vector<int>>& ret)
{
    for (int i=0; i < array.size(); i++)
    {
        if (query[array[i]] == NOT_AVAILABLE)
            continue;
        int cl = target - array[i];
        if (array[i] >= cl)
            continue;
        if (query.find(cl) != query.end())
        {
            if (query[cl] == i || query[cl] == NOT_AVAILABLE) {
                continue;
            }
            vector<int> sol;
            sol.push_back(i);
            sol.push_back(query[cl]);
            ret.push_back(sol);
        }
    }
}

class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        Map query, twosum1;
        vector<vector<int>> ret;
        for (int i=0; i < nums.size(); i++) {
            query[nums[i]] = i;
            twosum1[nums[i]] = i;
        }
        
        std::priority_queue<int, vector<int>> topk_min(nums.begin(), nums.begin()+3);
        std::priority_queue<int, vector<int>, std::greater<int>> topk_max(nums.begin(), nums.begin()+3);
        
        for (int i=3+1; i < nums.size(); i++) {
            
            if (nums[i] > topk_max.top()) {
                topk_max.pop();
                topk_max.push(nums[i]);
            }
            
            if (nums[i] < topk_min.top()) {
                topk_min.pop();
                topk_min.push(nums[i]);
            }
        }
        
        int max=0, min=0;
        while(!topk_max.empty()) {
            max+= topk_max.top(); topk_max.pop();
        }
        
        std::cout << "Max of 4 sum: " << max << std::endl;
        
        while(!topk_min.empty()) {
            min+= topk_min.top(); topk_min.pop();
        }
        
        std::cout << "Min of 4 sum: " << min << std::endl;
        
        vector<vector<int>> left, right;
        vector<int> leftsol, rightsol;
        for (int i=min; i < (max + min) / 2 + 1; i++)
        {
            left.clear();
            right.clear();
            
            twoSum(nums, i, twosum1, left);
            if (left.size() > 0)
            {
                for (auto indexesLeft : left) {
                    leftsol.clear();
                    for (auto idx : indexesLeft) {
                        query[nums[idx]] = NOT_AVAILABLE;
                        leftsol.push_back(nums[idx]);
                    }
                    
                    twoSum(nums, target - i, twosum1, right);
                    
                    for (auto idx : indexesLeft) {
                        query[nums[idx]] = idx;
                    }
                    
                    if (right.size() > 0) {
                        // add solution
                        for (auto indexesRight : right) {
                            rightsol.clear();
                            vector<int> sol;
                            sol.resize(4);
                            for (auto idx : indexesRight) {
                                rightsol.push_back(nums[idx]);
                            }
                            
                            vector<int>::iterator solptr = sol.begin();
                            std::merge(leftsol.begin(), leftsol.end(), rightsol.begin(), rightsol.end(), solptr);
                            ret.push_back(sol);
                            
                        }
                        
                    }
                    
                } // endfor
                
            }
            
        }
        return ret;
    }
    
};

#endif /* FastFourSum_hpp */
