//
//  floyd_path_tp.cpp
//  ApolloTeam
//
//  Created by Wang Yi on 20/5/19.
//
//
#include <vector>
using std::vector;
#include <algorithm>

void floid_paths(vector<vector<int>>& W, int V)
{
    for (int k=0; k < V; k++)
        for (int i=0; i <= V; i++)
            for(int j=0; j <= V; j++)
                W[i][j] = std::min(W[i][j], W[i][k] + W[k][j]);
}
