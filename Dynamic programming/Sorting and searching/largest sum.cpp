//
//1. Implement functions for finding largest sum and largest increasing order of integers and pairs.
//2. In case the problem is arranding n items one on top of the other, so that a small item will be on top a
//larger one:
//  2.1 We first have to sort the items and then reffer to the largest increasing order issue.
//  2.2 In case the items should be sorted by pair of values, we should implement a class for this item with the 
//relevant comparator

#include <iostream>

class Item {
public:
    Item(int h, int w) : height(h), width(w) {}
    bool operator<(const Item& other) {
        return (height < other.height && width < other.width);
    }
    
    //operator> in this case, isn't the opposite of operator<.
    //We may have a case that a isn't less than b, b isn't less than a and they aren't equal...
    bool operator>(const Item& other) {
        return (height > other.height && width > other.width);
    }
    int height;
    int width;
};


//Find the longest increasing sub sequence in an array
int longestSubSequence(Item* arr, int size) {
    if (size == 0) {
        return 0;
    }
    
    int maxSequenceLength = arr[0].height; 
    int currSequenceLength = arr[0].height;
    int currLastIndex = 0;
    for (int i = 1; i < size; ++i) {
        // std::cout << "Checking " << i << " > " << currLastIndex << "\n";
        if (arr[i] > arr[currLastIndex]) {
            // std::cout << i << " > " << currLastIndex << "\n";
            currLastIndex++;
            currSequenceLength += arr[i].height;
            
            if (currSequenceLength > maxSequenceLength) {
                maxSequenceLength = currSequenceLength;
            }
        } else {
            currLastIndex = i;
            currSequenceLength = 1;
        }
    }
    return maxSequenceLength;
}

//Find the longest increasing sub sequence in an array
int longestSubSequence(int* arr, int size) {
    if (size == 0) {
        return 0;
    }
    
    int maxSequenceLength = 1; 
    int maxEndIndex = 0;
    
    int currSequenceLength = 1;
    int currEndIndex = 1;
    for (int i = 1; i < size; ++i) {
        if (arr[i] > arr[currEndIndex]) {
            currEndIndex++;
            currSequenceLength++;
        } else {
            if (currSequenceLength > maxSequenceLength) {
                maxSequenceLength = currSequenceLength;
                maxEndIndex = currEndIndex;
            }
            currEndIndex = i;
            currSequenceLength = 1;
        }
    }
    return maxSequenceLength;
}

//Find largest sum in an array - assuming not all negative
//This can be improved to support all negativw, by handling specific this case and simply find the max value...
int largestSum(int* arr, int size) {
    if (size == 0) {
        return -1;
    }
    int maxSum = 0;
    int currMax = 0;
    for (int i = 0; i < size; ++i) {
        currMax += arr[i];
        if (currMax < 0) {
            currMax = 0;
        }
        if (currMax > maxSum) {
            maxSum = currMax;
        }
    }
    return maxSum;
}


int main() {
    constexpr int size = 6;
    Item arr[size] = {{4, 6}, {5, 7}, {7, 8}, {7, 7}, {8, 8}, {9, 9}};
    std::cout << longestSubSequence(arr, size);
    return 0;
}