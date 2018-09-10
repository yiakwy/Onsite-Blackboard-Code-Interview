//
//  ast.hpp
//  ast
//
//  Created by Wang Yi on 30/4/17.
//  Copyright © 2017 Wang Lei. All rights reserved.
//

#ifndef ast_hpp
#define ast_hpp

#include "token.hpp"
#include <iostream>
#include <algorithm>

using std::cin;
using std::cout;

#include <vector>
using std::vector;

#include <stack>
using std::stack;

#include <queue>
using std::queue;

class node {
public:
    node(Token tok):m_tok(tok), m_parent(nullptr){}
    
    Token m_tok;
    vector<node*> children;
    int m_pos = 0;
    node* m_parent;
    
    void add(node* child){children.push_back(child);};
    void set_pos(int pos){this->m_pos = pos;};
    
    vector<node*> wfs();
    // please refer to this question: http://stackoverflow.com/questions/1549930/c-equivalent-of-java-tostring for more details
    string _str() const {return string(" Tok: <") + this->m_tok.content + string("> ");}
    virtual std::ostream& dump(std::ostream& o) const {
        return o << _str();
    }
    
};

typedef node TreeNode;

class ast {
public:
    TreeNode* ast_builder(vector<Token> tokens);
    queue<Token> postfix_Expr(Token tokens[], size_t size);
    
private:
    vector<Token> postfix_tokens;
    TreeNode* root = nullptr;
};

std::ostream& operator<<(std::ostream& o, const TreeNode& t);

#define TAIL "└──"
#define NORMAL_NODE "├──"
#define INDENT_PREFIX          "|   "
#define INDENT_PREFIX_FOR_LAST "    "
#define ROOT_PREFIX            "───"
#define INDENT_STEP 3

template <class Tree> class _tree_node_printer {
public:
    _tree_node_printer(Tree* t=nullptr): m_tree(t){};
    _tree_node_printer(const _tree_node_printer& nd)
    {
        if (this != &nd)
        {
            m_tree = nd.m_tree;
            prefix = nd.prefix;
            isRoot = nd.isRoot;
            isTail = nd.isTail;
        }
    }
    
    _tree_node_printer& operator = (const _tree_node_printer& nd)
    {
        if (this != &nd)
        {
            m_tree = nd.m_tree;
            prefix = nd.prefix;
            isRoot = nd.isRoot;
            isTail = nd.isTail;
        }
        return *this;
    }
    
    virtual ~_tree_node_printer()
    {
        for (auto child : children){
            delete child;
        }
    }
    
    string _str();
    vector<_tree_node_printer*> build_children()
    {
        if (m_tree->children.size() != 0 && children.size() == 0)
        {
            int i=0;
            for (i=0; i < m_tree->children.size() - 1; i++)
            {
                Tree* child = m_tree->children[i];
                _tree_node_printer* nd = new _tree_node_printer(child);
                nd->prefix = string(NORMAL_NODE);
                children.push_back(nd);
            }
            
            if (m_tree->children.size() - 1 >= 0)
            {
                Tree* child = m_tree->children[m_tree->children.size() - 1];
                _tree_node_printer* nd = new _tree_node_printer(child);
                nd->prefix = string(TAIL);
                nd->isTail = true;
                children.push_back(nd);
            }
            
        }
        
        return children;
    }
    
    virtual std::ostream& dump(std::ostream& o) {
        return o << _str();
    }
    
private:
    Tree* m_tree;
    
    // fmt info
    string prefix = "";
    string indent = "";
    bool isRoot = false;
    bool isTail = false;
    
    vector<_tree_node_printer*> children;
};

typedef _tree_node_printer<TreeNode> TreeNodePrinter;

template <class Tree>
string
_tree_node_printer<Tree>::_str() {
    vector<string> temp;
    string ret;
    stack<_tree_node_printer<Tree>*> s;
    
    this->prefix = string(ROOT_PREFIX);
    this->isRoot = true;
    this->isTail = true;
    
    s.push(this);
    vector<_tree_node_printer*> children;
    _tree_node_printer* curr=nullptr;
    
    
    while(!s.empty())
    {
        curr = s.top(); s.pop();
        string indent = curr->indent;
        
        // visit func
        temp.push_back(indent + curr->prefix + curr->m_tree->_str() + string("\n"));
        
        auto children = curr->build_children();
        std::reverse(children.begin(), children.end());
        for(auto child : children)
        {
            string curr_indent = curr->isTail == true ? string(INDENT_PREFIX_FOR_LAST) : string(INDENT_PREFIX);
            child->indent = indent + curr_indent;
            s.push(child);
        }
        std::reverse(curr->children.begin(), curr->children.end());
    }
    
    // we can use boost::algorithm::join(vec, delim) here
    for (string el : temp)
    {
        ret += el;
    }
    return ret;
}


#endif /* ast_hpp */
