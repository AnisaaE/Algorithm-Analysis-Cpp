#ifndef SEARCHING_H
#define SEARCHING_H

#include <vector>

// 1. Linear Search (Forward) - Recursive
// Logic based on image_7d27ad.png
int linearSearchForward(const int* A, int n, int key);

// 2. Linear Search (Backward) - Recursive
// Source: image_7d26b5.jpg
int linearSearchBackward(const int* A, int n, int key);

// 3. Binary Search - Recursive (Requires Sorted Array)
// Source: image_7d2aeb.jpg
int binarySearchRecursive(const int* A, int key, int left, int right);

#endif