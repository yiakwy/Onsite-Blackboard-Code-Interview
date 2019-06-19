//
//  quick_linked_sort.cpp
//  ApolloTeam
//
//  Created by Wang Yi on 19/6/19.
//
//
#include <iostream>

typedef struct _node_t {
    int val;
    _node_t* next = nullptr;
    
    _node_t() {}
    _node_t(int val) {
        this->val = val;
    }
} Node;

void init_linked_array(int* arr, int n, Node** root)
{
    *root = new Node(arr[0]);
    
    Node* cur = *root;
    cur->next = nullptr;
    
    for (int i=1; i < n; i++)
    {
        Node* nd = new Node(arr[i]);
        nd->next = nullptr;
        
        cur->next = nd;
        cur = cur->next;
    }
}

Node* quick_linked_sort(Node* head)
{
    if (head == nullptr) {
        return nullptr;
    }
    
    if (head->next == nullptr) {
        return head;
    }
    
    Node* smaller = nullptr;
    Node* bigger = head;
    
    // partition
    Node* pre = head;
    Node* cur = head->next;
    int x = head->val;
    
    while (cur != nullptr)
    {
        if (cur->val <= x) {
            pre->next = cur->next;
            
            if (smaller == nullptr) {
                smaller = cur;
                cur->next = nullptr;
            } else {
                Node* next = smaller->next;
                smaller->next = cur;
                cur->next = next;
            }
            
            cur = pre->next;
        } else {
        
            pre = cur;
            cur = cur->next;
        }
    }
    
    smaller = quick_linked_sort(smaller);
    Node* pivot = bigger;
    bigger = quick_linked_sort(bigger->next);
    pivot->next = bigger;
    
    if (smaller == nullptr) {
        return pivot;
    }
    Node* tail = smaller;
    cur = smaller->next;
    while (cur != nullptr) {
        tail = cur;
        cur = cur->next;
    
    }
    
    tail->next = pivot;
    return smaller;
    
}

// Imporved version subquestion 2: 25% zeros
Node* quick_linked_sort_with_least_duplicated_zeros(Node* head)
{
    if (head == nullptr) {
        return nullptr;
    }
    
    if (head->next == nullptr) {
        return head;
    }
    
    Node* smaller = nullptr;
    Node* bigger = head;
    
    // partition
    Node* pre = head;
    Node* cur = head->next;
    int x = 0; //head->val;
    
    while (cur != nullptr)
    {
        if (cur->val <= x) {
            pre->next = cur->next;
            
            if (smaller == nullptr) {
                smaller = cur;
                cur->next = nullptr;
            } else {
                Node* next = smaller->next;
                smaller->next = cur;
                cur->next = next;
            }
            
            cur = pre->next;
        } else {
            
            pre = cur;
            cur = cur->next;
        }
    }
    
    // remove the line to process the smaller linked list

    // use normal quick sort
    bigger = quick_linked_sort(bigger); // pass all
    
    if (smaller == nullptr) {
        return bigger;
    }
    Node* tail = smaller;
    cur = smaller->next;
    while (cur != nullptr) {
        tail = cur;
        cur = cur->next;
        
    }
    
    tail->next = bigger;
    return smaller;
    
}

// Imporved version subquestion 3: considering non-uniform distribution
Node* quick_linked_sort_with_least_duplicated_elements(Node* head)
{
    if (head == nullptr) {
        return nullptr;
    }
    
    if (head->next == nullptr) {
        return head;
    }
    
    Node* smaller = nullptr;
    Node* duplicated = nullptr;
    Node* tail = nullptr;
    Node* bigger = head;
    
    // partition
    Node* pre = head;
    Node* cur = head->next;
    int x = head->val;
    
    while (cur != nullptr)
    {
        // to process duplicated elements, split the array into three parts
        if (cur->val == x) {
            pre->next = cur->next;
            
            if (smaller == nullptr) {
                smaller = cur;
                duplicated = cur;
                tail = smaller;
                cur->next = nullptr;
            } else {
                tail->next = cur;
                cur->next = nullptr;
                tail = tail->next;
            }
            cur = pre->next;
        }
        else if (cur->val < x) {
            pre->next = cur->next;
            
            if (smaller == nullptr) {
                smaller = cur;
                tail = smaller;
                cur->next = nullptr;
            } else {
                Node* next = smaller->next;
                smaller->next = cur;
                cur->next = next;
            }
            
            cur = pre->next;
        } else {
            
            pre = cur;
            cur = cur->next;
        }
    }
    
    if (duplicated == nullptr) {
        smaller = quick_linked_sort_with_least_duplicated_elements(smaller);
    } else {
        Node* pre = nullptr;
        Node* cur = smaller;
        
        while (cur != nullptr)
        {
            if (cur->val == x) {
                break;
            }
            pre = cur;
            cur = cur->next;
        }
        
        if (pre != nullptr) {
            pre->next = nullptr;
            smaller = quick_linked_sort_with_least_duplicated_elements(smaller);
            
            pre = nullptr;
            cur = smaller;
            while (cur != nullptr)
            {
                pre = cur;
                cur = cur->next;
            }
            pre->next = duplicated;
        }
        
        
    }
    Node* pivot = bigger;
    bigger = quick_linked_sort_with_least_duplicated_elements(bigger->next);
    pivot->next = bigger;
    
    if (smaller == nullptr) {
        return pivot;
    }
    tail = smaller;
    cur = smaller->next;
    while (cur != nullptr) {
        tail = cur;
        cur = cur->next;
        
    }

    tail->next = pivot;
    return smaller;
    
}


void print(Node* head)
{
    while (head != nullptr)
    {
        std::cout << head->val << ", ";
        head = head->next;
    }
    std::cout << std::endl;
}

#define N 8
#define N0 14

int main(int argc, char** argv)
{
    int array[N] = {2, 8, 7, 1, 3, 5, 6, 4};
    int array0[N0] = {0, 8, 7, 1, 3, 5, 6, 4, 1, 2, 0, 10, 0, 0};
    
    Node* head;
    init_linked_array(array, N, &head);
    
    head = quick_linked_sort(head);
    
    std::cout << "Solution for subquestion 0:" << std::endl;
    print(head);
    
    
    Node* head0;
    Node* head1;
    init_linked_array(array0, N0, &head0);

    head0 = quick_linked_sort_with_least_duplicated_zeros(head0);
    
    std::cout << "Improvement for subquestion 2:" << std::endl;
    print(head0);
    
    init_linked_array(array0, N0, &head1);
    head1 = quick_linked_sort_with_least_duplicated_elements(head1);
    
    std::cout << "Improvement for subquestion 3:" << std::endl;
    print(head1);
    
}
