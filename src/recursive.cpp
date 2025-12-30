#include "recursive.h"
#include <iostream>
#include <cstdio>
#include <algorithm> 

using namespace std;

// global variables for statistics
long long recursionCounter = 0;
int currentDepth = 0;
int maxDepth = 0;
bool verboseMode = false; 

void printIndent() {
    for (int i = 0; i < currentDepth; ++i) cout << "  |";
    cout << "--";
}

// 1. Sum from 1 to N
int sumRecursive(int n) {
    recursionCounter++;
    if (n == 1) return 1;
    int partialSum = sumRecursive(n - 1);
    return partialSum + n;
}

// 2. Sum of Array
int sumArrayRecursive(const int* A, int n) {
    recursionCounter++;
    if (n == 1) return A[0];
    int partialSum = sumArrayRecursive(A, n - 1);
    return partialSum + A[n - 1];
}

// 3. Power
double powerRecursive(double a, int n) {
    recursionCounter++;
    if (n == 0) return 1;
    if (n == 1) return a;
    return powerRecursive(a, n - 1) * a;
}

// 4. Fibonacci 
int fibonacciRecursive(int n) {
    recursionCounter++;
    currentDepth++;
    if (currentDepth > maxDepth) maxDepth = currentDepth;

    // it is gonna visualize the callsonly if choosen
    if (verboseMode) {
        printIndent();
        cout << "fib(" << n << ")" << endl;
    }

    int result;
    if (n == 0) result = 0;
    else if (n == 1) result = 1;
    else result = fibonacciRecursive(n - 1) + fibonacciRecursive(n - 2);

    currentDepth--;
    return result;
}

// 5. Tower of Hanoi
void towerOfHanoi(int n, char src, char target, char aux) {
    recursionCounter++;
    if (n <= 0) return;
    
    towerOfHanoi(n - 1, src, aux, target);
    cout << "Move disk " << n << " from " << char(src) << " to " << char(target) << endl;

    towerOfHanoi(n - 1, aux, target, src);
}

// 6. Super Digit
int superDigitRecursive(int n) {
    recursionCounter++;
    if (n < 10) return n;
    int sum = 0, temp = n;
    while(temp > 0) { sum += temp % 10; temp /= 10; }
    return superDigitRecursive(sum);
}