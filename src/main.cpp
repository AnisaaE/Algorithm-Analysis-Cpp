#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip> // За красиво подравняване (setw)
#include <random>
#include "max_subsequence.h"
#include "recursive.h"

using namespace std;
using namespace std::chrono;

// --- UTILS ---
void printSeparator() {
    cout << "--------------------------------------------------------\n";
}

// ... (functions printArray and generateRandomArray remain the same) ...
void printArray(const vector<int>& arr) { /* same as before */ }
vector<int> generateRandomArray(int size) { 
    vector<int> arr(size);
    random_device rd; mt19937 gen(rd()); uniform_int_distribution<> dis(-100, 100);
    for(int i=0; i<size; i++) arr[i] = dis(gen);
    return arr;
}
void runMaxSubsequenceBenchmark() { /* same as before */ }


// --- NEW & IMPROVED RECURSIVE MENU ---
void runRecursiveTests() {
    int choice;
    do {
        cout << "\n========== RECURSIVE ALGORITHMS ==========\n";
        cout << "1. Run All Analysis (Default inputs)\n";
        cout << "2. Visual Fibonacci (Tree View) - WOW Effect!\n";
        cout << "0. Back to Main Menu\n";
        cout << "Choice: ";
        cin >> choice;

        if (choice == 1) {
            // Reset globals
            verboseMode = false;
            
            cout << "\n" << left << setw(25) << "ALGORITHM" 
                 << setw(15) << "RESULT" 
                 << setw(15) << "CALLS" << endl;
            printSeparator();

            // 1. Sum
            recursionCounter = 0;
            int r1 = sumRecursive(20);
            cout << left << setw(25) << "Sum(1..20)" 
                 << setw(15) << r1 
                 << setw(15) << recursionCounter << endl;

            // 2. Power
            recursionCounter = 0;
            double r2 = powerRecursive(2.0, 10);
            cout << left << setw(25) << "Power(2^10)" 
                 << setw(15) << r2 
                 << setw(15) << recursionCounter << endl;

            // 3. Fibonacci
            recursionCounter = 0; maxDepth = 0; currentDepth = 0;
            int r3 = fibonacciRecursive(10);
            cout << left << setw(25) << "Fibonacci(10)" 
                 << setw(15) << r3 
                 << setw(15) << recursionCounter << endl;
                 
            // 4. Super Digit
            recursionCounter = 0;
            int r4 = superDigitRecursive(9875);
            cout << left << setw(25) << "SuperDigit(9875)" 
                 << setw(15) << r4 
                 << setw(15) << recursionCounter << endl;

            printSeparator();
            cout << "Analysis complete.\n";

        } else if (choice == 2) {
            int n;
            cout << "\nEnter Fibonacci number (recommend 5 or 6 for demo): ";
            cin >> n;

            cout << "\n--- RECURSION TREE VISUALIZATION ---\n";
            verboseMode = true; // ВКЛЮЧВАМЕ ВИЗУАЛИЗАЦИЯТА
            recursionCounter = 0;
            maxDepth = 0;
            currentDepth = 0;

            int res = fibonacciRecursive(n);

            verboseMode = false; // Изключваме я след това
            printSeparator();
            cout << "Result: " << res << endl;
            cout << "Total Recursive Calls: " << recursionCounter << endl;
            cout << "Max Stack Depth: " << maxDepth << " (How deep memory went)\n";
            printSeparator();
        }

    } while (choice != 0);
}

int main() {
    int choice;
    do {
        cout << "\n==========================\n";
        cout << "   PROJECT MASTER MENU\n";
        cout << "==========================\n";
        cout << "1. Maximum Subsequence Problem\n";
        cout << "2. Recursive Algorithms\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        if (choice == 1) runMaxSubsequenceBenchmark();
        else if (choice == 2) runRecursiveTests();

    } while (choice != 0);

    return 0;
}