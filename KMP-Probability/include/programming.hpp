//
//  programming.hpp
//  KMP_Prob
//
//  Created by Wang Yi on 19/3/17.
//  Copyright © 2017 Wang Yiyiak.co. All rights reserved.
//

#ifndef programming_hpp
#define programming_hpp

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>

#include "exceptions.hpp"

#include <boost/format.hpp>
#include <glog/logging.h>
// We will use glog for our tutorial
#ifdef HAVE_LIB_GFLAGS
#include <gflags/gflags.h>
using namespace gflags;
#endif

#include "kmp.h"

#define Malloc(type, len) \
    (type*) malloc(sizeof(type)*len)

#define FOR(i, s) \
for(i=0; i < s; i++) {
#define END ;}

#define COPY_MEM(d, src, len) \
    int d## _ptr; d = Malloc(int, len); \
    FOR(d## _ptr, len) d[d## _ptr] = src[d## _ptr]; \
    END

#define NOT_FOUND -1

#include <map>
using std::map;
using std::pair;
typedef long long ll;
#include <vector>
using std::vector;
#include <iterator>
using std::iterator_traits;

// this time we will introduce several methods used in C++ for memory table optimation
// since we can't use decorator pattern in every case, we will try every method comes into our minds.
typedef struct _fn_signature
{
    double ret;
    size_t curr_pos;
    size_t mtched;
    size_t L;
    
    _fn_signature(size_t curr_pos, size_t mtched, size_t L, double ret)
    {
        this->ret = ret;
        this->curr_pos = curr_pos;
        this->mtched = mtched;
        this->L = L;
    }

} Fn_Signature;

Fn_Signature decl_Fn_Signature(size_t curr_pos, size_t mtched, size_t L, double ret);
ll decl_generate_hashcode(size_t curr_pos, size_t mtched, size_t L);
size_t decl_bruteforce_search(size_t curr_pos, size_t mtched, size_t L, vector<Fn_Signature> Cn);

// please refer to std::lower_bound
template <class Increment_Tp, class Val>
Increment_Tp lower_bound(Increment_Tp first, Increment_Tp last, const Val& val)
{
    Increment_Tp it;
    typename std::iterator_traits<Increment_Tp>::difference_type c, step;
    c = distance(first, last);
    while (c > 0)
    {
        it = first; step = c/2; advance(it, step);
        if (it->ret < val)
        {
            first = ++it;
            c-=step+1;
        } else c = step;
    }
    return first;
}

template <class Increment_Tp, class Val>
size_t decl_binary_search(Increment_Tp first, Increment_Tp last, const Val& val)
{
    Increment_Tp ret = lower_bound(first, last, val);
    if (ret != last && val >= ret->ret)
        return ret - first;
    return NOT_FOUND;
}


typedef map<ll, vector<Fn_Signature>> Table;
#include <functional>

class move_corr
{
public:
    move_corr(size_t pttn_mv, size_t txt_head_mv):m_pttn_mv(pttn_mv),m_txt_head_mv(txt_head_mv){};
    size_t get_pttn_mv(){return this->m_pttn_mv;}
    size_t get_txt_mv(){return this->m_txt_head_mv;}
private:
    size_t m_pttn_mv;
    size_t m_txt_head_mv;
};

move_corr* kmp_steps(size_t curr, size_t mtched, size_t pttn_len, int steps[]);

// In the next chapter, we will talk about optimized dynamic programming...
class kmp_pb
{
public:
    typedef kmp_pb kmp_pbtype;
    
    explicit kmp_pb(size_t len, const char* pttn, size_t pttn_len, size_t vals_range): m_steps(nullptr)
    {
        m_steps = Malloc(int, pttn_len);
        if (m_steps == nullptr)
        {
            NotEnoughMemory e = NotEnoughMemory("weights");
            LOG(INFO) << e.what();//glog or something else
        }
        m_len = len;
        m_pttn_len = pttn_len;
        m_vals_range = vals_range;
        GetNext2(pttn, m_steps);
    }
    
    ~kmp_pb()
    {
        if (m_steps != nullptr)
        {
            free(m_steps);
            m_steps = nullptr;
        }
    }
    
    kmp_pb(const kmp_pbtype& ins)
    {
        if (this != &ins)
        {
            m_len = ins.m_len;
            m_pttn_len = ins.m_pttn_len;
            m_vals_range = ins.m_vals_range;
            
            if (ins.m_steps != nullptr)
            {
                COPY_MEM(m_steps, ins.m_steps, m_pttn_len)
            }
        }
    }
    
    kmp_pbtype& operator = (const kmp_pbtype& ins)
    {
        if (this != &ins)
        {
            m_len = ins.m_len;
            m_pttn_len = ins.m_pttn_len;
            m_vals_range = ins.m_vals_range;
            
            if (ins.m_steps != nullptr)
            {
                COPY_MEM(m_steps, ins.m_steps, m_pttn_len)
            }
        }
        return *this;
    }
    
    double Q(size_t mtched);
    double P(size_t curr_pos, size_t mtched, size_t l);
    
private:
    size_t m_len;
    size_t m_pttn_len;
    size_t m_vals_range;
    int* m_steps;
};

// optimizer.MemoryTable
template <class fn_type, class...Args>
class MemoryTable
{
public:
    MemoryTable(std::function<fn_type(Args ...)> fn, Table& cache) : m_fn(fn){this->cache = cache;}
    fn_type operator()(Args ... args)
    {
        ll id = this->generate_hashcode(args ...);
        Table::iterator it = cache.find(id);
        if (it != cache.end()){
            size_t where = this->bruteforce_search(args ..., it->second);
            if (where != NOT_FOUND)
                return it->second[where].ret;
        }
        Fn_Signature fs = decl_Fn_Signature(args ..., m_fn(args ...));
        cache[this->generate_hashcode(args ...)].push_back(fs);
        return fs.ret;
    }
    ll generate_hashcode(Args ... args){return decl_generate_hashcode(args ...);};
    size_t bruteforce_search(Args ... args, vector<Fn_Signature> l){return decl_bruteforce_search(args ..., l);};
private:
    std::function<fn_type(Args ...)> m_fn;
    Table& cache;
};

#endif /* programming_hpp */
