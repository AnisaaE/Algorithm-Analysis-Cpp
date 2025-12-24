#include "recursive.h"
#include <iostream>
#include <cstdio>
#include <algorithm> // за std::max

using namespace std;

// Дефиниране на глобалните променливи
long long recursionCounter = 0;
int currentDepth = 0;
int maxDepth = 0;
bool verboseMode = false;

// Helper: Принтира чертички според дълбочината
void printIndent() {
    for (int i = 0; i < currentDepth; ++i) cout << "  |";
    cout << "--";
}

// 1. Sum 1+2+...+N
int sumRecursive(int n) {
    recursionCounter++;
    if (n == 1) return 1;
    return sumRecursive(n - 1) + n;
}

// 2. Sum of Array
int sumArrayRecursive(const int* A, int n) {
    recursionCounter++;
    if (n == 1) return A[0];
    return sumArrayRecursive(A, n - 1) + A[n - 1];
}

// 3. Power
double powerRecursive(double a, int n) {
    recursionCounter++;
    if (n == 0) return 1;
    if (n == 1) return a;
    return powerRecursive(a, n - 1) * a;
}

// 4. Fibonacci (С ВИЗУАЛИЗАЦИЯ)
int fibonacciRecursive(int n) {
    // 1. Обновяване на статистиката
    recursionCounter++;
    currentDepth++;
    if (currentDepth > maxDepth) maxDepth = currentDepth;

    // 2. Визуализация (само ако е включена)
    if (verboseMode) {
        printIndent();
        cout << "fib(" << n << ")" << endl;
    }

    int result;
    // 3. Логика от слайда
    if (n == 0) result = 0;
    else if (n == 1) result = 1;
    else result = fibonacciRecursive(n - 1) + fibonacciRecursive(n - 2);

    // 4. Излизане от дълбочината
    currentDepth--;
    return result;
}

// 5. Tower of Hanoi
void towerOfHanoi(int n, int src, int target, int aux) {
    recursionCounter++;
    if (n <= 0) return;
    
    towerOfHanoi(n - 1, src, aux, target);
    // Move logic printed directly
    if (verboseMode) {
         // Може да се форматира по-красиво тук
    } else {
        // Стандартно принтиране само ако не сме в "Silent benchmark mode"
        // cout << "Move " << n << "..." << endl; 
        // (Оставих го празно за benchmark, в main ще го включим)
    }
    
    // За да не спами конзолата, принтираме само хода
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