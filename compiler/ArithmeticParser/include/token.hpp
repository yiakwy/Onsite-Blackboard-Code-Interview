//
//  token.hpp
//  ast
//
//  Created by Wang Yi on 30/4/17.
//  Copyright © 2017 Wang Lei. All rights reserved.
//

#ifndef token_hpp
#define token_hpp

#include <regex.h>
#include <cstring>
#include <iostream>
#include <string>

using std::string;

#define lowest_order -1
#define highest_order 10

#define Malloc(type, len) \
    (type*) malloc(sizeof(type)*len)

#define STRINGLIB(F) Symbol_##F

#define FOR(s, e) \
    for(s=0; s < e; s++) {
#define END ;}

// simple token
typedef struct _Op {
    const char* def;
    int id;
    int args_len;
    int assoc;
    int priority;
    regex_t re;
} Operator;

typedef long long ll;

typedef struct _token {
    int type;
    int id;
    char* content;
    ll len;
    //_token& operator=(_token &other);
    inline bool operator!=(_token &other);
    inline bool operator==(_token &other);
} Token;

static Token NOT_FOUND = {-1, -1};

bool
Token::operator==(Token &other)
{
    if (this != &other)
    {
        if (this->type == other.type &&
            this->id == other.id &&
            this->len == other.len &&
            strcmp(this->content, other.content) == 0) return true;
        else return false;
    } else return this == &other ? true : false;
}

bool
Token::operator!=(Token &other)
{
    return !(*this == other);
}
/*
Token&
Token::operator=(Token &other)
{
    if (this != &other)
    {
        this->type = other.type;
        this->id = other.id;
        this->content = other.content;
        this->len = other.len;
    }
    return *this;
}
*/
 
enum assoc {LEFT_ASSC, RIGHT_ASSC, NONE};
#define Number    1000
#define Symbol    1001
#define Separator 1002


#define Digit "^[-+]?[0-9]*\\.?[0-9]+([eE][-+]?[0-9]+)?"
#define Alphabet "^[a-zA-Z_][a-zA-Z_0-9]*"
#define White_Space "^[ ]+"
#define COMMA "^,"

static regex_t Digit_RE;
static regex_t Alphabet_RE;
static regex_t COMMA_RE;
static regex_t WHITE_SPACE_RE;

#define exp (Symbol+100)
#define log (Symbol+101)

static Operator operators[] = {
    { "^\\("   , '('    , 0, NONE, lowest_order},
    { "^\\)"   , ')'    , 0, NONE, highest_order},
    { "^\\+"   , '+'    , 2, LEFT_ASSC, 1},
    { "^-"     , '-'    , 2, LEFT_ASSC, 1},
    { "^\\*"   , '*'    , 2, LEFT_ASSC, 2},
    { "^/"     , '/'    , 2, LEFT_ASSC, 2},
    // regex does not support lookahead or lookbehind
    { "^exp"  , exp     , 2, LEFT_ASSC, 3},
    { "^log"  , log     , 1, LEFT_ASSC, 3},
    // conflicted with above token defs
    // accepted inputs undfined
    { Alphabet , Symbol ,-1, LEFT_ASSC, 3}
};

#define OPEN_PARA  '('
#define CLOSE_PARA ')'
#define PLUS       '+'
#define MINUS      '-'
#define MULTIPLY   '*'
#define DIVISION   '/'

#define Operator_Type 1
#define Operand 2

#define EXEC_FAILURE 1
#define EXEC_SUCC 0

int global_init();
Token mtch(const char* str);
Token* lexer(const char* str, int len, size_t* count);
Operator* get_operator(int id);

#endif /* token_hpp */
