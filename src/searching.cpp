#include "searching.h"

// 1. Forward Linear Search (Recursive)
// Logic: Checks first element, then recurses on the rest.
// Based on: image_7d27ad.png
int linearSearchForward(const int* A, int n, int key) {
    // Base case 1: Array is empty (not found)
    if (n == 0) {
        return -1;
    }
    // Base case 2: Found at the current first position
    if (A[0] == key) {
        return 0; // Index relative to current pointer
    }
    
    // Recursive step: Search in the rest of the array (A+1)
    int res = linearSearchForward(A + 1, n - 1, key);
    
    // If found in the sub-array, add 1 to correct the index
    if (res != -1) {
        return 1 + res;
    }
    
    return -1; // Not found
}

// 2. Backward Linear Search (Recursive)
// Logic: Checks last element, then recurses on the prefix.
// Source: image_7d26b5.jpg
int linearSearchBackward(const int* A, int n, int key) {
    // Base case: Array is empty
    if (n == 0) {
        return -1; 
    }
    
    // Check the last element (N-1)
    if (key == A[n - 1]) {
        return n - 1; // Success
    }

    // Recursive step: Search in the smaller array
    return linearSearchBackward(A, n - 1, key);
}

// 3. Binary Search (Recursive)
// Source: image_7d2aeb.jpg
int binarySearchRecursive(const int* A, int key, int left, int right) {
    // Base case: No elements left
    if (left > right) {
        return -1;
    }

    // Calculate middle
    int middle = (left + right) / 2;

    // Check match
    if (key == A[middle]) {
        return middle;
    }

    // Conquer & Merge
    // NOTE: The slide had a typo "if (key < A[left])". 
    // Correct logic is "if (key < A[middle])".
    if (key < A[middle]) {
        return binarySearchRecursive(A, key, left, middle - 1);
    } else {
        return binarySearchRecursive(A, key, middle + 1, right);
    }
}