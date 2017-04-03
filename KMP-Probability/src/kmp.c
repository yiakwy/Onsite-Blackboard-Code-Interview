//
//  kmp.c
//  Cyclic_Moving
//
//  Created by Wang Yi on 15/5/16.
//  Copyright (c) 2016 Wang Yi. All rights reserved.
//
#include "kmp.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>

#define Malloc(type, len) \
    (type*)malloc(sizeof(type)*len)
#define NOT_FOUND -1

int isDebug = 1;
// for debug purpose
#define __SHORT_FILE__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#define _FORMATTED_TIME getFormattedTime()
#define _PRE _FORMATTED_TIME

#define ALGO_KMP_DEMO(no, pttn, pttn_len, fmt, ...) \
printf(" %*s%s\n", (int)(no), "", pttn); \
printf(" %*s" fmt, (int)(no), "", ## __VA_ARGS__);

#define ALGO_KMP_cursor(no, forward, pttn_len, fmt, ...) \
if(no == 0) { \
printf("" fmt);} else { \
printf(" %*s" fmt, (int)(no+(forward-1)), "", ## __VA_ARGS__);}

// helper func
// http://stackoverflow.com/questions/7411301/how-to-introduce-date-and-time-in-log-file
char* getFormattedTime(void)
{
    time_t rawtime;
    struct tm* timeinfo;
    
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    
    // Must be static, otherwise won't work
    static char _repr_val[20];
    strftime(_repr_val, sizeof(_repr_val), "%Y-%m-%d %H:%M:%S", timeinfo);
    
    return _repr_val;
}

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
void GetNext2(const char* pttn, int steps[])
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

size_t pattern_find(const char* t, size_t len, const char* pttn, size_t pttn_len)
{
    int* steps = Malloc(int, pttn_len);
    size_t curr = 0;
    int mtched = 0;

    printf("string to be matched:\n %s\n", t);
    printf("begin:\n %s\n %*s\n", pttn, 1, "^");
    
    /* init steps */
    steps[0] = NOT_FOUND;
    GetNext2(pttn, steps);
    
    while (curr < len){
        if (isDebug == 1)
        {
            ALGO_KMP_cursor(curr-mtched, mtched, pttn_len, "-")
            printf("\n");
        }
        
        if (t[curr] == pttn[mtched]) mtched++, curr++;
        else if (mtched == 0) curr++;
        else {
            mtched = steps[mtched]; // move substring
        }
        
        if (isDebug == 1)
        {
            ALGO_KMP_DEMO(curr-mtched, pttn, pttn_len, "^")
            printf("\n");
        }
        
        if (mtched == pttn_len)
        {
            if (isDebug == 1)
            {
                ALGO_KMP_cursor(curr-mtched, mtched, pttn_len, "-")
                printf("\n");
            }
            return curr;
        }
    }
    
    if (isDebug == 1)
    {
        ALGO_KMP_cursor(curr-mtched, mtched, pttn_len, "-")
        printf("\n");
    }
    
    free(steps);
    steps=NULL;
    return NOT_FOUND;
}

// example:
//  applicaiton, power string
