//
//  programming.cpp
//  KMP_Prob
//
//  Created by Wang Yi on 19/3/17.
//  Copyright © 2017 Wang Yiyiak.co. All rights reserved.
//

#include "programming.hpp"
// Here I will implement dynamical programming for the problem
// P(i, j, L) = Q(j)∙P(0, 0, L−i−next_step(j)+1) +(1−Q(j))∙𝑃(𝑖+1,j+1,𝐿)

