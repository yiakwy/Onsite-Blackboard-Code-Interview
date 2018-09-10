//
//  main.cpp
//  ast
//
//  Created by Wang Yi on 30/4/17.
//  Copyright © 2017 Wang Lei. All rights reserved.
//

#include <iostream>
#include <string>
#include "token.hpp"
#include "ast.hpp"

using std::getline;
using std::string;

int main(int argc, const char * argv[]) {
    string line, repr="";
    queue<Token> q;
    vector<Token> ret;
    size_t size = 0;
    
    ast semantic_analyzer;
    //  getline(std::cin, line);
    line = "3 + 4 * 2 / exp( 1 - 5, 2 )";
    
    Token* tokens = lexer(line.c_str(), (int)line.length(), &size);
    q = semantic_analyzer.postfix_Expr(tokens, size);
    
    while(!q.empty())
    {
        if (repr == "")
            repr += string(q.front().content);
        else repr += "," + string(q.front().content);
        ret.push_back(q.front());q.pop();
    }
    
    std::cout << "postfix arrangement:" << repr << std::endl;
    semantic_analyzer.ast_builder(ret);
    
    // tree segmentation algorithm
    
    
    return 0;
}
