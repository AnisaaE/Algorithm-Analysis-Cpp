#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm> // За sort (за подготовка на данни)
#include <iomanip>   // За подравняване на таблиците (setw)
#include <random>    // За генериране на случайни числа
#include "max_subsequence.h"
#include "recursive.h"
#include "searching.h"
#include "sorting.h"
#include "heap.h"

using namespace std;
using namespace std::chrono;

// ==========================================
//            ПОМОЩНИ ФУНКЦИИ
// ==========================================

void printSeparator() {
    cout << "----------------------------------------------------------------\n";
}

// Функция за генериране на произволен масив
// minVal/maxVal са важни за Counting Sort, който не работи с отрицателни числа
vector<int> generateRandomArray(int size, int minVal = 0, int maxVal = 10000) {
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
//      МОДУЛ 1: MAX SUBSEQUENCE PROBLEM
// ==========================================

void runMaxSubsequenceBenchmark() {
    int n;
    cout << "\n=== MAX SUBSEQUENCE PERFORMANCE TEST ===\n";
    cout << "Enter array size (Recommended: 1000 - 5000): ";
    cin >> n;

    // Генерираме масив с отрицателни и положителни числа
    vector<int> data = generateRandomArray(n, -100, 100);
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
//      МОДУЛ 2: RECURSIVE ALGORITHMS
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
            towerOfHanoi(3, 'A', 'C', 'B'); 
            cout << left << setw(25) << "Hanoi Towers" << setw(15) << "3 Disks" 
                 << setw(15) << "-" << setw(15) << recursionCounter << endl;

            printSeparator();

        } else if (choice == 2) {
            int n;
            cout << "\nEnter Fibonacci number (Recommended 4 or 5): ";
            cin >> n;

            cout << "\n--- RECURSION TREE VISUALIZATION ---\n";
            verboseMode = true; 
            recursionCounter = 0; maxDepth = 0; currentDepth = 0;

            int res = fibonacciRecursive(n);

            verboseMode = false;
            printSeparator();
            cout << "Result: " << res << endl;
            cout << "Total Recursive Calls: " << recursionCounter << endl;
            cout << "Max Stack Depth: " << maxDepth << endl;
            printSeparator();
        }

    } while (choice != 0);
}

// ==========================================
//      МОДУЛ 3: SEARCHING ALGORITHMS
// ==========================================

void runSearchingTests() {
    cout << "\n========== SEARCHING ALGORITHMS BENCHMARK ==========\n";
    int n;
    cout << "Enter array size (Recommended: 10000 or 100000): ";
    cin >> n;

    // Генерираме сортиран масив (Задължително за Binary Search)
    vector<int> data = generateRandomArray(n, 0, n * 2);
    sort(data.begin(), data.end()); 
    
    int targetFound = data[n / 2]; // Елемент, който съществува
    
    cout << "Array generated and SORTED. Size: " << n << endl;
    
    printSeparator();
    cout << left << setw(25) << "ALGORITHM" << setw(20) << "TIME (microseconds)" << setw(10) << "INDEX" << endl;
    printSeparator();

    // 1. Linear Forward
    auto start = high_resolution_clock::now();
    int idx1 = linearSearchForward(data.data(), n, targetFound);
    auto end = high_resolution_clock::now();
    cout << left << setw(25) << "Linear Forward O(n)" 
         << setw(20) << duration_cast<microseconds>(end - start).count() 
         << setw(10) << idx1 << endl;

    // 2. Linear Backward
    start = high_resolution_clock::now();
    int idx2 = linearSearchBackward(data.data(), n, targetFound);
    end = high_resolution_clock::now();
    cout << left << setw(25) << "Linear Backward O(n)" 
         << setw(20) << duration_cast<microseconds>(end - start).count() 
         << setw(10) << idx2 << endl;

    // 3. Binary Search
    start = high_resolution_clock::now();
    int idx3 = binarySearchRecursive(data.data(), targetFound, 0, n - 1);
    end = high_resolution_clock::now();
    cout << left << setw(25) << "Binary Search O(log n)" 
         << setw(20) << duration_cast<microseconds>(end - start).count() 
         << setw(10) << idx3 << endl;
    
    printSeparator();
}

// ==========================================
//      МОДУЛ 4: SORTING ALGORITHMS
// ==========================================

