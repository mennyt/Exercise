
// C++ program to find single source shortest paths for Directed Acyclic Graphs 
#include<iostream> 
#include <algorithm>
#include <map>

int countCalls = 0;
double countStepsUtil(int steps, std::map<int, double>& stepsToCount) {
    countCalls++;
    if (steps == 0) {
        return 0;
    }
    if (steps == 1) {
        return 1;
    }
    if (steps < 0) { //or if steps == 2 return 3
        return -1;
    }
    
    auto iter = stepsToCount.find(steps);
    if (iter != stepsToCount.end()) {
        // std::cout << " steps= " << steps << " found in map= " << iter->second << std::endl;
        return iter->second;
    }
    
    int res = 3 + countStepsUtil(steps-1, stepsToCount) + 
    countStepsUtil(steps-2, stepsToCount) + 
    countStepsUtil(steps-3, stepsToCount);
    
    stepsToCount[steps] = res;
    
    // std::cout << " steps= " << steps << " added to map: " << res << std::endl;
    
    return res;
}

double countSteps(int steps) {
    std::map<int, double> stepsToCount;
    return countStepsUtil(steps, stepsToCount);
}

int main() {
    std::cout << countSteps(10) << std::endl;
    std::cout << "Number of calls: " << countCalls;
    
}
