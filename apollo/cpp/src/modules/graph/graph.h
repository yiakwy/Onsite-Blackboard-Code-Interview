//
//  graph.h
//  graph
//
//  Created by Wang Yi on 16/4/19.
//
//

#ifndef graph_h
#define graph_h

#include <vector>
using std::vector;

#include <map>
using std::map;
using std::pair;
using std::make_pair;

#include <queue>
using std::queue;

#include <memory>

#include "utils/api.h"

#define INSERTED 1
#define DELETED -1

template<class Elem>
class Terminal;

// tag integer safely
static void* tag(int t) {
    return (void*)static_cast<intptr_t>(t);
}

static int detag(void*p) {
    return static_cast<int>(reinterpret_cast<intptr_t>(p));
}

template<class Elem>
class Terminal {
public:
    explicit Terminal(Elem& el) : el_(el) {
        
    }
    
    Terminal(const Terminal& t)
    : el_(t.el_)
    {
    }
    
    virtual Elem el() {
        return el_;
    }
    
    virtual Terminal<Elem>* set_el(Elem el) {
        el_ = el;
        return this;
    }
    
protected:
    Elem el_;
};

/*
  Adjacent Matrix
 */
template<class Elem> using Terminals = vector<Terminal<Elem>*>;
template<class Elem> using AdjMtx = map<void*, Terminals<Elem>>;

template<class Elem>
class TreeNode;

template<class Elem>
class DisjointedNode;

template<class Elem>
class Graph {
public:
    explicit Graph() {};
    
    using DisjointedSets = vector<DisjointedNode<Elem>>;
    
    virtual DisjointedSets sets();
    
    virtual vector<Terminal<Elem>*>
    route(Terminal<Elem>* start, Terminal<Elem>* end);

};

template<class Elem>
class GraphSparse : public Graph<Elem> {
public:
    explicit GraphSparse(AdjMtx<Elem>& neighbors): Graph<Elem>(), neighbors_(neighbors) {
        
    }
    
    
    // @todo : TODO
    typename Graph<Elem>::DisjointedSets sets_from_terminals() {
        
    }
    
    typename Graph<Elem>::DisjointedSets sets() override {
        return sets_from_terminals();
    }
    
    // @todo : shortest path for general sparse graph
    vector<Terminal<Elem>*>
    route(Terminal<Elem>* start, Terminal<Elem>* end) override {
        
    }

private:
    AdjMtx<Elem> neighbors_;

};


// grid plane for example.
template<class Elem>
class GraphMatrix: public Graph<Elem> {
public:
    
    using Matrix = Elem**;
    
    explicit GraphMatrix(Matrix mtx, int rows, int cols): Graph<Elem>() {
    
    }
    
    // @todo : TODO
    typename Graph<Elem>::DisjointedSets sets_from_mtx() {
    
    }
    
    typename Graph<Elem>::DisjointedSets sets() override {
        return sets_from_mtx();
    }
    
    // @todo : shortest path for matrix
    vector<Terminal<Elem>*>
    route(Terminal<Elem>* start, Terminal<Elem>* end) override {
        
    }
    
};

/*
 
 */
static int tnd_count=0;
static const double ALPHA = 0.5;

