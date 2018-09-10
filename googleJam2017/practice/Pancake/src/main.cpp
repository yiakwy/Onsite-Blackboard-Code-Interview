//
//  main.cpp
//  googleJam1
//
//  Created by Wang Yi on 5/9/17.
//  Copyright © 2017 Wang Yi. All rights reserved.
//

#include <iostream>
#include <sstream>
using std::stringstream;
#include <string.h>
#include <string>
using std::string;

#include <vector>
using std::vector;
#include <queue>
using std::queue;
#include <unordered_map>
using std::unordered_map;
typedef unordered_map<int, bool> queryTable;

#include <stdlib.h>
#define Malloc(type, len) \
    (type*)malloc(sizeof(type)*len)

#define NOT_DEFINED -1
#define IMPOSSIBLE -1

int
idgen(const char* s, int l)
{
    int i, ret=0;
    for (i=0; i < l && i < 32; i++) {
        int bitv;
        if (s[i] == '+')
            bitv = 0;
        else if (s[i] == '-') {
            bitv = 1;
        }
        ret = (ret << 2) + bitv; // this id scheme does not work for big id
    }
    return ret;
}

typedef struct _nd {
public:
    const char* state;
    static size_t l;
    static int K;
    int id = NOT_DEFINED; // small id
    struct _nd* parent = nullptr;
    
    _nd(const char* s, size_t l) {
        this->state = s;
        this->l = l;
        this->id = idgen(s, (int)l); // 2^32 at most
    }
} Node;

size_t Node::l;
int Node::K;

char*
reverse_from_id(int id, int l){
    char* s = Malloc(char, l+1);
    int i=0;
    while (id != 0) {
        s[i++] = id % 2;
        id |= 2;
    }
    s[l] = '\0';
    return s;
}

typedef Node* (*transfunc)(Node* state, int pos);
#define PRINT_PATH(curr) \
    Node* temp = curr; \
    while (curr != nullptr) { \
        std::cout << curr->state << " "; \
        curr = curr->parent; \
    }; \
    std::cout << std::endl; \
    curr = temp;

void
toggle(char* s, int p)
{
    if (s[p] == '+') {  s[p] = '-'; } else
    if (s[p] == '-') {  s[p] = '+'; }
}

Node* trans(Node* state, int pos)
{
    char* s = Malloc(char, state->l+1);
    strcpy(s, state->state);
    s[state->l] = '\0';
    int i;
    for (i=pos; i < state->K + pos; i++) {
        toggle(s, i);
    }
    return new Node(s, state->l);
}

vector<Node*>
find_neighor(Node* curr, Node* target, transfunc trans, queryTable visited)
{
    vector<Node*> ret;
    int i;
    for (i=0; i < curr->l-Node::K+1; i++) {
        if (curr->state[i] == '+') {
            if (i != curr->l-Node::K) continue;
            else return ret; // the last part must not be equal
        }
        Node* nd = trans(curr, i);
//        if (nd->id <  && visited.find(nd->id) != visited.end()) { // does not work for big id
//            continue;
//        }
        nd->parent = curr;
        ret.push_back(nd); break;
    }
    return ret;
}

Node*
wfs(Node* state, Node* target, transfunc trans, int K, int* step){
    queue<Node*> q;
    q.push(state);
    int depth = 0;
    int curr_no=1, next_no=0;
    queryTable visited;
    
    while (!q.empty()) {
        Node* curr = q.front(); q.pop();
        visited[curr->id] = true;
        curr_no--;
        
        if (curr->id == target->id) {
            int sum = 0;
            for (int i=0; i < curr->l; i++) {
                if (curr->state[i] == '+') sum += 0;
                else sum += 1;
            }

            if (sum == 0) {
            // PRINT_PATH(curr)
            *step = depth;
            return curr;
            }
        }
        
        auto children = find_neighor(curr, target, trans, visited);
        next_no += (int)children.size();
        if (curr_no == 0) {
            depth++;
            curr_no = next_no;
            next_no = 0;
        }
        
        for (auto child : children) {
            q.push(child);
        }
    }
    
    return nullptr;
}

int
math_rule(const char* arr, int l, int K){
    int i, x=0, y=0;
    for (i=0; i < l; i++) {
        if (arr[i] == '+') {
            x += 1;
        } else
        if (arr[i] == '-') {
            y += 1;
        }
    }
    
    // K*n = x*2*k1 + y*(2*k2 - 1)
    if (x == y && K % 2 == 0 && x % K != 0) {
        return IMPOSSIBLE;
    }
    
    if (y%2 != 0 && K % 2 == 0) {
        return IMPOSSIBLE;
    }
    
    return 0;
}

int
solution (const char* arr, int l, int K){
    int ret = IMPOSSIBLE;
    Node* start = new Node(arr, l);
    char* end = Malloc(char, l+1);
    for (int i=0; i < l; i++) {
        end[i] = '+';
    }
        end[l] = '\0';
    Node* target = new Node(end, l);
    Node::K = K;
    int step;
    
    if (l < K) {
        
        return IMPOSSIBLE;
    }
    
//    if (math_rule(arr, l, K) == IMPOSSIBLE) {
//        return IMPOSSIBLE;
//    }
    
    
    Node* query = wfs(start, target, trans, K, &step);
    if (query != nullptr) {
        ret = step;
    }
    return ret;
}

int main(int argc, const char * argv[]) {
    int N, K, out;
    std::cin >> N;
    
    std::string line;
    std::stringstream split;
    std::string temp;
    
    std::getline(std::cin, line);
    
    for (int i=0; i < N; i++) {
        std::getline(std::cin, line);
        split << line;
        split >> temp;
        split >> K;
        split.clear();
        
        Node::K = K;
        Node::l = temp.length();
        out = solution(temp.c_str(), (int)temp.length(), K);
        
        if (out == -1)
            std::cout << "Case #" << i+1 << ":" << " " << "IMPOSSIBLE" << std::endl;
        else {
            std::cout << "Case #" << i+1 << ":" << " " << out << std::endl;
        }
        
    }
    
    return 0;
}
