#include <iostream>
#include <vector>
#include <chrono> // For time measurement
#include <random> // For random number generation
#include "max_subsequence.h"

using namespace std;
using namespace std::chrono;

// Helper function to print an array
void printArray(const vector<int>& arr) {
    if (arr.size() > 20) {
        cout << "[Array is too big to print]" << endl;
        return;
    }
    for (int x : arr) cout << x << " ";
    cout << endl;
}

// Helper function to generate a random array
vector<int> generateRandomArray(int size) {
    vector<int> arr(size);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(-100, 100); // Random numbers between -100 and 100

    for (int i = 0; i < size; i++) {
        arr[i] = dis(gen);
    }
    return arr;
}

// Benchmark Function (Performance Test)
void runBenchmark() {
    int n;
    cout << "\n--- BENCHMARK MODE ---\n";
    cout << "Enter array size (e.g., 1000, 5000): ";
    cin >> n;

    vector<int> data = generateRandomArray(n);
    cout << "Array generated with size " << n << ".\nStart testing...\n" << endl;

    // Timer for O(n^3)
    auto start = high_resolution_clock::now();
    maxSubSum1(data);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "1. Brute Force O(n^3): \t" << duration.count() << " microseconds" << endl;

    // Timer for O(n^2)
    start = high_resolution_clock::now();
    maxSubSum2(data);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "2. Improved O(n^2):    \t" << duration.count() << " microseconds" << endl;

    // Timer for O(n log n)
    start = high_resolution_clock::now();
    maxSubSum3(data);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "3. Div & Conq O(nlogn):\t" << duration.count() << " microseconds" << endl;

    // Timer for O(n)
    start = high_resolution_clock::now();
    maxSubSum4(data);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "4. Kadane O(n):        \t" << duration.count() << " microseconds" << endl;
}

// Single Test Function (Correctness Test)
void runSingleTest() {
    vector<int> testData = {-2, 11, -4, 13, -5, -2};
    cout << "\n--- SINGLE TEST MODE ---\n";
    cout << "Test Array: ";
    printArray(testData);

    cout << "Max Sum (O(n^3)): " << maxSubSum1(testData) << endl;
    cout << "Max Sum (O(n^2)): " << maxSubSum2(testData) << endl;
    cout << "Max Sum (Rec):    " << maxSubSum3(testData) << endl;
    cout << "Max Sum (Kadane): " << maxSubSum4(testData) << endl;
}

int main() {
    int choice;
    do {
        cout << "\n==========================\n";
        cout << "   ALGORITHM PROJECT MENU\n";
        cout << "==========================\n";
        cout << "1. Maximum Subsequence Problem\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        if (choice == 1) {
            int subChoice;
            cout << "\n   1. Single Test (Correctness)\n";
            cout << "   2. Benchmark (Performance)\n";
            cout << "   Choice: ";
            cin >> subChoice;

            if (subChoice == 1) runSingleTest();
            else if (subChoice == 2) runBenchmark();
        }

    } while (choice != 0);

    return 0;
}