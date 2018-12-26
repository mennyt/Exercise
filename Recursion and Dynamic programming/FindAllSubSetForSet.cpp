//This program finds all possible subsets for a given set

#include <iostream> 
#include <set>

using MySet = std::set<int>;
using MySetList = std::set<MySet>;
int callCount = 0;

//------ First solution - check all options (BEGIN) ------//
void getSetsUtil(MySet input, MySet currSet, MySetList& setList) {
    for (auto val : input) {
        callCount++;
        //Without val
        MySet copyInput(input);
        copyInput.erase(val);
        
        getSetsUtil(copyInput, currSet, setList);
        
        //With val
        currSet.insert(val);
        getSetsUtil(copyInput, currSet, setList);
    }  
    setList.insert(currSet);
}

MySetList getSets(const MySet& input) {
    //time complexity - O(2^n), which is the number of all sets.
    //For each item, it can either be or not be in every set (2 choices, for n elements)
    //Since all options of all sets are being checked
    
    MySet currSet;
    MySetList setList;
    getSetsUtil(input, currSet, setList);
    
    return setList;
}
//------ First solution - check all options (END) ------//

//------ Second solution - Add current element to all sets (BEGIN) ------//
MySetList getSetsOptimized(MySet& input) {
    MySetList setList;
    setList.insert(MySet());
    
    for (auto val : input) {
        for (auto set : setList) {
            callCount++;
            MySet newSet(set);
            newSet.insert(val);
            setList.insert(newSet);
        }
    }
    return setList;
}
//------ Second solution - Add current element to all sets (END) ------//

//------ Bi wise manipulation solution (START)------//
MySet intToSet(int val, int* arr) {
    MySet mySet;
    int index = 0;
    for (int k = val; k > 0; k >>= 1) {
        if (k & 1) {
            mySet.insert(arr[index]);
        }
        ++index;
    }
    return mySet;
}

MySetList bitWiseFindAllSets(int* arr, int size) {
    MySetList setList;
    int numSets = 1 << size; //number of sets is 2^n
    for (int i = 0; i < numSets; ++i) {
       setList.insert(intToSet(i, arr)); 
    }
    return setList;
}
//------ Bi wise manipulation solution (END)------//


void printSets(const MySetList& sets) {
    std::cout << "\n\nnumber of calls: " << callCount << "\n";
    std::cout << "number of sets: " << sets.size() << "\n";
    for (auto set : sets) {
        std::cout << "set size " << set.size() << ": ";
        for (auto val : set) {
            std::cout << val << ", ";
        }
        std::cout << "\n";
    }    
}

int main() {
    MySet mySet{1, 2, 3, 4, 5, 6};
    MySetList set1 = getSets(mySet);
    printSets(set1);
    
    callCount = 0;
    
    MySetList set2 = getSetsOptimized(mySet);
    printSets(set2);
    
    int arr[6] {1, 2, 3, 4, 5, 6};
    MySetList set3 = bitWiseFindAllSets(arr, 6);
    printSets(set3);
}
