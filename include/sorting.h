#ifndef SORTING_H
#define SORTING_H

#include <vector>

// --- O(n^2) SLOW SORTS ---
void selectionSort(int* A, int n);
void bubbleSort(int* A, int n);
void insertionSort(int* A, int n);

// --- O(n log n) FAST SORTS ---
void mergeSort(int* A, int n);
void quickSort(int* A, int n);
void heapSort(int* A, int n); // 

// --- O(n) LINEAR SORTS ---
// Counting Sort със "Satellite Data" логика (Stable)
void countingSort(int* A, int n);

// Radix Sort (Базиран на Counting Sort)
void radixSort(int* A, int n);

void externalSort(int* A, int n);

// Helper
void swapInt(int* a, int* b);

#endif