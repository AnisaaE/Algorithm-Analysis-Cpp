# 🚀 Algorithm Analysis & Complexity Project

This project is a comprehensive C++ suite designed to demonstrate, benchmark, and visualize fundamental algorithms and data structures. It covers a wide range of topics from **Algorithm Analysis** courses, including Sorting, Searching, Recursion, Heaps, Greedy Algorithms, and Dynamic Programming.

The application features a console-based interactive menu that allows users to generate random datasets, run benchmarks, and visualize algorithmic steps (e.g., DP tables, Recursion depth).

---

## 📋 Table of Contents

1. [Features & Modules](#-features--modules)
2. [Project Structure](#-project-structure)
3. [Installation & Compilation](#-installation--compilation)
4. [Usage](#-usage)
5. [Algorithm Details](#-algorithm-details)
6. [Requirements](#-requirements)

---

## 🚀 How to Run (Quick Start)

To compile and run the program, open your terminal (PowerShell or Command Prompt) in the project folder and paste the following command:

**Windows (PowerShell):**
```powershell
g++ src/*.cpp -I include -o main; .\main

## ✨ Features & Modules

The project is divided into **7 core modules**, each focusing on a specific paradigm or data structure.

### 1. Max Subsequence Sum (Benchmarking)
Comparison of four different algorithms solving the "Maximum Subsequence Sum" problem to demonstrate time complexity differences:
- **Brute Force:** $O(n^3)$ - *Cubic complexity (very slow).*
- **Improved Brute Force:** $O(n^2)$ - *Quadratic complexity.*
- **Divide & Conquer:** $O(n \log n)$ - *Recursive approach.*
- **Kadane's Algorithm:** $O(n)$ - *Linear time (Optimal).*
> **Feature:** Automatic large-dataset protection skips $O(n^3)$ tests for $N > 2000$.

### 2. Recursive Algorithms
Demonstration of recursion depth, call counting, and stack visualization:
- **Fibonacci:** Visual recursive tree trace.
- **Sum (1..N) & Array Sum.**
- **Power Function ($x^n$).**
- **Super Digit:** Recursive digit summation.
- **Tower of Hanoi:** Step-by-step move visualization.

### 3. Searching Algorithms
Performance comparison between linear and logarithmic searching:
- **Linear Search (Forward & Backward):** $O(n)$.
- **Binary Search (Recursive):** $O(\log n)$.
> **Feature:** Includes "Auto-Select" mode to guarantee a successful search hit for valid benchmarking.

### 4. Sorting Algorithms
A race between 8 sorting algorithms across three complexity classes:
- **Slow Sorts ($O(n^2)$):** Selection Sort, Bubble Sort, Insertion Sort.
- **Fast Sorts ($O(n \log n)$):** Merge Sort, Quick Sort, Heap Sort.
- **Linear Sorts ($O(n + k)$):** Counting Sort, Radix Sort.

### 5. Heap Data Structure
A complete **Binary Min-Heap** (Priority Queue) implementation:
- **Operations:** Insert, Delete Min, Decrease Key, Build Heap.
- **Visualization:** Printing the heap structure to the console.
- **Merging:** Algorithm to merge two heaps.

### 6. Greedy Algorithms
Implementation of classic optimization problems:
- **Job Scheduling:** Shortest Job First (SJF) strategy to minimize mean waiting time.
- **Activity Selection:** Selecting the maximum number of non-overlapping events.
- **Huffman Coding:** Full implementation of **Encoding** (Text $\to$ Bits) and **Decoding** (Bits $\to$ Text) using a frequency tree.

### 7. Dynamic Programming
Visualizing the "tables" used in DP to optimize recursive problems:
- **Fibonacci (Bottom-Up):** Displays the 1D memoization array.
- **Minimum Cost Path:** Visualizes the cost grid and the accumulated path matrix.
- **0/1 Knapsack Problem:** Displays the full DP table (Items vs. Capacity) to find the optimal value.

---

## 📂 Project Structure

The project separates source code (`src`) from header declarations (`include`) for clean architecture.

```text
AlgorithmProject/
├── include/              # Header files (.h)
│   ├── max_subsequence.h
│   ├── recursive.h
│   ├── searching.h
│   ├── sorting.h
│   ├── heap.h
│   ├── greedy.h
│   └── dynamic.h
├── src/                  # Source files (.cpp)
│   ├── main.cpp          # Entry point and Menu system
│   ├── max_subsequence.cpp
│   ├── recursive.cpp
│   ├── searching.cpp
│   ├── sorting.cpp
│   ├── heap.cpp
│   ├── greedy.cpp
│   └── dynamic.cpp
├── README.md             # Project Documentation
└── main.exe              # Compiled Executable