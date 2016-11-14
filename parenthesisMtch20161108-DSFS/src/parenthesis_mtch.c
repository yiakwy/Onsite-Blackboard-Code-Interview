//
//  parenthesis_mtch.cpp
//  parenthesis_mtch
//
//  Created by Wang Yi on 14/11/16.
//  Copyright (c) 2016 Wang Yi. All rights reserved.
//

#include "parenthesis_mtch.h"
#define FOR(START, END) \
    for (START=0; (START) < (END); (START)++){
#define END ;}

#define OPEN  '('
#define CLOSE ')'
#define UNDEF '?'

int parenthesis_mtch(const char* array, int l)
{
    int i;
    int head = 0;
    int* symbolTab_stack = Malloc(int, l);
    char* out  = Malloc(char, l);
  
    FOR(i, l)
    out[i] = UNDEF;
    END
    
    FOR(i, l)
        if (array[i] == OPEN)
            symbolTab_stack[head++] = i;
        else if (array[i] == CLOSE && head !=0) {
            out[symbolTab_stack[head-1]] = OPEN;
            out[i] = CLOSE;
            head--;
        }
    END
    
    FOR(i, l)
        //if (symbolTab_stack[i] != UNDEF)
            printf("%c", out[i]);
    END
 
    free(symbolTab_stack);
    free(out);
    symbolTab_stack = NULL;
    out = NULL;
    return 0;
}
