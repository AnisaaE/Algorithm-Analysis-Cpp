#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm> // За sort
#include <iomanip>   // За setw
#include <random>    // За random
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

// Генератор на случайни числа
vector<int> generateRandomArray(int size, int minVal = 0, int maxVal = 10000) {
    vector<int> arr(size);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(minVal, maxVal);

    for (int i = 0; i < size; i++) arr[i] = dis(gen);
    return arr;
}

// --- УНИВЕРСАЛНА ФУНКЦИЯ ЗА ИЗБОР НА ДАННИ ---
vector<int> getDataFromUser() {
    int choice;
    int n;
    
    cout << "\n--- DATA SELECTION ---\n";
    cout << "1. Generate RANDOM Data (Auto)\n";
    cout << "2. Enter MANUAL Data (User Input)\n";
    cout << "Choice: ";
    cin >> choice;

    if (choice == 2) {
        // Ръчно въвеждане
        cout << "Enter number of elements: ";
        cin >> n;
        vector<int> arr(n);
        cout << "Enter " << n << " integers: ";
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }
        cout << "-> Custom data loaded.\n";
        return arr;
    } else {
        // Случайно (по подразбиране)
        cout << "Enter array size (Recommended: 1000 - 10000): ";
        cin >> n;
        // Генерираме случайни (0 до 10000)
        cout << "-> Generating random data...\n";
        return generateRandomArray(n, 0, 10000);
    }
}

// ==========================================
//      МОДУЛ 1: MAX SUBSEQUENCE PROBLEM
// ==========================================

