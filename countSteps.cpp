
// C++ program to find single source shortest paths for Directed Acyclic Graphs 
#include<iostream> 
#include <algorithm>
#include <map>

int countCalls = 0;

double countWaysUtil(int steps, std::map<int, double>& stepsToCount) {
    countCalls++;
    if (steps == 0) {
        return 1;
    }
    if (steps < 0) {
        return 0;
    }
   
    auto iter = stepsToCount.find(steps);
    if (iter != stepsToCount.end()) {
        // std::cout << " steps= " << steps << " found in map= " << iter->second << std::endl;
        return iter->second;
    }
    
    int res = countWaysUtil(steps-1, stepsToCount) + 
    countWaysUtil(steps-2, stepsToCount) + 
    countWaysUtil(steps-3, stepsToCount);
    
    stepsToCount[steps] = res;
    
    // std::cout << " steps= " << steps << " added to map: " << res << std::endl;
    return res;
}

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

double countWays(int steps) {
    std::map<int, double> stepsToCount;
    return countWaysUtil(steps, stepsToCount);
}

int main() {
    int strais = 10;
    std::cout << "number of steps to go up " << strais << " strais: " << countSteps(strais) << std::endl;
    std::cout << "number of ways to go up " << strais << " strais: " << countWays(strais) << std::endl;
    // std::cout << "Number of calls: " << countCalls;
    
}
