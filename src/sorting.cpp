#include "sorting.h"
#include <vector>
#include <iostream>
#include <algorithm> // за std::max

using namespace std;

// ==========================================
//            ПОМОЩНИ ФУНКЦИИ (HELPERS)
// ==========================================

// Размяна на две числа (Swap)
void swapInt(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Логика за сливане (Merge) - използва се от Merge Sort
void mergeLogic(int* A, int n, int mid) {
    // mid е размерът на лявата част
    // n е общият размер
    vector<int> leftArr(mid);
    vector<int> rightArr(n - mid);

    // Копиране на данните
    for (int i = 0; i < mid; i++) leftArr[i] = A[i];
    for (int i = mid; i < n; i++) rightArr[i - mid] = A[i];

    int i = 0, j = 0, k = 0;
    
    // Сливане
    while (i < mid && j < (n - mid)) {
        if (leftArr[i] <= rightArr[j]) {
            A[k++] = leftArr[i++];
        } else {
            A[k++] = rightArr[j++];
        }
    }

    // Докопиране на останалите
    while (i < mid) A[k++] = leftArr[i++];
    while (j < (n - mid)) A[k++] = rightArr[j++];
}

// Логика за разделяне (Partition) - използва се от Quick Sort
// Source: image_7e74ea.png (Pivot = A[0])
int partitionLogic(int* A, int n) {
    if (n <= 1) return 0;
    int pivot = A[0]; 
    int i = 1;
    int j = n - 1;

    while (true) {
        // Мести j наляво, докато намери по-малко от пивота
        while (j > 0 && A[j] > pivot) j--;
        
        // Мести i надясно, докато намери по-голямо от пивота
        // (Добавена проверка i <= j за безопасност)
        while (i < n && i <= j && A[i] < pivot) i++;

        if (i >= j) break;

        swapInt(&A[i], &A[j]);
        i++;
        j--;
    }

    swapInt(&A[j], &A[0]); // Връщане на пивота на правилното място
    return j; // Връщаме индекса на пивота
}

// Логика за Heapify (Sift Down) - използва се от Heap Sort
void percDown(int* A, int i, int n) {
    int child;
    int tmp;

    for (tmp = A[i]; (2 * i + 1) < n; i = child) {
        child = 2 * i + 1; // Ляво дете
        // Ако дясното дете съществува и е по-голямо, избираме него
        if (child != n - 1 && A[child + 1] > A[child]) {
            child++;
        }
        // Ако детето е по-голямо от tmp -> качваме детето нагоре
        if (A[child] > tmp) {
            A[i] = A[child];
        } else {
            break;
        }
    }
    A[i] = tmp;
}

// ==========================================
//        1. БАВНИ СОРТИРОВКИ O(n^2)
// ==========================================

// Selection Sort
// Source: image_7e13b1.jpg
void selectionSort(int* A, int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (A[j] < A[minIndex]) 
                minIndex = j;
        }
        if (i != minIndex) 
            swapInt(&A[i], &A[minIndex]);
    }
}

// Bubble Sort
// Source: image_7e13ed.jpg
void bubbleSort(int* A, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 1; j < (n - i); j++) {
            if (A[j - 1] > A[j]) {
                swapInt(&A[j - 1], &A[j]);
            }
        }
    }
}

// Insertion Sort
// Source: image_7e142c.jpg
void insertionSort(int* A, int n) {
    int j, P, Tmp;
    for (P = 1; P < n; P++) {
        Tmp = A[P];
        for (j = P; j > 0 && A[j - 1] > Tmp; j--) {
            A[j] = A[j - 1];
        }
        A[j] = Tmp;
    }
}

// ==========================================
//        2. БЪРЗИ СОРТИРОВКИ O(n log n)
// ==========================================

// Merge Sort
// Source: image_7e1734.png
void mergeSort(int* A, int n) {
    if (n <= 1) return;

    int middle = n / 2;

    mergeSort(A, middle);               // Sort LHS
    mergeSort(A + middle, n - middle);  // Sort RHS

    mergeLogic(A, n, middle);
}

// Quick Sort
// Source: image_7e2231.png
void quickSort(int* A, int n) {
    if (n <= 1) return;

    int index = partitionLogic(A, n);

    quickSort(A, index); // Sort Left Part
    
    // Sort Right Part (index + 1 нататък)
    quickSort(A + index + 1, n - index - 1);
}

// Heap Sort
// Source: image_7e842c.png & image_7e8468.png
void heapSort(int* A, int n) {
    // 1. Build Heap (Построяване на пирамидата)
    for (int i = n / 2; i >= 0; i--) {
        percDown(A, i, n);
    }

    // 2. Delete Max (Сортиране)
    for (int i = n - 1; i > 0; i--) {
        swapInt(&A[0], &A[i]); // Най-големият отива накрая
        percDown(A, 0, i);     // Възстановяване на пирамидата
    }
}

// ==========================================
//        3. ЛИНЕЙНИ СОРТИРОВКИ O(n)
// ==========================================

// Counting Sort (Stable version for Satellite Data)
void countingSort(int* A, int n) {
    if (n <= 1) return;

    // Намиране на максималния елемент
    int maxVal = A[0];
    for (int i = 1; i < n; i++) {
        if (A[i] > maxVal) maxVal = A[i];
    }

    // Вектор за бройките
    vector<int> count(maxVal + 1, 0);

    // Броене
    for (int i = 0; i < n; i++) {
        count[A[i]]++;
    }

    // Кумулативно сумиране (за стабилност)
    for (int i = 1; i <= maxVal; i++) {
        count[i] += count[i - 1];
    }

    // Построяване на изходния масив
    vector<int> output(n);
    for (int i = n - 1; i >= 0; i--) {
        output[count[A[i]] - 1] = A[i];
        count[A[i]]--;
    }

    // Копиране обратно в оригиналния масив
    for (int i = 0; i < n; i++) {
        A[i] = output[i];
    }
}

// Помощна за Radix Sort
void countingSortForRadix(int* A, int n, int exp) {
    vector<int> output(n);
    int count[10] = {0};

    // Броене на цифрите
    for (int i = 0; i < n; i++)
        count[(A[i] / exp) % 10]++;

    // Кумулативно
    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // Output
    for (int i = n - 1; i >= 0; i--) {
        output[count[(A[i] / exp) % 10] - 1] = A[i];
        count[(A[i] / exp) % 10]--;
    }

    // Copy back
    for (int i = 0; i < n; i++)
        A[i] = output[i];
}

// Radix Sort
void radixSort(int* A, int n) {
    // Намиране на макс
    int maxVal = A[0];
    for (int i = 1; i < n; i++)
        if (A[i] > maxVal) maxVal = A[i];

    // Сортиране по разреди (1, 10, 100...)
    for (int exp = 1; maxVal / exp > 0; exp *= 10) {
        countingSortForRadix(A, n, exp);
    }
}