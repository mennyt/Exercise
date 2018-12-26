
// C++ program to find single source shortest paths for Directed Acyclic Graphs 
#include<iostream> 
#include <list>
#include <queue>
#include <stack>

//This code isn't tested!!!

//Find next node that comes in 'in order' traversal on a tree
Node* findNextInOrder(Node* node) {
    if (!node) {
        return nullptr;
    }
    
    //Has right sub tree - next node must comes from there at the most left as possible
    if (node->right) {
        Node* rightSubTree = node->right;
        while (rightSubTree && rightSubTree->left) {
            rightSubTree = rightSubTree->left;
        }
        return rightSubTree;
    }
    
    //Doesn't have a right sub tree nor a parent - end of the traverse!
    if (!node->parent) {
        return nullptr;
    }
    
    //has parent, don't have a right sub tree - next should be the most parent on the left...
    Node* parent = node->parent;
    while (parent && parent->right == node) {
        node = parent;
        parent = parent->parent;
    }
    return parent
}

int main() {
  
  
}