Given a series of a stock price, make one transaction: buy it at some time, and sell it after the purchase. Find the maximum revenue you could get per unit of stock.

The O\(n\) algorithm created and implemented by Lei on 13th Jun 2017. Here is analysis for reference:

## The problem formulation:
max P\(tj\) - P\(ti\) \(0 <= ti < tj <= N\)

Difference is not good for accumulation analysis, hence we write difference in accumulation manner, i.e.:

P\(tj\) - P\(ti\) = sum {P\(t\(k\)\) - P\(t\(k-1\)\) + P\(t\(i-1\)\)

Hence we transform the original array into difference array. For example, test case 

> 10, 8, 5, 9, 8, 6, 7, 12, 9 ==\> -2, -3, 4, -1, -2, 1, 5, -3

## Algortihm Formuation:
    0. move start point to first positive position; if the array has only one element return that or Max(0, that) depending on your definition
    1. find a pivot so that the contigunous sequence of sum can not be grow any more from the searching start point using **longest growth search**. Now, we got the largest contiguous sum : first_chunk
    2. set start as pivot go to 1 recursively. Now we got maximum **tail_sum**
    3. return MAX(first_chunk, tail_sum)

#### lib:
find\_fist\_ne

find\_fist\_po

array2diff

###### longest\_growth\_sum
0. deal with exotic simple cases
1. find the first position j we got a element whose value is negtive from start
2. find the first position k we got a element whose value is positive or 0 from j
3. caculate sum[start .. j] as s1
4. caculate recursively **tail_sum** by setting start as k
5. s1 + tail_sum > 0 goto 6 else goto 7
    6. we can connect them together by stoping at where tail_sum stops return s1 + sum[j..k] + tail_sum
    7. we cannot connect them together return MAX(s1, tail_sum) by setting stoping positions at k

## Asymptotic Time Complexity
Suppose for a array of length n, we have stops sequence k0=0, k1, ..., km=n
, where m must be <= n/2

we have:

O\(b\(n-k0\)\) = O\(k1\) - O\(k0\) + O\(b\(n-k1\)\)

O\(b\(n-k1\)\) = O\(k2\) - O\(k1\) + O\(b\(n-k2\)\)

... ...

O\(b\(n-km\)\) = O\(km\) - O\(k\(m-1\)\)

Finally we have:

O(bn) = O\(n\)