template<class Elem>
class TreeNode: public Terminal<Elem>,
                public std::enable_shared_from_this<TreeNode<Elem>>
{
public:
    explicit TreeNode(Elem& el): Terminal<Elem>(el), id_(tnd_count++) {
    
    }
    
    TreeNode(const TreeNode& nd)
    : Terminal<Elem>(nd),
      id_(nd.id_),
      parent(nd.parent),
      pos_(nd.pos_),
      children(nd.children),
      slots_(nd.slots_)
    {

    }
    
    
    using Ptr = std::shared_ptr<TreeNode<Elem>>;
    using WeakPtr = std::weak_ptr<TreeNode<Elem>>;

    TreeNode(const TreeNode::Ptr nd)
    : Terminal<Elem>(nd),
    id_(nd->id_),
    parent(nd->parent),
    pos_(nd->pos_),
    children(nd->children),
    slots_(nd->slots_)
    {
        
    }
    
    // @todo : TODO
    template<typename Callback>
    void
    wfs(Callback cb) {
        std::queue<TreeNode*> q;
        q.push(this);
        int curr_no = 1, depth =1, next_no=0;
        typedef map<int, bool> VisitedTab;
        VisitedTab visitedtab;
        vector<TreeNode*> visited;
        
        while(!q.empty()) {
            TreeNode<Elem>* curr = q.front(); q.pop();
            curr_no--;
            auto it = visitedtab.find(curr->id());
            if (it != visitedtab.end()) {
                continue;
            } else {
                visitedtab[curr->id()] = true;
                visited.push_back(curr);
                cb(curr, depth);
            }
            
            auto neighbors = curr->getChildren([&, depth, visitedtab, this](TreeNode<int>* child)->bool {
                auto it = visitedtab.find(child->id());
                if (it != visitedtab.end()) {
                    
                    return false;

                } else {
                    return true; //  add other logics here
                }
            });
            next_no += neighbors.size();
            
            for (auto neighbor : neighbors) {
                q.push(neighbor.get());
            }
            
            if (curr_no == 0) {
                depth++;
                curr_no = next_no;
                next_no = 0;
            }
            
        }
        
    }
    
    // @todo : TODO
    template<typename Callback>
    void
    dfs(Callback cb) {
    
    }
    
    int id() {
        return id_;
    }
    
    TreeNode*
    set_pos(int pos) {
        pos_ = pos;
    }
    
    int
    get_pos() {
        return pos_;
    }
       
    TreeNode*
    add(TreeNode::Ptr nd) {
        if (nd->parent.lock().get() != this) {
            TreeNode::Ptr  parent = std::enable_shared_from_this<TreeNode<Elem>>::shared_from_this();
            nd->set_parent(parent);
        } else if (nd->get_pos() == -1) {
            return this;
        } else if (nd->get_pos() != -1 && this->children[nd->get_pos()].get() == nd.get()) {
            return this;
        }

        this->children.push_back(nd);
        this->slots_++;
        nd->set_pos(this->children.size());
        return this;
    }
    
    TreeNode*
    set_parent(TreeNode::WeakPtr parent) {
        TreeNode::Ptr child = std::enable_shared_from_this<TreeNode<Elem>>::shared_from_this();
        if (this->parent.lock().get() != nullptr && this->parent.lock().get() != parent.lock().get()) {
            this->parent.lock()->remove(child);
        }

        this->parent = parent;
        parent.lock()->add(child);
        return this;

    }

    TreeNode::Ptr
    remove(TreeNode::Ptr nd) {
        TreeNode::Ptr deleted = this->children[nd->get_pos()];
        this->children[nd->get_pos()] = nullptr;
        this->slots_--;
        deleted->set_parent(TreeNode<Elem>::WeakPtr());
        
        if (Overloadded()) {
            Reformed();
        }
        
        return deleted;
        
    }
    
    vector<TreeNode::Ptr>
    getChildren() {
        vector<TreeNode::Ptr> ret = filter_func<TreeNode::Ptr>(children, [&, this](TreeNode::Ptr child) -> bool {
            if (child != nullptr) {
                return true;
            } else {
                return false;
            }
        });
        
        return ret;
        
    }
    
    template<typename Callback>
    vector<TreeNode::Ptr>
    getChildren(Callback cb) {
        vector<TreeNode::Ptr> children = getChildren();
        vector<TreeNode::Ptr> ret = filter_func<TreeNode::Ptr>(children, [&, this](TreeNode::Ptr child) -> bool {
            if (cb(child.get())) {
                return true;
            } else {
                return false;
            }
        });
        
        return ret;
    }
    
    // Enhance performance using an overrloading factor
    bool Overloadded() {
        return slots_ / double(children.size()) < alpha;
    }
    
    void Reformed() {
        vector<TreeNode::Ptr> filtered = filter_func<TreeNode::Ptr>(children, [&, this](TreeNode::Ptr child) -> bool {
            if (child != nullptr) {
                return true;
            } else {
                return false;
            }
        });

        for (int i=0; i < filtered.size(); i++) {
            filtered[i]->set_pos(i);
        }
 
        this->children = filtered;       

    }
    
    virtual Elem el() {
        return this->el_;
    }
    
    virtual TreeNode<Elem>* set_el(Elem el) override {
        this->el_ = el;
        return this;
    }
    
protected:
    int id_ = -1;
    TreeNode::WeakPtr parent;
    int pos_ = -1;
    vector<TreeNode::Ptr> children;
    static double alpha;
    int slots_ = 0;
};

template<class Elem>
double TreeNode<Elem>::alpha = ALPHA;

// Imporved Disjointed Set ADS by Lei in 2016. The data structure was also used in HDMap Generation project and under patenting in 2018 with other bunch jointed algorithms.
template<class Elem>
class DisjointedNode : public TreeNode<Elem>
{
public:
    explicit DisjointedNode(Elem& el): TreeNode<Elem>(el) {
        init();
    }
    
    void
    init() {
        this->set_parent(TreeNode<Elem>::shared_from_this()); // make itself a set
        // randomness
        std::random_device device;
        std::mt19937 gen(device());
        std::bernoulli_distribution coin_flip(0.5);
        gen_ = gen;
        coin_flip_ = coin_flip;
    }
    
    typename TreeNode<Elem>::Ptr
    findByCmpr() {
        if (this->parent.lock.get() != this) {
            this->set_parent(this->parent->findByCmpr());
        }
        return this->parent.lock();
    }
    
    void
    set_rank(double rank) {
        rank_ = rank;
    }
    
    double
    rank() {
        return rank_;
    }
    
    void
    unionByRank(TreeNode<Elem> other) {
        auto left = this->findByCmpr();
        auto right = other->findByCmpr();
        
        if (left->rank() < right->rank()) {
            left->set_parent(right);
        } else if (left->rank() > right->rank()) {
            right->set_parent(left);
        } else {
            if (coin_flip_(gen_)) {
                left->set_parent(right);
                right->set_rank(right->rank() + 1);
            } else {
                right->set_parent(left);
                left->set_rank(right->rank() + 1);
            }
        }
    }
    
private:
    double rank_ = 0;
    std::mt19937 gen_;
    std::bernoulli_distribution coin_flip_;
    
};

#endif /* graph_h */
