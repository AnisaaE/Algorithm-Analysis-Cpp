#include "../include/max_subsequence.h"
#include <vector>
#include <algorithm> 

using namespace std;

// Helper for Divide & Conquer
// Finds maximum sum passing through the center
int maxSubSumRec(const vector<int>& a, int left, int right) {
    if (left == right) { // Base case
        return (a[left] > 0) ? a[left] : 0;
    }

    int center = (left + right) / 2;
    int maxLeftSum = maxSubSumRec(a, left, center);
    int maxRightSum = maxSubSumRec(a, center + 1, right);

    // Calculate max sum to the left of center
    int maxLeftBorderSum = 0, leftBorderSum = 0;
    for (int i = center; i >= left; --i) {
        leftBorderSum += a[i];
        if (leftBorderSum > maxLeftBorderSum)
            maxLeftBorderSum = leftBorderSum;
    }

    // Calculate max sum to the right of center
    int maxRightBorderSum = 0, rightBorderSum = 0;
    for (int i = center + 1; i <= right; ++i) {
        rightBorderSum += a[i];
        if (rightBorderSum > maxRightBorderSum)
            maxRightBorderSum = rightBorderSum;
    }

    // Return the maximum of the three
    return max({maxLeftSum, maxRightSum, maxLeftBorderSum + maxRightBorderSum});
}

// 1. Brute Force O(n^3)
int maxSubSum1(const vector<int>& a) {
    int maxSum = 0;
    for (int i = 0; i < a.size(); i++) {
        for (int j = i; j < a.size(); j++) {
            int thisSum = 0;
            for (int k = i; k <= j; k++) {
                thisSum += a[k];
            }
            if (thisSum > maxSum)
                maxSum = thisSum;
        }
    }
    return maxSum;
}

// 2. Improved Brute Force O(n^2)
int maxSubSum2(const vector<int>& a) {
    int maxSum = 0;
    for (int i = 0; i < a.size(); i++) {
        int thisSum = 0;
        for (int j = i; j < a.size(); j++) {
            thisSum += a[j];
            if (thisSum > maxSum)
                maxSum = thisSum;
        }
    }
    return maxSum;
}

// 3. Divide and Conquer O(n log n) wrapper
int maxSubSum3(const vector<int>& a) {
    return maxSubSumRec(a, 0, a.size() - 1);
}

// 4. Kadane's Algorithm O(n)
int maxSubSum4(const vector<int>& a) {
    int maxSum = 0, thisSum = 0;
    for (int j = 0; j < a.size(); j++) {
        thisSum += a[j];
        if (thisSum > maxSum)
            maxSum = thisSum;
        else if (thisSum < 0)
            thisSum = 0;
    }
    return maxSum;
}