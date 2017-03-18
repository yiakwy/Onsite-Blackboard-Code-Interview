//
//  kmp.c
//  Cyclic_Moving
//
//  Created by Wang Yi on 15/5/16.
//  Copyright (c) 2016 Wang Yi. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include "kmp.h"

#define Malloc(type, len) \
    (type*)malloc(sizeof(type)*len)
#define NOT_FOUND -1

void GetNext(const char* pttn, int steps[])
{
    size_t size = strlen(pttn);
    steps[0] = NOT_FOUND;
    int mtched = NOT_FOUND;
    int pos = 0;
    
    // or mtched = 0, pos = 1
    while(pos < size-1)
    {
        if (mtched == NOT_FOUND || pttn[pos] == pttn[mtched])
        {
            steps[++pos] = ++mtched;
        }
        else {
            mtched = steps[mtched];
        }
    }
}

// worst performance 2*N ~ (2-1/M)*N
// worst performance for improved KMP_step
void GetNext2(char* pttn, int steps[])
{
    size_t size = strlen(pttn);
    steps[0] = NOT_FOUND;
    int mtched = NOT_FOUND;
    int pos = 0;
    // or mtched = 0, curr =1
    while(pos < size-1)
    {
        if(mtched == NOT_FOUND || pttn[pos] == pttn[mtched])
        {
            // steps[++pos] = ++mtched;
            // steps[pos] <= steps[mtched] if pttn[mtched] == pttn[steps[mtched]] \
            //                               else mtched;
            steps[++pos] = ++mtched;
        } else {
            int next_step = steps[mtched];
            if (pttn[mtched] == pttn[next_step])
            {
                mtched = steps[next_step];
            }
            else mtched = next_step;
        }
    }
}

size_t pattern_find(const char* t, size_t len, char* pttn)
{
    size_t pttn_len = strlen(pttn);
    int* steps = Malloc(int, pttn_len);
    size_t curr = 0;
    int mtched = 0;
    
    /* init steps */
    steps[0] = NOT_FOUND;
    GetNext(pttn, steps);
    
    while (curr < len){
        if (t[curr] == pttn[mtched]) mtched++, curr++;
        else if (mtched == 0) curr++;
        else {
            mtched = steps[mtched]; // move substring
        }
        
        if (mtched == pttn_len){ return curr; }
    }
    
    free(steps);
    steps=NULL;
    return NOT_FOUND;
}

// example:
//  applicaiton, power string
