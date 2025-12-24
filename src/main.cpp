#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm> // For sort
#include <iomanip>   // For beautiful tables (setw)
#include <random>    // For random number generation
#include "max_subsequence.h"
#include "recursive.h"
#include "searching.h"

using namespace std;
using namespace std::chrono;

// ==========================================
//               UTILITY FUNCTIONS
// ==========================================

void printSeparator() {
    cout << "----------------------------------------------------------------\n";
}

// Helper to print array elements
void printArray(const vector<int>& arr) {
    if (arr.size() > 20) {
        cout << "[Array is too big to print completely]" << endl;
        return;
    }
    cout << "[ ";
    for (int x : arr) cout << x << " ";
    cout << "]" << endl;
}

// Helper to generate random array
vector<int> generateRandomArray(int size, int minVal = -100, int maxVal = 100) {
    vector<int> arr(size);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(minVal, maxVal);

    for (int i = 0; i < size; i++) {
        arr[i] = dis(gen);
    }
    return arr;
}

// ==========================================
//      MODULE 1: MAX SUBSEQUENCE PROBLEM
// ==========================================

void runMaxSubsequenceBenchmark() {
    int n;
    cout << "\n=== MAX SUBSEQUENCE PERFORMANCE TEST ===\n";
    cout << "Enter array size (Recommended: 1000 - 5000): ";
    cin >> n;

    // Generate data
    vector<int> data = generateRandomArray(n);
    cout << "Generated random array of size " << n << ".\nRunning algorithms...\n";

    printSeparator();
    cout << left << setw(30) << "ALGORITHM" << setw(20) << "TIME (microseconds)" << endl;
    printSeparator();

    // 1. Brute Force O(n^3)
    auto start = high_resolution_clock::now();
    maxSubSum1(data);
    auto end = high_resolution_clock::now();
    cout << left << setw(30) << "1. Brute Force O(n^3)" 
         << setw(20) << duration_cast<microseconds>(end - start).count() << endl;

    // 2. Improved Brute Force O(n^2)
    start = high_resolution_clock::now();
    maxSubSum2(data);
    end = high_resolution_clock::now();
    cout << left << setw(30) << "2. Improved O(n^2)" 
         << setw(20) << duration_cast<microseconds>(end - start).count() << endl;

    // 3. Divide & Conquer O(n log n)
    start = high_resolution_clock::now();
    maxSubSum3(data);
    end = high_resolution_clock::now();
    cout << left << setw(30) << "3. Divide & Conquer O(nlogn)" 
         << setw(20) << duration_cast<microseconds>(end - start).count() << endl;

    // 4. Kadane O(n)
    start = high_resolution_clock::now();
    maxSubSum4(data);
    end = high_resolution_clock::now();
    cout << left << setw(30) << "4. Kadane Algorithm O(n)" 
         << setw(20) << duration_cast<microseconds>(end - start).count() << endl;
    
    printSeparator();
}

// ==========================================
//      MODULE 2: RECURSIVE ALGORITHMS
// ==========================================

void runRecursiveTests() {
    int choice;
    do {
        cout << "\n========== RECURSIVE ALGORITHMS MENU ==========\n";
        cout << "1. Run Analysis Table (Calls & Results)\n";
        cout << "2. Visual Fibonacci (Recursion Tree - WOW Effect)\n";
        cout << "0. Back to Main Menu\n";
        cout << "Choice: ";
        cin >> choice;

        if (choice == 1) {
            // Reset visualization mode
            verboseMode = false;
            
            cout << "\n" << left << setw(25) << "ALGORITHM" 
                 << setw(15) << "INPUT"
                 << setw(15) << "RESULT" 
                 << setw(15) << "CALLS" << endl;
            printSeparator();

            // 1. Sum
            recursionCounter = 0;
            int r1 = sumRecursive(20);
            cout << left << setw(25) << "Sum(1..N)" << setw(15) << "N=20" 
                 << setw(15) << r1 << setw(15) << recursionCounter << endl;

            // 2. Array Sum
            int arrData[] = {1, 5, 10, 20, 50};
            recursionCounter = 0;
            int r2 = sumArrayRecursive(arrData, 5);
            cout << left << setw(25) << "Array Sum" << setw(15) << "Size=5" 
                 << setw(15) << r2 << setw(15) << recursionCounter << endl;

            // 3. Power
            recursionCounter = 0;
            double r3 = powerRecursive(2.0, 10);
            cout << left << setw(25) << "Power(a^n)" << setw(15) << "2^10" 
                 << setw(15) << r3 << setw(15) << recursionCounter << endl;

            // 4. Fibonacci
            recursionCounter = 0;
            int r4 = fibonacciRecursive(10);
            cout << left << setw(25) << "Fibonacci" << setw(15) << "N=10" 
                 << setw(15) << r4 << setw(15) << recursionCounter << endl;
                 
            // 5. Super Digit
            recursionCounter = 0;
            int r5 = superDigitRecursive(9875);
            cout << left << setw(25) << "Super Digit" << setw(15) << "9875" 
                 << setw(15) << r5 << setw(15) << recursionCounter << endl;

            // 6. Hanoi
            recursionCounter = 0;
            // Capture output to avoid spamming table, run separately to count
            towerOfHanoi(3, 'A', 'C', 'B'); 
            cout << left << setw(25) << "Hanoi Towers" << setw(15) << "3 Disks" 
                 << setw(15) << "-" << setw(15) << recursionCounter << endl;

            printSeparator();

        } else if (choice == 2) {
            int n;
            cout << "\nEnter Fibonacci number (Recommended 4 or 5): ";
            cin >> n;

            cout << "\n--- RECURSION TREE VISUALIZATION ---\n";
            verboseMode = true; // ENABLE VISUALIZATION
            recursionCounter = 0;
            maxDepth = 0;
            currentDepth = 0;

            int res = fibonacciRecursive(n);

            verboseMode = false; // DISABLE AFTER RUN
            printSeparator();
            cout << "Result: " << res << endl;
            cout << "Total Recursive Calls: " << recursionCounter << endl;
            cout << "Max Stack Depth: " << maxDepth << endl;
            printSeparator();
        }

    } while (choice != 0);
}