void runSortingBenchmark() {
    int n;
    cout << "\n========== SORTING ALGORITHMS BENCHMARK ==========\n";
    cout << "WARNING: O(n^2) algorithms are slow. N > 20000 might take time.\n";
    cout << "Enter array size (Recommended: 5000 - 10000): ";
    cin >> n;

    // Важно: Counting и Radix изискват положителни числа!
    // Генерираме "Master" копие, за да подаваме еднакви данни на всички
    vector<int> masterData = generateRandomArray(n, 0, 10000);
    
    cout << "Data generated. Starting race...\n";
    printSeparator();
    cout << left << setw(25) << "ALGORITHM" << setw(15) << "COMPLEXITY" << setw(20) << "TIME (milliseconds)" << endl;
    printSeparator();

    // --- SLOW ALGORITHMS ---
    vector<int> copy = masterData;
    auto start = high_resolution_clock::now();
    selectionSort(copy.data(), n);
    auto end = high_resolution_clock::now();
    double t = duration_cast<milliseconds>(end - start).count();
    cout << left << setw(25) << "Selection Sort" << setw(15) << "O(n^2)" << setw(20) << t << endl;

    copy = masterData;
    start = high_resolution_clock::now();
    bubbleSort(copy.data(), n);
    end = high_resolution_clock::now();
    t = duration_cast<milliseconds>(end - start).count();
    cout << left << setw(25) << "Bubble Sort" << setw(15) << "O(n^2)" << setw(20) << t << endl;

    copy = masterData;
    start = high_resolution_clock::now();
    insertionSort(copy.data(), n);
    end = high_resolution_clock::now();
    t = duration_cast<milliseconds>(end - start).count();
    cout << left << setw(25) << "Insertion Sort" << setw(15) << "O(n^2)" << setw(20) << t << endl;

    printSeparator();

    // --- FAST ALGORITHMS ---
    copy = masterData;
    start = high_resolution_clock::now();
    mergeSort(copy.data(), n);
    end = high_resolution_clock::now();
    t = duration_cast<milliseconds>(end - start).count();
    cout << left << setw(25) << "Merge Sort" << setw(15) << "O(n log n)" << setw(20) << t << endl;

    copy = masterData;
    start = high_resolution_clock::now();
    quickSort(copy.data(), n);
    end = high_resolution_clock::now();
    t = duration_cast<milliseconds>(end - start).count();
    cout << left << setw(25) << "Quick Sort" << setw(15) << "O(n log n)" << setw(20) << t << endl;

    copy = masterData;
    start = high_resolution_clock::now();
    heapSort(copy.data(), n);
    end = high_resolution_clock::now();
    t = duration_cast<milliseconds>(end - start).count();
    cout << left << setw(25) << "Heap Sort" << setw(15) << "O(n log n)" << setw(20) << t << endl;

    printSeparator();

    // --- LINEAR ALGORITHMS ---
    copy = masterData;
    start = high_resolution_clock::now();
    countingSort(copy.data(), n);
    end = high_resolution_clock::now();
    t = duration_cast<milliseconds>(end - start).count();
    cout << left << setw(25) << "Counting Sort" << setw(15) << "O(n+k)" << setw(20) << t << endl;

    copy = masterData;
    start = high_resolution_clock::now();
    radixSort(copy.data(), n);
    end = high_resolution_clock::now();
    t = duration_cast<milliseconds>(end - start).count();
    cout << left << setw(25) << "Radix Sort" << setw(15) << "O(d*(n+k))" << setw(20) << t << endl;

    printSeparator();
}

// ==========================================
//      MODULE 5: HEAP OPERATIONS (NEW)
// ==========================================
void runHeapTests() {
    cout << "\n========== HEAP (PRIORITY QUEUE) DEMO ==========\n";
    
    // 1. Build Heap
    vector<int> input = {10, 4, 5, 30, 3, 1};
    cout << "Input Array: {10, 4, 5, 30, 3, 1}\n";
    
    BinaryHeap h(input); // Uses BuildHeap O(N)
    cout << "Built Min-Heap: "; 
    h.printHeap(); // Should be: 1 3 5 30 4 10 (or similar valid heap)

    // 2. Insert
    cout << "\n[Insert 0]...\n";
    h.insert(0);
    h.printHeap();

    // 3. DeleteMin
    cout << "\n[DeleteMin] -> Removed: " << h.deleteMinReturn() << endl;
    h.printHeap();

    // 4. Decrease Key
    cout << "\n[DecreaseKey] Index 3 by 10...\n";
    h.decreaseKey(3, 10);
    h.printHeap();

    // 5. Merge
    cout << "\n[Merge Heaps]\n";
    BinaryHeap h2({50, 100, 20});
    cout << "Heap 2: "; h2.printHeap();
    
    cout << "Merging H1 and H2...\n";
    BinaryHeap merged = mergeHeaps(h, h2);
    merged.printHeap();

    printSeparator();
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
        cout << "1. Maximum Subsequence Sum\n";
        cout << "2. Recursive Algorithms\n";
        cout << "3. Searching Algorithms\n";
        cout << "4. Sorting Algorithms\n";
        cout << "5. Heap Operations (Binary Heap)\n";
        cout << "0. Exit\n";
        cout << "Select module: ";
        cin >> choice;

        switch (choice) {
            case 1: runMaxSubsequenceBenchmark(); break;
            case 2: runRecursiveTests(); break;
            case 3: runSearchingTests(); break;
            case 4: runSortingBenchmark(); break;
            case 5: runHeapTests(); break; // NEW
            case 0: cout << "Goodbye!\n"; break;
            default: cout << "Invalid.\n";
        }

    } while (choice != 0);

    return 0;
}