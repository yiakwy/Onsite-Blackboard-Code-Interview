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

int main(int argc, char** argv)
{
    Solution sol;
    int ret = sol.uniquePaths(3, 2);
    std::cout << ret << std::endl;
}
