#ifndef MAX_SUBSEQUENCE_H
#define MAX_SUBSEQUENCE_H

#include <vector>

// 1. Brute Force O(n^3)
int maxSubSum1(const std::vector<int>& a);

// 2. Improved Brute Force O(n^2)
int maxSubSum2(const std::vector<int>& a);

// 3. Divide and Conquer O(n log n)
int maxSubSum3(const std::vector<int>& a);

// 4. Kadane's Algorithm O(n)
int maxSubSum4(const std::vector<int>& a);

#endif