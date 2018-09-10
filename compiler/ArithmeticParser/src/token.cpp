//
//  token.cpp
//  ast
//
//  Created by Wang Yi on 30/4/17.
//  Copyright © 2017 Wang Lei. All rights reserved.
//

#include "token.hpp"

int global_init()
{
    int i, rule_len = sizeof(operators) / sizeof(Operator);
    
    if (regcomp(&Alphabet_RE, Alphabet, REG_NEWLINE|REG_EXTENDED))
        return EXEC_FAILURE;
    
    if (regcomp(&Digit_RE, Digit, REG_NEWLINE|REG_EXTENDED))
        return EXEC_FAILURE;
    
    if (regcomp(&COMMA_RE, COMMA, REG_NEWLINE|REG_EXTENDED))
        return EXEC_FAILURE;
    
    if (regcomp(&WHITE_SPACE_RE, White_Space, REG_NEWLINE|REG_EXTENDED))
        return EXEC_FAILURE;
    
    FOR(i, rule_len)
    if (regcomp(&(operators[i].re), operators[i].def, REG_NEWLINE|REG_EXTENDED))
        return EXEC_FAILURE;
    END
    
    return EXEC_SUCC;
}

Token mtch(const char* str)
{
    int i, rule_len = sizeof(operators) / sizeof(Operator);
    Token ret;
    regmatch_t mtched;
    ret.len = 0;
    
    if (regexec(&WHITE_SPACE_RE, str, 1, &mtched, REG_NOTEOL) == 0)
    {
        ret.len += mtched.rm_eo - mtched.rm_so;
        str = str + ret.len;
    }
    
    if (regexec(&Digit_RE, str, 1, &mtched, REG_NOTEOL) == 0)
    {
        ret.type = Operand;
        ret.len += mtched.rm_eo - mtched.rm_so;
        ret.id = Number;
        ret.content = new char[ret.len+1];
        strncpy(ret.content, str + mtched.rm_so, mtched.rm_eo - mtched.rm_so);
        ret.content[ret.len] = '\0';
        return ret;
    }
    
    if (regexec(&COMMA_RE, str, 1, &mtched, REG_NOTEOL) == 0)
    {
        ret.type = Operator_Type;
        ret.len += mtched.rm_eo - mtched.rm_so;
        ret.id = Separator;
        ret.content = new char[ret.len+1];
        strncpy(ret.content, str + mtched.rm_so, mtched.rm_eo - mtched.rm_so);
        ret.content[ret.len] = '\0';
        return ret;
    }

    
    FOR(i, rule_len - 1)
    if (regexec(&(operators[i].re), str, 1, &mtched, REG_NOTEOL))
        continue;
    
    ret.type = Operator_Type;
    ret.len += mtched.rm_eo - mtched.rm_so;
    ret.id = operators[i].id;
    ret.content = new char[ret.len+1];
    strncpy(ret.content, str + mtched.rm_so, mtched.rm_eo - mtched.rm_so);
    ret.content[ret.len] = '\0';
    return ret
    END

    if (regexec(&Alphabet_RE, str, 1, &mtched, REG_NOTEOL) == 0)
    {
        ll span = mtched.rm_eo - mtched.rm_so;
        ret.type = Operator_Type; // or Operand
        ret.len += span;
        ret.id = Symbol;
        ret.content = new char[ret.len+1];
        strncpy(ret.content, str + mtched.rm_so, span);
        ret.content[ret.len] = '\0';
        return ret;
    }
    
    return NOT_FOUND;
}

Token* lexer(const char* str, int len, size_t* count)
{
    
    Token* tokens = new Token[len];
    int size = 0;
    
    Token tok = NOT_FOUND;
    global_init();
    
    std::cout << "token lexer:" << std::endl;
    
    while(*str != '\0' &&
          (tok = mtch(str)) != NOT_FOUND){
        tokens[size++] = tok;
        str = str + tok.len;
        std::cout << "< tok: \"" << string(tok.content) << "\" > ";
    }
    std::cout << std::endl;
    std::cout << "There are totally " << size << " tokens parsed!" << std::endl;
    *count = size;
    return tokens;
}

Operator* get_operator(int id)
{
    int i, rule_len = sizeof(operators) / sizeof(Operator);
    FOR(i, rule_len)
    if (operators[i].id == id)
        return operators+i;
    END
    return nullptr;
}