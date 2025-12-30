#ifndef DYNAMIC_H
#define DYNAMIC_H

#include <vector>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <climits> // За INT_MAX

// Структура за предметите в Раницата
struct Item {
    int id;
    int weight;
    int value;
};

// --- ALGORITHMS ---

// 1. Fibonacci (Bottom-Up DP от слайд image_a59670.png)
void runFibonacciDP(int n);

// 2. Minimum Cost Path (Top-Down DP от слайд image_a5f7ab.png)
void runMinCostPath(const std::vector<std::vector<int>>& grid);

// 3. 0/1 Knapsack Problem (Sırt Çantası - Table Visualization)
// Базиран на логиката от image_a5fb48.png и примера от image_a5f869.png
void runKnapsackDP(int capacity, const std::vector<Item>& items);

#endif