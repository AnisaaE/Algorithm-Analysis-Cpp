#ifndef RECURSIVE_H
#define RECURSIVE_H

#include <vector>
#include <iostream>
#include <string>

// --- GLOBALS FOR ANALYSIS ---
extern long long recursionCounter; // Брой извиквания
extern int currentDepth;           // Текуща дълбочина (Stack depth)
extern int maxDepth;               // Най-голяма достигната дълбочина
extern bool verboseMode;           // Дали да принтираме дървото (Visualization on/off)

// --- HELPER ---
// Функция за правене на отстъпи (Visual Tree)
void printIndent();

// --- ALGORITHMS ---
int sumRecursive(int n);
int sumArrayRecursive(const int* A, int n);
double powerRecursive(double a, int n);
int fibonacciRecursive(int n);
void towerOfHanoi(int n, int src, int target, int aux);
int superDigitRecursive(int n);

#endif