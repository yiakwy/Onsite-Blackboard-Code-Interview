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
#define VISITED true
#define NOT_VISITED false
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

int ReadTwoOperants(std::vector<bool>& visited, const std::vector<int>& nums, std::stack<int>& operants, std::stack<std::string>& path, int* depth) {
    int flag = 1;
    int i=0;
    while (operants.size() < 2) {
        
        if (i >= nums.size())
            break;
        if (visited[i] != NOT_VISITED) {
            i++;
            continue;
        }
        operants.push(nums[i]);
        path.push(std::to_string(nums[i]));
        visited[i] = VISITED;
        *depth += 1;
        i++;
        
    }
    
    if (operants.size() < 2)
        flag = NOT_APPLICABLE;
    
    return flag;
}

int calc(char operator_symbol, int left, int right, int* ret)
{
    int flag = 1;
    switch(operator_symbol)
    {
        case '+':
            *ret = left + right;
            break;
        case '-':
            *ret = left - right;
            break;
        case '*':
            *ret = left * right;
            break;
        case '/':
            if (right == 0) {
                flag = NOT_APPLICABLE;
                break;
            }
            *ret = left / right;
            break;
    }
    return flag;
}

void recursive_routine(std::vector<Token>& operator_symbols, std::stack<Token> operators, std::stack<int> operants, std::vector<bool> visited, const std::vector<int>& nums, int depth, int depth0, int unmtched, vector<std::string>& ret, std::stack<std::string>& path) {
    if (depth >= nums.size()) {
        int val = pop(operants);
        std::string expr = pop(path);
        if (val == 24) {
            ret.push_back(expr);
        }
        return;
    }
    
    if (depth0 >= nums.size()-1) {
        int val;
        if (unmtched != 0)
            return;
        while (!operators.empty()) {
            int left, right, ret;
            int flag;
            flag = ReadTwoOperants(visited, nums, operants, path, &depth);
            right = pop(operants);
            left = pop(operants);
            calc(operators.top().op, left, right, &ret);
            operants.push(ret);
            std::string rexpr = pop(path);
            std::string lexpr = pop(path);
            path.push(lexpr + std::string(1, operators.top().op) + rexpr);
            operators.pop();
        }
        val = pop(operants);
        std::string expr = pop(path);
        if (val == 24) {
            ret.push_back(expr);
        }
        return;
    }
    
    Token tok;
    
    for (int i=0; i < operator_symbols.size(); i++) {
        tok = operator_symbols[i];
        
        switch(tok.op) {
            case '(':
                if (depth == 0 && unmtched >= nums.size() - 2)
                    continue;
                if (depth != 0 && unmtched >= nums.size() - depth - 1)
                    continue;
                operators.push(tok);
                unmtched++;
                
                recursive_routine(operator_symbols, operators, operants, visited, nums, depth, depth0, unmtched, ret, path);
                
                unmtched--;
                operators.pop();
                break;
            case ')':
            {
                if (operators.empty())
                    continue;
                if (operators.top().op == '(')
                    continue;
                std::stack<Token> ori_operators = operators;
                std::stack<int> ori_operants = operants;
                std::vector<bool> ori_visited = visited;
                int ori_depth = depth;
                std::stack<std::string> ori_path = path;
                
                while (!operators.empty() && operators.top().op != '(')
                {
                    int left, right, ret;
                    int flag;
                    flag = ReadTwoOperants(visited, nums, operants, path, &depth); // only 1 or 0 to be readed;
                    if (flag == NOT_APPLICABLE) {
                        // !
                    } else {
                        right = pop(operants);
                        left = pop(operants);
                        calc(operators.top().op, left, right, &ret);
                        operants.push(ret);
                        std::string lexpr, rexpr;
                        rexpr = pop(path);
                        lexpr = pop(path);
                        path.push(lexpr + std::string(1, operators.top().op) + rexpr);
                        operators.pop();
                    }
                    
                }
                if (operators.empty())
                {
                    operators = ori_operators;
                    operants = ori_operants;
                    visited = ori_visited;
                    depth = ori_depth;
                    path = ori_path;
                    break;
                }
                operators.pop();
                unmtched--;
                std::string expr = pop(path);
                path.push(std::string(1, '(') + expr + std::string(1, ')'));
                
                recursive_routine(operator_symbols, operators, operants, visited, nums, depth, depth0, unmtched, ret, path);
                
                operators = ori_operators;
                operants = ori_operants;
                visited = ori_visited;
                depth = ori_depth;
                unmtched++;
                path = ori_path;
                break;
            }
            default:
            {
                std::stack<Token> ori_operators = operators;
                std::stack<int> ori_operants = operants;
                std::vector<bool> ori_visited = visited;
                int ori_depth = depth;
                std::stack<std::string> ori_path = path;
                
                if (operators.empty()) {
                    operators.push(tok);
                } else if (tok.assoc_level < operators.top().assoc_level) {
                    while (tok.assoc_level < operators.top().assoc_level) {
                        
                        int left, right, ret;
                        int flag;
                        flag = ReadTwoOperants(visited, nums, operants, path, &depth);
                        if (flag == NOT_APPLICABLE) {
                            // !
                        } else {
                            right = pop(operants);
                            left = pop(operants);
                            calc(operators.top().op, left, right, &ret);
                            operants.push(ret);
                            std::string lexpr, rexpr;
                            rexpr = pop(path);
                            lexpr = pop(path);
                            path.push(lexpr + std::string(1, operators.top().op) + rexpr);
                            operators.pop();
                            
                        }
                        
                    }
                    operators.push(tok);
                    
                } else {
                    operators.push(tok);
                }
                
                recursive_routine(operator_symbols, operators, operants, visited, nums, depth, depth0+1, unmtched, ret, path);
                
                operators = ori_operators;
                operants = ori_operants;
                visited = ori_visited;
                depth = ori_depth;
                path = ori_path;
            }
        } // endofswitch
        
    }
    
}

class Solution {
public:
    bool judgePoint24(vector<int>& nums) {
        std::vector<std::string> ret;
        std::stack<std::string> path;
        
        std::vector<Token> operator_symbols = {
            {'(', -1},
            {')', -1},
            {'+', 0},
            {'-', 0},
            {'*', 1},
            {'/', 1},
        };
        
        std::stack<Token> operators;
        std::stack<int> operants;
        
        int cur;
        int depth, depth0, unmtched;
        std::vector<bool> visited(nums.size(), false);
        
        recursive_routine(operator_symbols, operators, operants, visited, nums, depth, depth0, unmtched, ret, path);
        
        if (ret.size() > 0) {
            for (auto expr : ret) {
                std::cout << expr << std::endl;
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
