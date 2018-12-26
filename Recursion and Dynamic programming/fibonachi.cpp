
// C++ program to find single source shortest paths for Directed Acyclic Graphs 
#include<iostream> 
#include <map> 

int recursiveFib(int val) {
    if (val == 0 || val == 1) {
        return val;
    }
    return recursiveFib(val-1) + recursiveFib(val-2);
}

int dynamicProgrammingFibUtil(int val, std::map<int, int>& cache) {
    if (val == 0 || val == 1) {
        return val;
    } 
    int minus1, minus2;
    
    auto fibMinus1 = cache.find(val-1);
    if (fibMinus1 != cache.end()) {
        minus1 = fibMinus1->second;
    } else {
        minus1 = dynamicProgrammingFibUtil(val-1, cache);
        cache[val-1] = minus1;
    }
    
    auto fibMinus2 = cache.find(val-2);
    if (fibMinus2 != cache.end()) {
        minus2 = fibMinus2->second;
    } else {
        minus2 = dynamicProgrammingFibUtil(val-2, cache);
        cache[val-2] = minus2;
    }
    
    return minus1 + minus2;
}

int dynamicProgrammingFib(int val) {
    std::map<int, int> cache;
    return dynamicProgrammingFibUtil(val, cache);
}

int bottomToTopFib(int val) {
    if (val == 0 || val == 1) {
        return val;
    }
    
    int prev1 = 0;
    int cur = 1;
    for (int i = 2; i <= val; ++i) {
        int tmpCur = cur;
        cur = cur + prev1;
        prev1 = tmpCur;
    }
    return cur;
}

int main() 
{ 
    //0 1 1 2 3 5 8 13 21 34
    int val = 9;
    std::cout << "recursive: " << recursiveFib(val) << std::endl;
    std::cout << "bottom to top: " << bottomToTopFib(val) << std::endl;
    std::cout << "dynamicProgrammingFib: " << dynamicProgrammingFib(val);
} 