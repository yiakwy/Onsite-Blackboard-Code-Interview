//
//  programming.cpp
//  KMP_Prob
//
//  Created by Wang Yi on 19/3/17.
//  Copyright © 2017 Wang Yiyiak.co. All rights reserved.
//

#include "programming.hpp"

// Here I will implement dynamical programming for the problem
// P(i, j, L) = Q(j)∙P(next_steps(j), next_step(j), L−i+next_step(j)) + (1−Q(j))∙𝑃(𝑖+1,j+1,𝐿) (j!= 0)
// to solve it, we want to make sure it is a DAG and we also need to identify the "boundary conditions" like we solve other
// mathematical problems.
// boundary conditions:
//   P(*, M_L, l) = 1
//   P(curr, M_L - 1, l) = Q(M_L - 1)∙P(next_steps(M_L - 1), next_steps(M_L - 1), L-i+next_steps(M_L-1)) +
//                         (1 - Q(M_L - 1)) (l > M_L)
//   P(curr, 0, l) = Q(0)∙P(0, 0, l - 1) + (1-Q(0))∙P(curr+1, 1, l)
//   P(j, j, M_L) = (1 - Q(0))^(M_L - j)

move_corr* kmp_steps(size_t curr, size_t mtched, size_t pttn_len, int steps[])
{
    size_t pttn_mv = steps[mtched]; // the actual distance should be (mtched - steps[mtched])
    size_t txt_head_mv = curr - steps[mtched];
    move_corr* pos = new move_corr(pttn_mv, txt_head_mv);
    return pos;
};


double
kmp_pb::Q(size_t mtched)
{
    double _p = 1.0 / m_vals_range;
    return (1 - _p);
}

// Question1: Try to implement the following codes body as we talk in the class, the instructor should already done every dirty thing.
// Question2: Give the snnipet of the codes, try to pove the process is convergent.
double
kmp_pb::P(size_t curr_pos, size_t mtched, size_t l)
{
    if (l <= m_pttn_len)
        return pow((1.0) / m_vals_range, l - mtched);
    if (mtched == 0)
        return Q(0) * P(0, 0, l - 1) + (1-Q(0)) * P(curr_pos + 1, 1, l);
    else if (mtched == m_pttn_len){
        return 1;
    } else {
        return Q(mtched) * P(m_steps[mtched], m_steps[mtched], l - curr_pos + m_steps[mtched]) + \
               (1 - Q(mtched)) * P(curr_pos + 1, mtched + 1, l);
    }
    
}

Fn_Signature decl_Fn_Signature(size_t curr_pos, size_t mtched, size_t L, double ret)
{
    Fn_Signature fs(curr_pos, mtched, L, ret);
    return fs;
}

ll decl_generate_hashcode(size_t curr_pos, size_t mtched, size_t L)
{
    ll code = curr_pos * L + mtched; // curr_pos <= L
    return code;
}

size_t decl_bruteforce_search(size_t curr_pos, size_t mtched, size_t L, vector<Fn_Signature> Cn)
{
    int step = 0;
    for (auto el : Cn)
    {
        if (el.curr_pos == curr_pos &&
            el.mtched == mtched &&
            el.L == L)
            return step;
        step++;
    }
    return NOT_FOUND;
}

