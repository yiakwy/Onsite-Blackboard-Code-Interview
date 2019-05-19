//
//  twenty-four.cpp
//  ApolloTeam
//
//  Created by Wang Yi on 13/5/19.
//
//
#include <iostream>

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <stack>
using std::stack;

#include <map>
using std::map;

#include <numeric>
using std::accumulate;

using Map = std::map<int, int>;

#define NOT_FOUND -1
#define NOT_APPLICABLE -1

template<typename Type>
Type pop(std::stack<Type>& h) {
    Type ret = h.top();
    h.pop();
    return ret;
}

struct Token {
    char op;
    int assoc_level;
    
};

struct TreeNode {
    TreeNode* left;
    TreeNode* right;
    bool isleaf;
    Token tok;
    int val;
    
    TreeNode() {
        left = nullptr;
        right = nullptr;
        isleaf = true;
    }
    
    std::string
    infix_travel_dump () {
        if (isleaf) {
            return std::to_string(val);
        }
        
        std::string sleft = left->infix_travel_dump();
        std::string sright = right->infix_travel_dump();
        
        if (!(left->isleaf) && tok.assoc_level > left->tok.assoc_level) {
            sleft = std::string(1, '(') + sleft + std::string(1, ')');
        }
        
        if (!(right->isleaf) && tok.assoc_level > right->tok.assoc_level) {
            sright = std::string(1, '(') + sright + std::string(1, ')');
        }
        
        return sleft + std::string(1, tok.op) + sright;
        
    }
    
};

void routine(vector<int>& nums, vector<TreeNode>& operants, std::vector<Token>& operator_symbols, vector<std::string>& rets)
{
    if (nums.size() == 1) {
        if ((int)nums[0] == 24) {
            TreeNode root = operants[0];
            std::string ret = root.infix_travel_dump();
            rets.push_back(ret);
        }
        return;
    }
    
    vector<int> nums_1;
    vector<TreeNode> operants_1;
    
    int a, b;
    for (int i=0; i < nums.size(); i++) {
        a = nums[i];
        for (int j=i+1; j < nums.size(); j++) {
            b = nums[j];
            
            nums_1.clear();
            operants_1.clear();
            
            for (int k=0; k < nums.size(); k++) {
                if (k != i && k != j) {
                    nums_1.push_back(nums[k]);
                    operants_1.push_back(operants[k]);
                }
            }
            
            nums_1.push_back(-1);
            TreeNode nd;
            nd.isleaf = false;
            operants_1.push_back(nd);
            
            for (Token tok : operator_symbols) {
                
                TreeNode& nd = operants_1[operants_1.size()-1];
                nd.tok = tok;

                if (tok.op == '+') {
                    nd.val = nums_1[nums_1.size()-1] = a + b;
                    
                    nd.left = &operants[i];
                    nd.right = &operants[j];

                    routine(nums_1, operants_1, operator_symbols, rets);
                } else if (tok.op == '-') {
                    nd.val = nums_1[nums_1.size()-1] = a - b;
                    
                    nd.left = &operants[i];
                    nd.right = &operants[j];
                    
                    routine(nums_1, operants_1, operator_symbols, rets);

                    nd.val = nums_1[nums_1.size()] = b - a;
                    
                    nd.left = &operants[j];
                    nd.right = &operants[i];
                    
                    routine(nums_1, operants_1, operator_symbols, rets);
                } else if (tok.op == '*') {
                    nd.val = nums_1[nums_1.size()-1] = a * b;
                    
                    nd.left = &operants[i];
                    nd.right = &operants[j];
                    
                    routine(nums_1, operants_1, operator_symbols, rets);
                } else if (tok.op == '/') {
                    if (b != 0) {
                        nd.val = nums_1[nums_1.size()-1] = a / (b * 1.0f);
                        
                        nd.left = &operants[i];
                        nd.right = &operants[j];
                        
                        routine(nums_1, operants_1, operator_symbols, rets);
                    }
                    if (a != 0) {
                        nd.val = nums_1[nums_1.size()-1] = b / (a * 1.0f);
                        
                        nd.left = &operants[j];
                        nd.right = &operants[i];
                        
                        routine(nums_1, operants_1, operator_symbols, rets);
                    }
              
                }
            
            }
            
        }
   
    }
    
}

class Solution {
public:
    bool judgePoint24(vector<int>& nums) {
        std::vector<std::string> rets;
        
        std::vector<Token> operator_symbols = {
            {'(', -1},
            {')', -1},
            {'+', 0},
            {'-', 0},
            {'*', 1},
            {'/', 1},
        };
        
        std::vector<TreeNode> operants;
        
        for (int i=0; i < nums.size(); i++) {
            TreeNode nd;
            nd.val = nums[i];
            operants.push_back(nd);
        }
        
        routine(nums, operants, operator_symbols, rets);
        
        if (rets.size() > 0) {
            for (auto ret : rets) {
                std::cout << ret << std::endl;
            }
            return true;
        } else {
            return false;
        }
        
    }
    
};

int main(int argc, char** argv)
{
    Solution sol;
    
    std::vector<int> nums = {4, 1, 8, 7};
    
    bool ret = sol.judgePoint24(nums);

    return 0;
}
