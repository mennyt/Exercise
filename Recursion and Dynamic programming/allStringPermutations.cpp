//This program finds all possible subsets for a given string
//For example: 
//input='dog'
//output= dog, dgo, god, gdo, ogd, odg

#include <iostream> 
#include <list>
#include <set>

using StringList = std::list<std::string>;

//The idea is to imagine the base case 
// size=0: input="" output={""}
//size=1: input="a" output={"a"}
//size=2: input="ab" output={"ab", "ba"}
//The question we should always ask is- "how can we use f(n-1) to solve f(n)?"
//In this case, for level of size=3, we should simple add "c" to all locations of all permutations of f("ab")... 

StringList allPermutations(const std::string& str) {
    if (str.size() == 0) {
        return StringList{str};
    }
    std::string remainder(str);
    char firstChar = remainder[0];
    remainder.erase(remainder.begin());
    StringList permutations = allPermutations(remainder);
    
    StringList newPermutations;
    //push firstChar to all permutations...
    for (auto permutation : permutations) {
        if (permutation.size() == 0) {
            std::string newString (1, firstChar);
            newPermutations.push_back(newString);
        } else {
            newPermutations.push_back(firstChar + permutation);
            newPermutations.push_back(permutation + firstChar);
            for (int i = 1; i <= permutation.size()-1; ++i) {
                std::string newString = permutation.substr(0, i) + std::string(1, firstChar) + permutation.substr(i, permutation.size()-i);
                newPermutations.push_back(newString);
            }
        }
    }
    return newPermutations;
}

void printPermutations(const StringList& permutations) {
    std::cout << "nunmber of permutations: " << permutations.size() << "\n";
    
    for (auto str : permutations) {
        std::cout << str << ", ";
    }
}

int main() {
    std::string str = "dogi";
    StringList permutations = allPermutations(str);
    printPermutations(permutations);
    
    return 0;
}