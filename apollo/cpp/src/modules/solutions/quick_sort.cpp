//
//  quick_sort.cpp
//  ApolloTeam
//
//  Created by Wang Yi on 8/5/19.
//
//

#include <iostream>
#include "quick_sort.hpp"

typedef int (*_cmpfunc_t)(int, int);

void print(int* array, size_t size)
{
    for (int i=0; i < size; i++) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}

void swap(int* left, int* right)
{
    int temp = *left;
    *left = *right;
    *right = temp;
}

int partition(int* array, size_t low, size_t high, _cmpfunc_t cmpfunc)
{
    int x = array[high];
    int i = low - 1;
    for (int j=low; j <= high-1; j++)
    {
        if (cmpfunc(x, array[j]) > 0) {
            swap(array+i+1, array+j);
            i++;
        }
    }
    swap(array+i+1, array+high);
    return i+1;
}

#define N 8

void quick_sort(int* array, size_t low, size_t high, _cmpfunc_t cmpfunc) {
    if (low < high) {
        int pivot = partition(array, low, high, cmpfunc);
        if (pivot == 0) {
            quick_sort(array, pivot+1, high, cmpfunc);
        } else {
            quick_sort(array, low, pivot-1, cmpfunc);
            quick_sort(array, pivot+1, high, cmpfunc);
        }
    }
}

int cmp(int left, int right) {
    if (left > right) {
        return 1;
    } else if (left == right) {
        return 0;
    } else {
        return -1;
    }
}

/*
  According to Master Theorem, the run time complexity is upper bounded by O(n^2) and can achieve O(N^2) when the partition is unbalanced with non-constant ratio. Hence the worst complexity is O(n^2). It is because the pivot might be a const. Considering T(n) = T(n-1) + O(n), we will derived that qicksort runs at Omega(n^2). By utiilizing RandomParition technique, we could prove that the statistical expected run time bounded by O(nlogn).  - by Lei, reference textbook <Introduction to Algorithms>
 */
int main(int argc, char** argv)
{
    int array[N] = {2, 8, 7, 1, 3, 5, 6, 4};
    quick_sort(array, 0, N-1, cmp);
    print(array, N);
}
