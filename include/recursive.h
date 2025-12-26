#ifndef RECURSIVE_H
#define RECURSIVE_H

#include <vector>
#include <iostream>

// --- GLOBALS FOR ANALYSIS ---
// Тези редове казват на Main.cpp, че тези променливи съществуват някъде
extern long long recursionCounter; 
extern int currentDepth;           
extern int maxDepth;               
extern bool verboseMode; // <--- ТОВА ЛИПСВАШЕ

// --- ALGORITHMS ---
int sumRecursive(int n);
int sumArrayRecursive(const int* A, int n);
double powerRecursive(double a, int n);
int fibonacciRecursive(int n);
int superDigitRecursive(int n);

// Използваме char, както поиска
void towerOfHanoi(int n, char src, char target, char aux);

#endif