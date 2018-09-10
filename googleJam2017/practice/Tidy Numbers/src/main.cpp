//
//  main.cpp
//  googleJam2
//
//  Created by Wang Yi on 10/9/17.
//  Copyright © 2017 Wang Yi. All rights reserved.
//
#include <stdio.h>
#include <err.h>

#include <iostream>
#include <sstream>
#include <string>

#include <cmath>
using std::pow;

#include <string.h>
#include <stdarg.h>
using std::string;
#define N 19
#define MIN(a, b) ((a) > (b) ? (b) : (a))

#define __SHORT_FILE (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#define LOG(msg) \
    if ((msg)) \
    fprintf(stderr, "[%s]: alert at %s (%s:%d)\n", (msg), __FUNCTION__, __SHORT_FILE, __LINE__);

typedef long long ll;

ll
solution(ll inp);

int main(int argc, const char * argv[]) {
    int T;
    std::cin >> T;
    
    std::stringstream split;
    string line;
    
    ll temp, out;
    
    std::getline(std::cin, line);
    
    for (int i=0; i < T; i++) {
        std::getline(std::cin, line);
        split << line;
        split >> temp;
        split.clear();
        
        out = solution(temp);
        
        std::cout << "Case #" << i+1 << ":" << " " << out << std::endl;
    }
}

ll
solution(ll inp){
    int digits[N] = {0};
    int l = 0, head;
    bool flag = false;
    ll ret = 0;
    
    while (inp > 0) {
        digits[l++]  =inp % 10;
        inp = inp / 10;
    }
    
    head = l-1;
    while(head > 0 && !flag) {
        int temp = digits[head];
        if (digits[head] > digits[head-1]) {
            temp = temp-1;
            ret = ret*10 + temp;
            flag = true;
            head--;
        } else
        if (digits[head] == digits[head-1]){
            // look ahead
            int state = head - 1;
            bool control_ok = false, control_wrong=false;
            ll sum = temp;
            while (state > 0 && !(control_ok || control_wrong)) {
                if (digits[state] > digits[state-1]) {
                    control_wrong = true;
                } else
                if (digits[state] < digits[state-1]) {
                    sum = sum*10 + temp;
                    control_ok = true;
                } else {
                    sum = sum*10 + temp;
                }
                
                state--;
            }
            
            if (control_wrong) {
                temp = temp - 1;
                ret = ret*10 + temp;
                flag = true;
                head--;
            } else
            if (control_ok) {
                ll temp = pow(10, head-state);
                ret = ret * temp + sum;
                head = state;
            } else {
                ll temp = pow(10, head-state);
                ret = ret * temp + sum;
                head = state;
            }
            
        } else { // digits[head] < digits[head-1]
            ret = ret*10 + temp;
            head--;
        }
    }
    
    if (flag) {
        while (head >= 0) {
            ret = ret * 10 + 9;
            head--;
        }
    } else {
        if (head == 0) {
            ret = ret * 10 + digits[0];
        } else {
            LOG("Something wrong here!");
            exit(1);
        }
    }
    
    return ret;
    
}
