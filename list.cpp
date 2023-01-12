/**
    @author [mst]
    @file   list.cpp
    @brief  Linked list implementations

    [bp] there are different approaches to linked list implementations. A "value
    and pointer" node with a push function will suffice for quick tasks. A
    higher level "list" structure may be added to encapsulate additional
    functionality, tail pointers, prints, reverse methods.

    [wip] add reversall, deletion etc. functionality, vector to lisr etc.

    features, changelog:
    -2023.01: -some more helper functionality
    -2021.04: -initial draft

    @author [mst]
    @version 0.1 2022.04
*/


#include "list.hpp"
#include <iostream>         // usage of console prints


////////////////// DECL_IMPL

void ListNode::printList() {
    if (this == nullptr) {
        std::cout << "empty list" << std::endl;
        return;
    }

    ListNode* lp = this;
    while (lp) {
        std::cout << lp->val << "->";
        lp = lp->next;
    }

    std::cout << "nullptr" << '\n';
}

// [demo] externally define a class method
ListNode::ListNode(int x, ListNode *next): 
    val(x), next(next) {}


// list push helper function
void pushList(ListNode* &head, int val) {
    // [bp] this will still work with an empty list case
    ListNode* NewNode = new ListNode(val, head);
    head = NewNode;
}

// list end insertion helper function
void addTailList(ListNode* &head, int val) {
    //if (head == nulptr) { // [demo] unnecessary check
    //    return
    //}
    ListNode* NewNode = new ListNode(val, nullptr);
    if (head == nullptr) {
        head = NewNode;
        return;
    }

    ListNode* ptr = head;
    while (ptr->next) {
        ptr = ptr->next;
    }    
    ptr->next = NewNode;
}






////////////////// DRIVER
int main()
{
    // [bp] putting this in the global space is an overhead
    // even worse in a header file as would foce including in all users
    using namespace std;

    // [bp] using endl would force a flush.                            
    cout << "[mst] cpp linked listss doodle" << '\n' << '\n';

    ListNode* l5 = nullptr;
    addTailList (l5,9);
    addTailList (l5,9);
    addTailList (l5,9);
    pushList (l5,8);
    addTailList (l5,9);
    addTailList (l5,9);
    addTailList (l5,9);
    l5->printList();
    




	return 0;
}


