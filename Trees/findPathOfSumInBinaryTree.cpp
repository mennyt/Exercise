
// C++ program to find single source shortest paths for Directed Acyclic Graphs 
#include<iostream> 
#include <list>

//This function returns a path that gives a sum equals 'target' from any node
void getPath(Node* node, int target, int countLeft, Path currPath, PathList& pathList) {
    if ((!node || !countLeft) && !currPath.empty()) {
        // pathList.push(path);
        return;// true;
    }
    
    //With current node    
    Path pathWithNode(currPath);
    pathWithNode.push(node);
    pathList.push(path);
    
    //Continue since the values may be negative
    getPath(node->left, target, target-node->value, pathWithNode);
    getPath(node->right, target, target-node->value, pathWithNode);
    
    //If not during a path, search for a path in the left/right without curr node
    if (currPath.empty()) {
        getPath(node->left, target, target, currPath, currPath);
        getPath(node->right, target, target, currPath, currPath);
    }  
}