// ==========================================
//      MODULE 3: SEARCHING ALGORITHMS
// ==========================================

void runSearchingTests() {
    cout << "\n========== SEARCHING ALGORITHMS BENCHMARK ==========\n";
    int n;
    cout << "Enter array size (Recommended: 10000 or 100000): ";
    cin >> n;

    // 1. Generate SORTED array (Critical for Binary Search)
    vector<int> data = generateRandomArray(n, 0, n * 2);
    sort(data.begin(), data.end()); 
    
    // Define targets
    int targetFound = data[n / 2]; // Element in the middle
    int targetMissing = -500;      // Element that doesn't exist

    cout << "Array generated and SORTED. Size: " << n << endl;
    cout << "Searching for value: " << targetFound << endl;
    
    printSeparator();
    cout << left << setw(25) << "ALGORITHM" << setw(20) << "TIME (microseconds)" << setw(10) << "INDEX" << endl;
    printSeparator();

    // Test 1: Linear Search Forward
    auto start = high_resolution_clock::now();
    int idx1 = linearSearchForward(data.data(), n, targetFound);
    auto end = high_resolution_clock::now();
    cout << left << setw(25) << "Linear Forward O(n)" 
         << setw(20) << duration_cast<microseconds>(end - start).count() 
         << setw(10) << idx1 << endl;

    // Test 2: Linear Search Backward
    start = high_resolution_clock::now();
    int idx2 = linearSearchBackward(data.data(), n, targetFound);
    end = high_resolution_clock::now();
    cout << left << setw(25) << "Linear Backward O(n)" 
         << setw(20) << duration_cast<microseconds>(end - start).count() 
         << setw(10) << idx2 << endl;

    // Test 3: Binary Search
    start = high_resolution_clock::now();
    int idx3 = binarySearchRecursive(data.data(), targetFound, 0, n - 1);
    end = high_resolution_clock::now();
    cout << left << setw(25) << "Binary Search O(log n)" 
         << setw(20) << duration_cast<microseconds>(end - start).count() 
         << setw(10) << idx3 << endl;

    printSeparator();
    cout << "Observation: Binary Search should be significantly faster for large N.\n";
}

// ==========================================
//              MAIN FUNCTION
// ==========================================

int main() {
    int choice;
    do {
        cout << "\n#################################################\n";
        cout << "      ALGORITHM ANALYSIS PROJECT - MAIN MENU\n";
        cout << "#################################################\n";
        cout << "1. Maximum Subsequence Sum (O(n^3) vs O(n))\n";
        cout << "2. Recursive Algorithms (Analysis & Visualization)\n";
        cout << "3. Searching Algorithms (Linear vs Binary)\n";
        cout << "4. Sorting Algorithms (Coming Soon...)\n";
        cout << "0. Exit\n";
        cout << "#################################################\n";
        cout << "Select module: ";
        cin >> choice;

        switch (choice) {
            case 1: runMaxSubsequenceBenchmark(); break;
            case 2: runRecursiveTests(); break;
            case 3: runSearchingTests(); break;
            case 4: cout << "Sorting module is next!\n"; break;
            case 0: cout << "Exiting program. Goodbye!\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 0);

    return 0;
}