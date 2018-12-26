
// C++ program to find single source shortest paths for Directed Acyclic Graphs 
#include<iostream> 
#include <stack>

using intStack = std::stack<int>;

int popFromStack(intStack& stack) {
    int val = stack.top();
    stack.pop();
    return val;
}
void moveToStack(intStack& source, intStack& target) {
    while (!source.empty()) {
        int curr = popFromStack(source);
        target.push(curr);
    }
}
void sortStack(intStack& inputStack) {
    intStack auxStack;
    
    while(!inputStack.empty()) {
        int curr = popFromStack(inputStack);
        if (auxStack.empty()) {
            auxStack.push(curr);
            continue;
        }
        int topAuxStack = auxStack.top();
        if (curr <= topAuxStack) {
            auxStack.push(curr);
            continue;
        }
        while(!auxStack.empty() && auxStack.top() < curr) {
            topAuxStack = popFromStack(auxStack);
            inputStack.push(topAuxStack);
        }
        //either auxStack is empty, or top of the stack is bigger/equal to curr
        auxStack.push(curr);
    }
    moveToStack(auxStack, inputStack);
}

void printStack(intStack stack) { //We don't want to clear the stack for printout...
    std::cout << "sorted stack: ";
    while (!stack.empty()) {
        int curr = popFromStack(stack);
        std::cout << curr << ", ";
    }
}

int main() {
  intStack stack;
  stack.push(5);
  stack.push(3);
  stack.push(8);
  stack.push(2);
  stack.push(7);
  stack.push(5);
  stack.push(2);

  sortStack(stack);
  printStack(stack);
  
}