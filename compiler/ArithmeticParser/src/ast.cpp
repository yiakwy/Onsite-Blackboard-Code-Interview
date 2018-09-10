//
//  ast.cpp
//  ast
//
//  Created by Wang Yi on 30/4/17.
//  Copyright © 2017 Wang Lei. All rights reserved.
//

#include "ast.hpp"
#define ast_read(tokens, buf) \
    static int _i=0, _len = size; \
    if (_i < _len) *buf = tokens[_i++]; else break;

#define AST_FAILED(msg, o, out) \
    { o << msg << std::endl; \
    return out; }

TreeNode*
ast::ast_builder(vector<Token> tokens)
{
    stack<TreeNode*> s;
    TreeNode* root;
    int i, j, k, children_num, size=tokens.size();
    
    FOR(i, size)
    if (tokens[i].type == Operand) s.push(new TreeNode(tokens[i]));
    else if (tokens[i].type == Operator_Type)
    {
        
        Operator* op = get_operator(tokens[i].id);
        children_num = op->args_len;
        
        TreeNode* curr = new TreeNode(tokens[i]);
        
        if (children_num != -1) {
            FOR(j, children_num)
                TreeNode* child = s.top(); s.pop();
                curr->add(child);
                child->set_pos(j);
                child->m_parent = curr;
            END
            // std::reverse(curr->children.begin(), curr->children.end());
        } else {

        }
        
        s.push(curr);
    }
    END
    
//    std::cout << s.size() << std::endl;
//    if (s.size() > 1)
//        AST_FAILED("Wrong Token Defs!", cout, root)
    
    root = s.top();s.pop();
    TreeNodePrinter tnp(root);
    std::cout << "--- abstract syntax tree ---" << std::endl;
    std::cout << tnp._str() << std::endl;
    this->root = root;
    return root;
}

queue<Token>
ast::postfix_Expr(Token tokens[], size_t size)
{
    queue<Token> out;
    stack<Token> operators;
    Token buf;
    
    while(true) {
        ast_read(tokens, &buf);
        
        if (buf.type == Operand) out.push(buf);
        if (buf.type == Operator_Type) {
            
            switch (buf.id)
            {
                case OPEN_PARA:
                    operators.push(buf);
                    break;
                case Number:
                    out.push(buf);
                    break;
                case Symbol:
                    operators.push(buf);
                    break;
                case Separator:
                    while(!operators.empty() &&
                          operators.top().id != OPEN_PARA)
                    {
                        out.push(operators.top());operators.pop();
                    }
                    
                    if (operators.empty())
                        AST_FAILED("Open parathensis mismathced or separator not correct!", cout, out);
                    break;
                case CLOSE_PARA:
                    while(!operators.empty() &&
                           operators.top().id != OPEN_PARA)
                    {
                        out.push(operators.top());operators.pop();
                    }
                    
                    if (operators.empty())
                        AST_FAILED("No matched open parathensis!", cout, out);
                    
                    operators.pop();
                    
                    break;
                default:
                    if (operators.empty()) operators.push(buf);
                    else {
                        Operator *buf_op = get_operator(buf.id);
                        
                        if (buf_op == nullptr) AST_FAILED("Invalided operator", cout, out);
                        
                        while(!operators.empty())
                        {
                            Token pre = operators.top();
                            Operator *pre_op = get_operator(pre.id);
                            
                            if (pre_op == nullptr)
                                AST_FAILED("Invalided operator", cout, out);
                            
                            if ((buf_op->assoc == LEFT_ASSC && buf_op->priority <= pre_op->priority) ||
                                buf_op->priority < pre_op->priority)
                            {
                                out.push(pre); operators.pop();
                            } else break;
                        }
                        
                        operators.push(buf);
                    
                    }
                
            } // end of switch

        } // end of if
        
    }
    
    while(!operators.empty())
    {
        if (operators.top().id == OPEN_PARA)
            AST_FAILED("There is a mismatched open parenthensis found!", cout, out);
        out.push(operators.top());operators.pop();
    }
    
    // You might also want to use boost::algorithm::join(vec, delim) here
    return out;
}

std::ostream& operator<<(std::ostream& o, const TreeNode& t)
{
    return t.dump(o);
}

vector<TreeNode*>
TreeNode::wfs()
{
    vector<TreeNode*> ret;
    queue<TreeNode*> q;
    q.push(this);
    vector<TreeNode*> children;
    int depth = 1;
    TreeNode* curr = nullptr;
    int curr_no = 1, next_no = 0;
    
    while (!q.empty())
    {
        curr = q.front(); q.pop();
        
        // visit
        ret.push_back(curr);
        curr_no --;
        
        auto children = curr->children;
        next_no += (int)children.size();
        
        if (curr_no == 0){
            depth++;
            curr_no = next_no;
            next_no = 0;
        }
        
        for(auto child : children)
        {
            q.push(child);
        }
        
    }
    
    return ret;
    
}

