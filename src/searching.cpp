#include "searching.h"

// 1. Forward Linear Search (Recursive)
int linearSearchForward(const int* A, int n, int key) {
    if (n == 0) {
        return -1;
    }
    if (A[0] == key) {
        return 0; // index relative to current pointer
    }
        int res = linearSearchForward(A + 1, n - 1, key);
    
    // If found in the sub-array, add 1 to correct the index
    if (res != -1) {
        return 1 + res;
    }
    
    return -1;
}

// 2. Backward Linear Search (Recursive)
int linearSearchBackward(const int* A, int n, int key) {
    if (n == 0) {
        return -1; 
    }
    
    if (key == A[n - 1]) {
        return n - 1; 
    }

    return linearSearchBackward(A, n - 1, key);
}

// 3. Binary Search (Recursive)
int binarySearchRecursive(const int* A, int key, int left, int right) {
    // Base case: No elements left
    if (left > right) {
        return -1;
    }

    int middle = (left + right) / 2;

    if (key == A[middle]) {
        return middle;
    }

    // Conquer & Merge
    // note: The code in the slide uses "if (key < A[left])". 
    // Correct logic is "if (key < A[middle])".
    if (key < A[middle]) {
        return binarySearchRecursive(A, key, left, middle - 1);
    } else {
        return binarySearchRecursive(A, key, middle + 1, right);
    }
}