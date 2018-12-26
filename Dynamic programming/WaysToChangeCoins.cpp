//This program finds all possible ways to change an ammount of money to coins of
//quarters(25 cents), dimes(10 cents), nickels(5 cents) and pennies(1 cent)

#include <iostream> 
#include <map>
#include <list>

struct Change {
    int quarters=0;
    int dimes=0;
    int nickels=0;
    int pennies=0;
};
using ChangeWays = std::list<Change>;

using CacheChange = std::map<int, int>;
int countCalls = 0;

int numWaysToChangeUtil(int ammount, Change currChange, ChangeWays& changeWays, CacheChange& cache) {
    countCalls++;
    int remainPennies = (ammount % 5);
    currChange.pennies += remainPennies;
    int val = ammount - remainPennies; //Round the pennies, since there is only one option for this small change...
    
    if (val < 0) {
        return 0;
    }
    if (val <= 1) {
        changeWays.push_back(currChange);
        return 1;
    }
    
    auto currValIter = cache.find(val);
    if (currValIter != cache.end()) {
        return currValIter->second;
    }
    
    int quarter, dime, nickel, pennie;
    auto pennieIter = cache.find(val-1);
    if (pennieIter != cache.end()) {
        pennie = pennieIter->second;
    } else {
        Change change(currChange);
        change.pennies++;
        pennie = numWaysToChangeUtil(val - 1, change, changeWays, cache);
    }
    
    auto nickelIter = cache.find(val-5);
    if (nickelIter != cache.end()) {
        nickel = nickelIter->second;
    } else {
        Change change(currChange);
        change.nickels++;
        nickel = numWaysToChangeUtil(val - 5, change, changeWays, cache);
    }
    
    auto dimeIter = cache.find(val-10);
    if (dimeIter != cache.end()) {
        dime = dimeIter->second;
    } else {
        Change change(currChange);
        change.dimes++;
        dime = numWaysToChangeUtil(val - 10, change, changeWays, cache);
    }
    
    auto quarterIter = cache.find(val-25);
    if (quarterIter != cache.end()) {
        quarter = quarterIter->second;
    } else {
        Change change(currChange);
        change.quarters++;
        quarter = numWaysToChangeUtil(val - 25, change, changeWays, cache);
    }
    
    int res = pennie + nickel + dime + quarter;
    cache[ammount] = res;
            
}

int numWaysToChange(int val) {
    CacheChange cache;
    Change currChange;
    ChangeWays changeWays;
    int res = numWaysToChangeUtil(val, currChange, changeWays, cache);
    std::cout << "\nnumber of ways according to output structure: " << changeWays.size() << "\n";
    for (auto change : changeWays) {
        std::cout << "\nChange:\n";
        std::cout << change.pennies << " pennies, " << change.nickels <<
        " nickels, " << change.dimes << " dimes, " << change.quarters << "quarters";
    }
    return res;
}

int main() {
    int value = 12;
    std::cout << "\n" << numWaysToChange(value);
    std::cout << "\nNumber of calls: " << countCalls;
    return 0;
}