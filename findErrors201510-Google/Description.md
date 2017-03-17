Given a snippet of codes, try to find the error. The codes sometimes work but sometimes don't. Try to analyze the reason why they do?


```c++
//
//  main.cpp
//  google_test
//
//  Created by Wang Yi on 17/3/17.
//  Copyright © 2017 Wang Yiyiak.co. All rights reserved.
//

#include <iostream>
#include <time.h>
#include <cmath>

typedef long long ll;

void global_init()
{
    //srand(time(nullptr));
    unsigned int pseudo_seed = time(nullptr);
    unsigned int seed = (unsigned int)((pseudo_seed * pseudo_seed));
    srand(seed);
}

double recursive_method()
{
    switch(rand() % 10)
    {
        case 0:
        case 1:
            return 1.0;
            break;
        case 2:
            recursive_method() + recursive_method();
            break;
        case 3:
        case 4:
        case 5:
            std::cout << "good result!" << std::endl;
        default:
            recursive_method();
            
    }
    return 100.0;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    global_init();
    recursive_method();
    std::cout << "Hello, World!\n";
    return 0;
}
```
