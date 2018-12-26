
#include <iostream> 
#include <algorithm>

//Returns the magic index for a sorted distinct numbers, where A[i]=i
//If no such index is found - return -1
int magicIndexDistinctSortedArray(int* arr, int begin, int end, int size) {
    if (end < begin || end >= size || begin < 0) {
        return -1;
    }
    int middle = (begin + end) / 2;
    if (arr[middle] == middle) {
        return middle;
    }
    if (arr[middle] > middle) {
        return magicIndexDistinctSortedArray(arr, begin, middle - 1, size);
    } else {
        return magicIndexDistinctSortedArray(arr, middle + 1, end, size);
    }
    return 1;
}


//Returns the magic index for a sorted non-distinct numbers, where A[i]=i
//If no such index is found - return -1
int magicIndexNonDistinctSortedArray(int* arr, int begin, int end, int size) {
    if (end < begin || end >= size || begin < 0) {
        return -1;
    }
    int middle = (begin + end) / 2;
    if (arr[middle] == middle) {
        return middle;
    }
    if (arr[middle] > middle) {
        int left = magicIndexNonDistinctSortedArray(arr, begin, middle - 1, size);
        if (left != -1) {
            return left;
        }
        //Search in the right side as well, but can skip some of the values - Since arr[middle] isn't a magicIndex,
        //then arr[arr[middle]] can be the next candiate!
        int right = magicIndexNonDistinctSortedArray(arr, std::max(middle + 1, arr[middle]), end, size);
        return right;
    } else {
        int right = magicIndexNonDistinctSortedArray(arr, middle + 1, end, size);
        if (right != -1) {
            return right;
        }
        int left = magicIndexNonDistinctSortedArray(arr, begin, std::min(middle - 1, arr[middle]), size);
        return left;
    }
    return 1;
}

int main() {
    int size = 10;
    int* arr = new int[size] {-10, -5, 1, 6, 6, 6, 6, 8, 9, 10};
    
    std::cout << magicIndexNonDistinctSortedArray(arr, 0, size-1, size);
    return 0;
}
