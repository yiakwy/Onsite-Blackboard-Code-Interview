//
//  unique_path.cpp
//  ApolloTeam
//
//  Created by Wang Yi on 20/5/19.
//
//
#include <iostream>
#include <vector>
using std::vector;

class Solution {
public:
    int uniquePaths(int m, int n) {
        std::vector<std::vector<int>> maze(m, vector<int>(n, 1));
        for (int i=1; i < m;i++) {
            for (int j=1; j < n;j++) {
                maze[i][j] = maze[i-1][j] + maze[i][j-1];
            }
        }
        return maze[m-1][n-1];
    }
};

class Solution2 {
public:
    int uniquePaths(int m, int n) {

        int small, max;
        if (m > n) {
            small = n;
            max = m;
        } else {
            small = m;
            max = n;
        }
        
        // base = (small-1)!
        // denominator = (max+small-2)! started from max
        long ret = 1.0;
        for (int i=max; i <= max+small-2; i++) {
            // ret *= (i*1.0f / (i-max+1)); // wrong
            ret *= i;
            ret /= (i-max+1);
        }
        return (int)ret;
    }
};

int main(int argc, char** argv)
{
    Solution2 sol;
    int ret = sol.uniquePaths(23, 12);
    std::cout << ret << std::endl;
}
