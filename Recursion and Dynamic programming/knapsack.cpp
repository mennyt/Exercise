
// C++ program to find single source shortest paths for Directed Acyclic Graphs 
#include<iostream> 
#include <vector> 
#include <string>
#include <map>

class Item {
public:
    Item(int itemWight, int itemValue, int itemCount = 1) : 
        weight(itemWight), value(itemValue), id(++s_counter), count(itemCount) {}
    ~Item() {}
    
    std::string toString() const {
        return std::to_string(id) + ',' + std::to_string(count);
    }
    int weight;
    int value;
    int id;
    int count;
    
private:
    static int s_counter;
};
int Item::s_counter = 0;

class Sack {
public:
    Sack(const std::vector<Item>& itemList): items(itemList) {}
    Sack(const Sack& other) : items(other.items) {}
    Sack(){}
    ~Sack() {}
    
    int getWeight() const {
        int weight = 0;
        for (auto item : items) {
            weight += item.weight;
        }
        return weight;
    }
    
    int getValue() const {
        int value = 0;
        for (auto item : items) {
            value += item.value;
        }
        return value;
    }
    
    bool betterThan(const Sack& other) const {
        return getValue() > other.getValue();
    }
    
    void addItem(const Item& item) {
        items.push_back(item);
    }
    void print() const {
        if (items.empty()) {
            std::cout << "sack is empty!";
            return;
        } 
        for (auto item : items) {
            std::cout << "id: " << item.id << ", ";
        }
        
        std::cout << "\nTotal weight: " << getWeight();
        std::cout << "\nTotal value: " << getValue();
    }
    
    std::vector<Item> items;
};

using Items = std::vector<Item>;
using CallstackCache = std::map<std::string, Sack>;

std::string callstackToString(const Items& items, int targetValue) {
    std::string outputStr;
    for (auto item : items) {
       outputStr += (item.toString() + "-");
    }
    outputStr += ("TargetValue: " + std::to_string(targetValue));
    return outputStr;
}

int callstackCount = 0; //for debug - check how may calls to recursive function

Sack knapsackUtil(Items availableItems, int targetWeight, Sack sack, CallstackCache& callstackCache) {
    callstackCount++;
    Sack bestSack = sack;
    for (auto iter = availableItems.begin(); iter != availableItems.end(); ++iter) {
        if (!iter->count || iter->weight > targetWeight) {
            continue;
        }
        
        iter->count--; //Reduve item count 
        
        std::string cacheStr = callstackToString(availableItems, targetWeight - iter->weight);
        auto cacheIter = callstackCache.find(cacheStr);
        Sack currSack;
        if (cacheIter == callstackCache.end()) {
            currSack = sack;
            currSack.addItem(*iter);
            currSack = knapsackUtil(availableItems, targetWeight - iter->weight, currSack, callstackCache);
            
            //Add to cache
            callstackCache[cacheStr] = currSack; //TODO: Better use move assignment operation to avoid cloning
        } else {
            currSack = cacheIter->second;
        }
        
        if (currSack.betterThan(bestSack)) {
            bestSack = currSack;
        }
        iter->count++; //increase back item count so that the item will be checked independantly
    }
    return bestSack;
}

Sack knapsack(Items availableItems, int targetWeight, Sack sack) {
    CallstackCache callstackCache;
    return knapsackUtil(availableItems, targetWeight, sack, callstackCache);
}

int main() 
{ 
    Items availableItems = {{1, 3, 4}, {4, 3}, {8, 4}, {9, 0}, {2, 8}, {3, 3}, {2, 18}};
    int targetWeight = 9;
    Sack sack;
    Sack res = knapsack(availableItems, targetWeight, sack);
    res.print();
    
    std::cout << "\nnumber of calls: " << callstackCount;
    
} 