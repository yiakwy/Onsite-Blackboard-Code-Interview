//
//  programming.cpp
//  KMP_Prob
//
//  Created by Wang Yi on 19/3/17.
//  Copyright © 2017 Wang Yiyiak.co. All rights reserved.
//

#include "programming.hpp"

// March 19, 2017
// This was original wrong solution I proposed, Please go on to see the "right" one `real_P`.
// Here I will implement dynamical programming for the problem
// P(i, j, L) = Q(j)∙P(next_steps(j), next_step(j), L−i+next_step(j)) + (1−Q(j))∙𝑃(𝑖+1,j+1,𝐿) (j!= 0)
// to solve it, we want to make sure it is a DAG and we also need to identify the "boundary conditions" like we solve other
// mathematical problems.
// boundary conditions:
//   P(*, M_L, l) = 1, we already found, 100 percent
//   P(curr, M_L - 1, l) = Q(M_L - 1)∙P(next_steps(M_L - 1), next_steps(M_L - 1), L-i+next_steps(M_L-1)) +
//                         (1 - Q(M_L - 1)) (l > M_L)
//   P(curr, 0, l) = Q(0)∙P(0, 0, l - 1) + (1-Q(0))∙P(curr+1, 1, l)
//   P(j, j, M_L) = (1 - Q(0))^(M_L - j)

// April 3th, 2017
// I record what I found (my girl friend go for traveling, and I was coding in home, Peking):
// My DP result is
/*
I0403 21:36:33.696638 1741760 main.cpp:35] Given a text M of length 6, the probability of string <P> : ABB in <M> is: 0.402344
I0403 21:36:33.697320 1741760 main.cpp:41] Given a text M of length 6, the probability of string <P> : BBA in <M> is: 0.453125
 */
// My sampling engine result (plausible) is :
/*
 I0404 01:02:58.897646 1786816 main.cpp:37] random_alphabet distribution, uniform checking ...
 I0404 01:02:58.981082 1786816 probtests.cpp:156] running test cases <10000> : avg:5000 , utd:21 , ratio of utd over avg0.0042
 probability histogram:
 
 **** alphadistribution toolkit -- histogram, copyright © 2017 Wang Yi (yiak.wy@gmail.com) ****
 
 <A>: ###############               0.5021
 <B>: ##############                0.4979
 
 I0404 01:03:03.826927 1786816 main.cpp:50] Given a text M of length 6, the probability of string <P> : ABB in <M> is: 0.48023
 I0404 01:03:08.599938 1786816 main.cpp:58] Given a text M of length 6, the probability of string <P> : BBA in <M> is: 0.48211
 
 */
/*
 It was clear that something wrong with my equations.
 Since I am considering probability of (M in Txt of length l), we have sampling space
  xxx ... xxxabcefgabc? xxx ... xxx
             abcefgabck ??

                                   cases({M: M in Txt of length `A1`}) * cases({M: M in Txt of length `A2`})
  i.e : P(curr, 9, L) = Q(9) * ---------------------------------------------------------------------------- + ...
                                space( P(0, 0, curr - n(9)) + 1 ) * space( P(n(9), n(9), L - curr + n(9)) )

 Boundary condition:
 */


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

// created on April 3, 2017, Lei Wang
// P(i, j, L) = Q(j)∙P(0,0,curr+1-mtched)∙P(next_steps(j), next_step(j), L−i+next_step(j)) + (1−Q(j))∙𝑃(𝑖+1,j+1,𝐿) (j!= 0)
double
kmp_pb::real_P(size_t curr_pos, size_t mtched, size_t l)
{
    if (curr_pos == l-1)
    {
        if (mtched == m_pttn_len - 1)
            return Q(mtched) * P(m_steps[mtched], m_steps[mtched], curr_pos - (mtched - m_steps[mtched])) + (1-Q(mtched));
        if (mtched < m_pttn_len - 1)
            return Q(mtched) * P(m_steps[mtched], m_steps[mtched], curr_pos - (mtched - m_steps[mtched]));
    }
    
    if (l < m_pttn_len)
        return 0;
    if (l == m_pttn_len)
        return pow((1.0) / m_vals_range, l - mtched);
    if (mtched == 0)
    {
        if (curr_pos - m_steps[mtched] >= m_pttn_len)
        {
            return Q(0) * P(0, 0, curr_pos) * P(0, 0, l - 1) + (1-Q(0)) * P(curr_pos + 1, 1, l);
        } else return Q(0) * P(0, 0, l - 1) + (1-Q(0)) * P(curr_pos + 1, 1, l);
    }
    
    else if (mtched == m_pttn_len){
        return 1;
    } else { // 0 < mtched < m_pttn_len
        
        if (curr_pos - m_steps[mtched] >= m_pttn_len )
        {
            return Q(mtched) * P(m_steps[mtched], m_steps[mtched], curr_pos - (mtched - m_steps[mtched])) * P(m_steps[mtched], m_steps[mtched], l - curr_pos + m_steps[mtched]) + (1 - Q(mtched)) * P(curr_pos + 1, mtched + 1, l);
        } else return Q(mtched) * P(m_steps[mtched], m_steps[mtched], l - curr_pos + m_steps[mtched]) + (1 - Q(mtched)) * P(curr_pos + 1, mtched + 1, l);
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

