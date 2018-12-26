
// C++ program to find single source shortest paths for Directed Acyclic Graphs 
#include<iostream> 
#include <stack> 
#include <string>
#include <map>

using Cubes = std::stack<int>;

void printStack(Cubes cubes) {
    while (!cubes.empty()) {
        int val = cubes.top();
        cubes.pop();
        std::cout << val << "\n";
    }
}

void hanoiWithChar(int val, char src, char target, char aux) {
    if (val == 0) {
        return;
    }
    if (val == 1) {
        std::cout << "Move " << val << " to " << target << std::endl;
        return;
    }
    hanoiWithChar(val-1, src, aux, target);
    std::cout << "Move " << val << " to " << target << std::endl;
    hanoiWithChar(val-1, aux, target, src);
}

Cubes target, aux;
Cubes source ({5, 4, 3, 2, 1});
Cubes& getCubes(char cubesName) {
    switch(cubesName) {
        case 'A':
            return source;
        case 'B':
            return target;
        case 'C':
            return aux;
    }
}

void moveDisc(char src, char target) {
    Cubes& srcCubes = getCubes(src); 
    Cubes& targetCubes = getCubes(target);
    
    int val = srcCubes.top();
    srcCubes.pop();
    
    targetCubes.push(val);
    
    std::cout << "Move " << val << " to " << target << std::endl;
}

void hanoiWithStack(int val, char src, char target, char aux) {
    if (val == 0) {
        return;
    }
    if (val == 1) {
        moveDisc(src, target);
        return;
    }
    hanoiWithStack(val-1, src, aux, target);
    moveDisc(src, target);
    hanoiWithStack(val-1, aux, target, src);
}

struct ManualStackItem {
    int val;
    char src;
    char target;
    char aux;
    bool firstCall; //true when there's a need to return to this stack again...
};

void iterativeHanoi(int Ival, char Isrc, char Itarget, char Iaux) {
    std::stack<ManualStackItem> manualStack;
   
    manualStack.push({Ival, Isrc, Itarget, Iaux, true});
    while(!manualStack.empty()) {
        ManualStackItem manualStackItem = manualStack.top();
        manualStack.pop();
        
        int val = manualStackItem.val;
        char src = manualStackItem.src;
        char target = manualStackItem.target;
        char aux = manualStackItem.aux;
        if (val == 0) {
            continue;
        }
        if (val == 1) {
            moveDisc(src, target);
            continue;
        }
        
        if (manualStackItem.firstCall) {
            manualStackItem.firstCall = false;
            manualStack.push(manualStackItem);
            manualStack.push({val-1, src, aux, target, true});
        } else {
            moveDisc(src, target);
            manualStack.push({val-1, aux, target, src, true});
        }
    }
}

int main() {
    // printStack(source);
    // std::cout << std::endl;
    hanoiWithChar(4, 'A', 'B', 'C');
    // hanoiWithStack(source.size(), 'A', 'B', 'C');
    iterativeHanoi(source.size(), 'A', 'B', 'C');
    printStack(target);
    
    
} 