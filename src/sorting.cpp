#include "sorting.h"
#include <vector>
#include <iostream>
#include <algorithm> 
#include <fstream>
#include <queue>
#include <string>
#include <cstdio> 

using namespace std;

// ==========================================
//            (HELPERS)
// ==========================================

void swapInt(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

//Merge logic for Merge Sort
void mergeLogic(int* A, int n, int mid) {
    // mid 
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
//        O(n^2)
// ==========================================

// Selection Sort
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
//        O(n log n)
// ==========================================

// Merge Sort
void mergeSort(int* A, int n) {
    if (n <= 1) return;

    int middle = n / 2;

    mergeSort(A, middle);               // Sort LHS
    mergeSort(A + middle, n - middle);  // Sort RHS

    mergeLogic(A, n, middle);
}

// Quick Sort
void quickSort(int* A, int n) {
    if (n <= 1) return;

    int index = partitionLogic(A, n);

    quickSort(A, index); // Sort Left Part
    quickSort(A + index + 1, n - index - 1);
}

// Heap Sort
void heapSort(int* A, int n) {
    // 1. Build Heap
    for (int i = n / 2; i >= 0; i--) {
        percDown(A, i, n);
    }

    // 2. Delete Max
    for (int i = n - 1; i > 0; i--) {
        swapInt(&A[0], &A[i]); 
        percDown(A, 0, i);     
    }
}

// ==========================================
//        3.  O(n)
// ==========================================

// Counting Sort (Stable version for Satellite Data)
void countingSort(int* A, int n) {
    if (n <= 1) return;

    int maxVal = A[0];
    for (int i = 1; i < n; i++) {
        if (A[i] > maxVal) maxVal = A[i];
    }

    vector<int> count(maxVal + 1, 0);

    // Броене
    for (int i = 0; i < n; i++) {
        count[A[i]]++;
    }

    for (int i = 1; i <= maxVal; i++) {
        count[i] += count[i - 1];
    }

    vector<int> output(n);
    for (int i = n - 1; i >= 0; i--) {
        output[count[A[i]] - 1] = A[i];
        count[A[i]]--;
    }

    for (int i = 0; i < n; i++) {
        A[i] = output[i];
    }
}

void countingSortForRadix(int* A, int n, int exp) {
    vector<int> output(n);
    int count[10] = {0};

    for (int i = 0; i < n; i++)
        count[(A[i] / exp) % 10]++;

    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; i--) {
        output[count[(A[i] / exp) % 10] - 1] = A[i];
        count[(A[i] / exp) % 10]--;
    }

    for (int i = 0; i < n; i++)
        A[i] = output[i];
}

// Radix Sort
void radixSort(int* A, int n) {
    int maxVal = A[0];
    for (int i = 1; i < n; i++)
        if (A[i] > maxVal) maxVal = A[i];

    for (int exp = 1; maxVal / exp > 0; exp *= 10) {
        countingSortForRadix(A, n, exp);
    }
}

// ==========================================
//     EXTERNAL SORTING (HARICI SIRALAMA)
// ==========================================

// struct for Min-Heap node
struct MinHeapNode {
    int element; 
    int i;       
};

// Comparator for the priority queue (to work like Min-Heap)
struct comp {
    bool operator()(MinHeapNode l, MinHeapNode r) {
        return l.element > r.element;
    }
};

/**
 * K-Way Merging (8 Yollu Birleştirme)
 * using Binary Heap to merge k sorted files
 */
void mergeFiles(const char* output_file, int k) {
    vector<ifstream*> inFiles(k);
    for (int i = 0; i < k; i++) {
        string fileName = "temp_" + to_string(i) + ".txt";
        inFiles[i] = new ifstream(fileName);
    }

    ofstream out(output_file);
    
    priority_queue<MinHeapNode, vector<MinHeapNode>, comp> pq;

    for (int i = 0; i < k; i++) {
        int val;
        if (*inFiles[i] >> val) {
            pq.push({val, i});
        }
    }

    while (!pq.empty()) {
        MinHeapNode root = pq.top();
        pq.pop();

        out << root.element << " ";

        int i = root.i;
        int nextVal;
        if (*inFiles[i] >> nextVal) {
            pq.push({nextVal, i});
        }
    }

    for (int i = 0; i < k; i++) {
        inFiles[i]->close();
        delete inFiles[i];
        string fileName = "temp_" + to_string(i) + ".txt";
        remove(fileName.c_str());
    }
    out.close();
}

/**
 * creating initial runs 
 */
int createInitialRuns(const char* input_file, int run_size) {
    ifstream in(input_file);
    if (!in.is_open()) return 0;

    ofstream out;
    vector<int> arr(run_size);
    bool moreInput = true;
    int nextRunIdx = 0;
    int val;

    while (moreInput) {
        int i = 0;
        // simulation og RAM limit
        while (i < run_size && in >> val) {
            arr[i++] = val;
        }

        if (i == 0) break; 

        sort(arr.begin(), arr.begin() + i);

        string fileName = "temp_" + to_string(nextRunIdx) + ".txt";
        out.open(fileName);
        for (int j = 0; j < i; j++) {
            out << arr[j] << " ";
        }
        out.close();
        nextRunIdx++;
    }
    in.close();
    return nextRunIdx;
}

void externalSort(int* A, int n) {
    const char* input_file = "data_input.txt";
    const char* output_file = "data_output.txt";
    
    ofstream inFile(input_file);
    for (int i = 0; i < n; i++) {
        inFile << A[i] << " ";
    }
    inFile.close();

    int run_size = (n < 20) ? 2 : (n / 10 + 1); 

    int numRuns = createInitialRuns(input_file, run_size);

    mergeFiles(output_file, numRuns);

    ifstream outFile(output_file);
    for (int i = 0; i < n; i++) {
        outFile >> A[i];
    }
    outFile.close();

    remove(input_file);
    remove(output_file);
}