void runMaxSubsequenceBenchmark() {
    cout << "\n=== MAX SUBSEQUENCE PERFORMANCE TEST ===\n";
    
    // Питаме потребителя за данни
    vector<int> data = getDataFromUser();
    int n = data.size();

    cout << "Running algorithms on " << n << " elements...\n";

    printSeparator();
    cout << left << setw(30) << "ALGORITHM" << setw(20) << "TIME (microseconds)" << endl;
    printSeparator();

    // 1. Brute Force O(n^3)
    if (n > 2000) cout << left << setw(30) << "1. Brute Force O(n^3)" << setw(20) << "SKIPPED (>2000)" << endl;
    else {
        auto start = high_resolution_clock::now();
        maxSubSum1(data);
        auto end = high_resolution_clock::now();
        cout << left << setw(30) << "1. Brute Force O(n^3)" 
             << setw(20) << duration_cast<microseconds>(end - start).count() << endl;
    }

    // 2. Improved Brute Force O(n^2)
    if (n > 20000) cout << left << setw(30) << "2. Improved O(n^2)" << setw(20) << "SKIPPED (>20000)" << endl;
    else {
        auto start = high_resolution_clock::now();
        maxSubSum2(data);
        auto end = high_resolution_clock::now();
        cout << left << setw(30) << "2. Improved O(n^2)" 
             << setw(20) << duration_cast<microseconds>(end - start).count() << endl;
    }

    // 3. Divide & Conquer O(n log n)
    auto start = high_resolution_clock::now();
    maxSubSum3(data);
    auto end = high_resolution_clock::now();
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

// ==========================================
//      МОДУЛ 2: RECURSIVE ALGORITHMS (FIXED)
// ==========================================
void runRecursiveTests() {
    int choice;
    do {
        cout << "\n========== RECURSIVE ALGORITHMS MENU ==========\n";
        cout << "1. Analysis Table (Compare all algorithms)\n"; 
        cout << "2. Visual Fibonacci (Three)\n";
        cout << "3. Test Sum (1..N)\n";
        cout << "4. Test Array Sum\n";
        cout << "5. Test Power (2^N)\n";
        cout << "6. Test Super Digit\n";
        cout << "7. Test Hanoi Towers\n";
        cout << "0. Back to Main Menu\n";
        cout << "Choice: ";
        cin >> choice;

        // Нулираме броячите преди всяко пускане
        recursionCounter = 0; 
        verboseMode = false;

        if (choice == 1) {
            // --- ТУК БЕШЕ ПРОБЛЕМЪТ. ЕТО ПЪЛНАТА ТАБЛИЦА СЕГА: ---
            int n; 
            cout << "Enter N for benchmark (e.g., 10 or 20): "; 
            cin >> n;

            cout << "\n" << left << setw(20) << "ALGORITHM" << setw(15) << "INPUT" << setw(15) << "RESULT" << setw(15) << "CALLS" << endl;
            printSeparator();
            
            // 1. Sum
            recursionCounter = 0; 
            int r1 = sumRecursive(n);
            cout << left << setw(20) << "Sum(1..N)" << setw(15) << n << setw(15) << r1 << setw(15) << recursionCounter << endl;

            // 2. Fibonacci (Внимаваме да не е твърде голямо)
            if(n <= 40) {
                recursionCounter = 0; 
                int r2 = fibonacciRecursive(n);
                cout << left << setw(20) << "Fibonacci" << setw(15) << n << setw(15) << r2 << setw(15) << recursionCounter << endl;
            } else {
                cout << left << setw(20) << "Fibonacci" << setw(15) << n << setw(15) << "SKIP (>40)" << setw(15) << "Too Many" << endl;
            }

            // 3. Power (2^N)
            recursionCounter = 0; 
            double r3 = powerRecursive(2.0, n);
            // Използваме scientific notation за големи числа, или просто double
            cout << left << setw(20) << "Power(2^N)" << setw(15) << n << setw(15) << r3 << setw(15) << recursionCounter << endl;

            // 4. Super Digit (Ще ползваме число, базирано на N, напр. N * 987, за да е интересно)
            int inputSD = n * 9876; 
            recursionCounter = 0; 
            int r4 = superDigitRecursive(inputSD);
            cout << left << setw(20) << "SuperDigit" << setw(15) << inputSD << setw(15) << r4 << setw(15) << recursionCounter << endl;

            printSeparator();
            cout << "NOTE: Hanoi Towers is excluded from table because it prints text.\n";

        } else if (choice == 2) {
            int n; cout << "Fib Number: "; cin >> n;
            verboseMode = true; fibonacciRecursive(n); verboseMode = false;

        } else if (choice == 3) {
            int n; cout << "Enter N: "; cin >> n;
            cout << "Sum = " << sumRecursive(n) << " (Calls: " << recursionCounter << ")\n";

        } else if (choice == 4) {
            int size; cout << "Array size: "; cin >> size;
            vector<int> arr(size); cout << "Elements: "; for(int i=0; i<size; i++) cin >> arr[i];
            cout << "Result = " << sumArrayRecursive(arr.data(), size) << " (Calls: " << recursionCounter << ")\n";

        } else if (choice == 5) {
            double a; int n; cout << "Base a: "; cin >> a; cout << "Exp n: "; cin >> n;
            cout << "Result = " << powerRecursive(a, n) << " (Calls: " << recursionCounter << ")\n";

        } else if (choice == 6) {
            int n; cout << "Number: "; cin >> n;
            cout << "Super Digit = " << superDigitRecursive(n) << " (Calls: " << recursionCounter << ")\n";

        } else if (choice == 7) {
            int disks; cout << "Disks: "; cin >> disks;
            towerOfHanoi(disks, 'L', 'R', 'M');
            cout << "Total Moves: " << recursionCounter << endl;
        }

    } while (choice != 0);
}
// ==========================================
//      МОДУЛ 3: SEARCHING ALGORITHMS
// ==========================================

// ==========================================
//      MODULE 3: SEARCHING (UPDATED)
// ==========================================
void runSearchingTests() {
    cout << "\n=== SEARCHING ALGORITHMS BENCHMARK ===\n";
    
    // 1. Get Data
    vector<int> data = getDataFromUser();
    int n = data.size();
    
    // 2. Sort Data (Mandatory for Binary Search)
    sort(data.begin(), data.end());
    cout << "-> Data sorted automatically (Required for Binary Search validity).\n";

    // 3. Choose Target (The new logic)
    int target;
    int searchMode;

    cout << "\n--- TARGET SELECTION ---\n";
    cout << "1. Auto-Select (Guarantees the number is found)\n";
    cout << "2. Manual Input (Enter your own number)\n";
    cout << "Choice: ";
    cin >> searchMode;

    if (searchMode == 2) {
        // MANUAL MODE WITH WARNING
        cout << "\n[WARNING]: If you enter a number that does not exist in the array,\n";
        cout << "           the result will be -1 (Not Found).\n";
        cout << "Enter value to search for: ";
        cin >> target;
    } else {
        // AUTO MODE
        target = data[n/2]; // Pick the middle element
        cout << "-> Auto-selected value: " << target << endl;
    }
    
    // 4. Run Algorithms
    printSeparator();
    cout << left << setw(25) << "ALGORITHM" << setw(20) << "TIME (us)" << setw(15) << "FOUND INDEX" << endl;
    printSeparator();

    // Linear Forward
    auto start = high_resolution_clock::now();
    int idx1 = linearSearchForward(data.data(), n, target);
    auto end = high_resolution_clock::now();
    cout << left << setw(25) << "Linear Forward" << setw(20) << duration_cast<microseconds>(end - start).count() << setw(15) << idx1 << endl;

    // Linear Backward
    start = high_resolution_clock::now();
    int idx2 = linearSearchBackward(data.data(), n, target);
    end = high_resolution_clock::now();
    cout << left << setw(25) << "Linear Backward" << setw(20) << duration_cast<microseconds>(end - start).count() << setw(15) << idx2 << endl;

    // Binary Search
    start = high_resolution_clock::now();
    int idx3 = binarySearchRecursive(data.data(), target, 0, n - 1);
    end = high_resolution_clock::now();
    cout << left << setw(25) << "Binary Search" << setw(20) << duration_cast<microseconds>(end - start).count() << setw(15) << idx3 << endl;
    
    printSeparator();
    if (idx1 == -1 && idx2 == -1 && idx3 == -1) {
        cout << "Result: The number " << target << " was NOT found in the array.\n";
    } else {
        cout << "Result: The number " << target << " was successfully found.\n";
    }
}
// ==========================================
//      МОДУЛ 4: SORTING ALGORITHMS
// ==========================================

void runSortingBenchmark() {
    cout << "\n========== SORTING ALGORITHMS BENCHMARK ==========\n";
    
    // Питаме потребителя за данни
    vector<int> masterData = getDataFromUser();
    int n = masterData.size();

    if (n > 20000) cout << "WARNING: N is large. O(n^2) algorithms might be very slow.\n";
    
    cout << "Starting race...\n";
    printSeparator();
    cout << left << setw(25) << "ALGORITHM" << setw(15) << "COMPLEXITY" << setw(20) << "TIME (microseconds)" << endl;
    printSeparator();

    // --- SLOW ALGORITHMS ---
    if (n <= 30000) { 
        vector<int> copy = masterData;
        auto start = high_resolution_clock::now();
        selectionSort(copy.data(), n);
        auto end = high_resolution_clock::now();
        cout << left << setw(25) << "Selection Sort" << setw(15) << "O(n^2)" << setw(20) << duration_cast<microseconds>(end - start).count() << endl;

        copy = masterData;
        start = high_resolution_clock::now();
        bubbleSort(copy.data(), n);
        end = high_resolution_clock::now();
        cout << left << setw(25) << "Bubble Sort" << setw(15) << "O(n^2)" << setw(20) << duration_cast<microseconds>(end - start).count() << endl;

        copy = masterData;
        start = high_resolution_clock::now();
        insertionSort(copy.data(), n);
        end = high_resolution_clock::now();
        cout << left << setw(25) << "Insertion Sort" << setw(15) << "O(n^2)" << setw(20) << duration_cast<microseconds>(end - start).count() << endl;
    } else {
         cout << "Skipping Slow Sorts (O(n^2)) because N > 30000.\n";
    }

    printSeparator();

    // --- FAST ALGORITHMS ---
    vector<int> copy = masterData;
    auto start = high_resolution_clock::now();
    mergeSort(copy.data(), n);
    auto end = high_resolution_clock::now();
    cout << left << setw(25) << "Merge Sort" << setw(15) << "O(n log n)" << setw(20) << duration_cast<microseconds>(end - start).count() << endl;

    copy = masterData;
    start = high_resolution_clock::now();
    quickSort(copy.data(), n);
    end = high_resolution_clock::now();
    cout << left << setw(25) << "Quick Sort" << setw(15) << "O(n log n)" << setw(20) << duration_cast<microseconds>(end - start).count() << endl;

    copy = masterData;
    start = high_resolution_clock::now();
    heapSort(copy.data(), n);
    end = high_resolution_clock::now();
    cout << left << setw(25) << "Heap Sort" << setw(15) << "O(n log n)" << setw(20) << duration_cast<microseconds>(end - start).count() << endl;

    printSeparator();

    // --- LINEAR ALGORITHMS ---
    bool hasNegative = false;
    for(int x : masterData) if(x < 0) hasNegative = true;

    if (!hasNegative) {
        copy = masterData;
        start = high_resolution_clock::now();
        countingSort(copy.data(), n);
        end = high_resolution_clock::now();
        cout << left << setw(25) << "Counting Sort" << setw(15) << "O(n+k)" << setw(20) << duration_cast<microseconds>(end - start).count() << endl;

        copy = masterData;
        start = high_resolution_clock::now();
        radixSort(copy.data(), n);
        end = high_resolution_clock::now();
        cout << left << setw(25) << "Radix Sort" << setw(15) << "O(d*(n+k))" << setw(20) << duration_cast<microseconds>(end - start).count() << endl;
    } else {
        cout << "Skipping Counting/Radix Sort (Data contains negative numbers).\n";
    }

    printSeparator();
}

// ==========================================
//      МОДУЛ 5: HEAP OPERATIONS
// ==========================================

void runHeapTests() {
    int choice;
    BinaryHeap h; 

    cout << "\n========== HEAP MANAGER (PRIORITY QUEUE) ==========\n";
    
    // Питаме потребителя още в началото дали иска да зареди данни
    cout << "Do you want to initialize the Heap now?\n";
    cout << "1. Yes (Random or Manual)\n2. No (Start Empty)\nChoice: ";
    int initChoice; cin >> initChoice;
    
    if (initChoice == 1) {
        vector<int> initData = getDataFromUser(); // Използваме общата функция
        h = BinaryHeap(initData);
        cout << "-> Heap initialized!\n";
        h.printHeap();
    }

    do {
        cout << "\n--- HEAP MENU ---\n";
        cout << "1. Insert\n2. Delete Min\n3. Re-Build Heap\n4. Decrease Key\n5. Merge Demo\n0. Back\nChoice: ";
        cin >> choice;

        if (choice == 1) {
            int val; cout << "Value: "; cin >> val; h.insert(val); h.printHeap();
        } else if (choice == 2) {
            if(!h.isEmpty()) { cout << "Deleted: " << h.deleteMinReturn() << endl; h.printHeap(); }
            else cout << "Heap is empty.\n";
        } else if (choice == 3) {
            vector<int> newData = getDataFromUser();
            h = BinaryHeap(newData);
            h.printHeap();
        } else if (choice == 4) {
            int i, d; cout << "Index & Delta: "; cin >> i >> d; h.decreaseKey(i, d); h.printHeap();
        } else if (choice == 5) {
            BinaryHeap h2({10, 20, 30}); 
            cout << "Merging with {10, 20, 30}...\n";
            h = mergeHeaps(h, h2); 
            h.printHeap();
        }
    } while (choice != 0);
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
        cout << "1. Max Subsequence Sum (Benchmarks)\n";
        cout << "2. Recursive Algorithms\n";
        cout << "3. Searching Algorithms\n";
        cout << "4. Sorting Algorithms (Benchmarks)\n";
        cout << "5. Heap Operations\n";
        cout << "0. Exit\n";
        cout << "Select module: ";
        cin >> choice;

        switch (choice) {
            case 1: runMaxSubsequenceBenchmark(); break;
            case 2: runRecursiveTests(); break;
            case 3: runSearchingTests(); break;
            case 4: runSortingBenchmark(); break;
            case 5: runHeapTests(); break;
            case 0: cout << "Goodbye!\n"; break;
            default: cout << "Invalid.\n";
        }
    } while (choice != 0);
    return 0;
}