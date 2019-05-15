//
//  the_maze.cpp
//  ApolloTeam
//
//  Created by Wang Yi on 14/5/19.
//
//

#include <iostream>
#include <queue>
#include <vector>
#include <cmath>
using std::vector;
#include <map>
using std::map;
#include <stack>
using std::stack;

struct Node {
    int r;
    int c;
    int val;
    float g_score;
    float h_score;
    float f_score;
    Node* parent;
    
    Node() {
        g_score = INFINITY;
        parent = nullptr;
    }
    
    void
    Init(int r, int c, int val) {
        this->r = r;
        this->c = c;
        this->val = val;
    }
};

using Map = map<Node*, int>;

#define INSERTED 1
#define VISITED 2

class Cmp {
public:
    bool operator()(Node* left, Node* right) {
        if (left->f_score > right->f_score ) {
            return true;
        } else {
            return false;
        }
    }
};

float dist(Node* a, Node* b) {
    return sqrt(pow(a->r - b->r, 2) + pow(a->c - b->c, 2));
}

float heuristic_dist(Node* a, Node* b)
{
    return dist(a, b);
}

class Solution {
public:
    /**
     * @param maze: the maze
     * @param start: the start
     * @param destination: the destination
     * @return: whether the ball could stop at the destination
     */
    bool hasPath(vector<vector<int>> &maze, vector<int> &start, vector<int> &destination) {
        // write your code here
        bool ret = false;
        std::priority_queue<Node*, vector<Node*>, Cmp> q;
        
        vector<vector<Node>> map;
        Map inverted_query;
        Node *cur;
        Node *start1, *end;
        
        for (int i=0; i < maze.size(); i++) {
            vector<Node> row;
            map.push_back(row);
            for (int j=0; j < maze[i].size(); j++) {
                Node nd;
                map[i].push_back(nd);
                map[i][j].Init(i,j,maze[i][j]);
            }
        }
        
        start1 = &map[start[0]][start[1]];
        end = &map[destination[0]][destination[1]];
        
        start1->g_score = 0;
        start1->f_score = heuristic_dist(start1, end);
        
        q.push(start1);
        
        while(!q.empty())
        {
            cur = q.top();q.pop();
            
            if (cur == end) {
                ret = true;
                std::stack<Node*> path;
                while (cur->parent != nullptr) {
                    path.push(cur);
                    cur = cur->parent;
                }
                path.push(cur);
                while (!path.empty())
                {
                    cur = path.top(); path.pop();
                    std::cout << "<" << cur->r << "," << cur->c << ">" << " ";
                }
                break;
            }
            
            inverted_query[cur] = VISITED;
            
            if (cur->parent != nullptr) {
                Node* next = nullptr;
                Node* last = cur;
                int dr = cur->r - cur->parent->r, dc = cur->c - cur->parent->c;
                
                while (next == nullptr || next->val != 1) {

                    if (next != nullptr) {
                        cur = next;
                    }
                    int r, c;
                    r = cur->r + dr;
                    c = cur->c + dc;
                    if (r < 0 || r >= map.size() || c < 0 || c >= map[0].size()) {
                        break;
                    }
                    next = &map[r][c];
                }
                if (cur != last) {
                    float t = last->g_score + dist(last, cur);
                    if (t < cur->g_score) {
                        cur->g_score = t;
                        cur->h_score = heuristic_dist(cur, end);
                        cur->f_score = cur->g_score + cur->f_score;
                        cur->parent = last;
                    }
                }
            }
            
            auto neighbors = getChildren(inverted_query, cur, map);
            
            for (Node* neighbor : neighbors) {
                if (inverted_query.find(neighbor) != inverted_query.end() && inverted_query[neighbor] == VISITED) {
                    continue;
                }
                
                if (neighbor->val == 1) {
                    continue;
                }
                
                if (inverted_query.find(neighbor) == inverted_query.end() || (inverted_query[neighbor] != INSERTED && inverted_query[neighbor] != VISITED)) {
                    inverted_query[neighbor] = INSERTED;
                    q.push(neighbor);
                }
                
                float t = cur->g_score + dist(cur, neighbor);
                
                if (t > neighbor->g_score) {
                    continue;
                }
                
                neighbor->g_score = t;
                neighbor->h_score = heuristic_dist(neighbor, end);
                neighbor->f_score = neighbor->g_score + neighbor->h_score;
                neighbor->parent = cur;
                
            }
            
        }
        
        return ret;
        
    }
    
    vector<Node*> getChildren(Map& visited, Node* cur, vector<vector<Node>>&map) {
        int r = cur->r, c = cur->c;
        vector<vector<int>> indexes = {
            {r-1, c},
            {r, c-1},
            {r+1, c},
            {r, c+1}
        };
        
        vector<Node*> ret;
        
        for (auto index : indexes) {
            if (index[0] < 0 || index[0] >= map.size() || index[1] < 0 || index[1] >= map[0].size()) {
                continue;
            }
            
            ret.push_back(&map[index[0]][index[1]]);
            
        }
        
        return ret;
        
    }
    
};


int main(int argc, char** argv)
{
    vector<vector<int>> maze = {
        {0,0,1,0,0},
        {0,0,0,0,0},
        {0,0,0,1,0},
        {1,1,0,1,1},
        {0,0,0,0,0}
    };
    
    vector<int> start = {0,4};
    vector<int> end = {3,2};
    
    Solution sol;
    
    int ret = sol.hasPath(maze, start, end);
    
    return 0;
    
}
