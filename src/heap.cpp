#include "heap.h"
#include <iostream>

using namespace std;

// --- CONSTRUCTORS ---

BinaryHeap::BinaryHeap(int capacity) {
    // 1-based indexing, so size is capacity + 1
    array.resize(capacity + 1);
    currentSize = 0;
    
    // Sentinel Node (from text: -infinity at index 0)
    array[0] = INT_MIN; 
}

// BuildHeap Logic (Bottom-Up)
// Text: "for i = N/2 to 1 do Heapify(i)"
BinaryHeap::BinaryHeap(const std::vector<int>& items) {
    currentSize = items.size();
    array.resize(currentSize + 1);
    array[0] = INT_MIN; // Sentinel

    // Copy elements starting at index 1
    for (int i = 0; i < currentSize; i++) {
        array[i + 1] = items[i];
    }

    // BuildHeap: Percolate down from N/2 to 1
    for (int i = currentSize / 2; i > 0; i--) {
        percolateDown(i);
    }
}

// --- CORE OPERATIONS ---

bool BinaryHeap::isEmpty() const {
    return currentSize == 0;
}

int BinaryHeap::findMin() const {
    if (isEmpty()) return -1; // Error code
    return array[1];
}

// Source: image_cfc0be.jpg (InsertKey)
void BinaryHeap::insert(int key) {
    // Resize if full
    if (currentSize == array.size() - 1) {
        array.resize(array.size() * 2);
    }

    // Increase # of nodes
    int N = ++currentSize;
    
    // Percolate Up
    // Note: The slide uses "while(1)" with checks.
    // We use the Sentinel at array[0] to stop the loop automatically if needed,
    // but here we follow the slide logic structure.
    
    int node = N;
    while (node > 1) { // Logic adapted for C++ loop
        int parent = node / 2;
        if (array[parent] < key) {
            // Parent is smaller? Then we are done (Min-Heap property satisfied)
            break; 
        }
        
        // Exchange keys with parent
        array[node] = array[parent];
        node = parent; // Move one level up
    }
    array[node] = key; // Insert the key
}

// Helper: Percolate Down (Logic extracted from DeleteMin slide)
void BinaryHeap::percolateDown(int hole) {
    int child;
    int tmp = array[hole];

    while (hole * 2 <= currentSize) {
        child = hole * 2; // Left child
        
        // Check if right child exists and is smaller
        if (child != currentSize && array[child + 1] < array[child]) {
            child++;
        }

        // If child is smaller than tmp, move child up
        if (array[child] < tmp) {
            array[hole] = array[child];
        } else {
            break;
        }
        hole = child;
    }
    array[hole] = tmp;
}

// Source: image_cfc080.jpg (DeleteMin)
void BinaryHeap::deleteMin() {
    if (isEmpty()) return;

    // Move last key to root
    array[1] = array[currentSize];
    currentSize--;

    // Push the key down
    percolateDown(1);
}

int BinaryHeap::deleteMinReturn() {
    if (isEmpty()) return -1;
    int minItem = array[1];
    deleteMin();
    return minItem;
}

// --- ADDITIONAL OPERATIONS (From Text) ---

// Text: "Subtract Delta from H[P]. Then move key Up."
void BinaryHeap::decreaseKey(int index, int delta) {
    if (index > currentSize || index < 1) return;

    array[index] -= delta;
    
    // Percolate Up logic
    int tmp = array[index];
    int node = index;
    while (node > 1 && array[node / 2] > tmp) {
        array[node] = array[node / 2];
        node /= 2;
    }
    array[node] = tmp;
}

// Text: "Add Delta to H[P]. Then move key Down."
void BinaryHeap::increaseKey(int index, int delta) {
    if (index > currentSize || index < 1) return;

    array[index] += delta;
    percolateDown(index);
}

// Text: "Copy H[N] to H[index]. Then move down."
void BinaryHeap::deleteKey(int index) {
    if (index > currentSize || index < 1) return;

    // DecreaseKey to -infinity then deleteMin is standard, 
    // BUT text says: "Copy H[N] to H[index], decrease N, move down".
    array[index] = array[currentSize];
    currentSize--;
    percolateDown(index);
}

// --- UTILS ---

void BinaryHeap::printHeap() {
    if (isEmpty()) {
        cout << "Heap is empty." << endl;
        return;
    }
    cout << "Heap Elements: ";
    for (int i = 1; i <= currentSize; i++) {
        cout << array[i] << " ";
    }
    cout << endl;
}

const std::vector<int>& BinaryHeap::getElements() const {
    return array;
}

// Merge Heaps (External Function)
// Text: "Copy H2 to H1, then BuildHeap. Time: O(N)"
BinaryHeap mergeHeaps(const BinaryHeap& h1, const BinaryHeap& h2) {
    vector<int> combined;
    
    // Get elements from H1
    const vector<int>& v1 = h1.getElements();
    // Start from 1 because 0 is sentinel
    // Note: h1.getElements returns vector with sentinel, need to be careful with size
    // Easier way: Extract raw data.
    
    // We can't access h1.currentSize easily without getter, 
    // but the vector has data up to a point. 
    // Let's assume passed heaps are clean.
    
    // Copy H1 content (ignoring sentinel)
    // We implement strictly as: create vector of all items -> BuildHeap
    
    auto data1 = h1.getElements();
    for(size_t i = 1; i < data1.size(); i++) {
        if(data1[i] != 0 && data1[i] > INT_MIN) combined.push_back(data1[i]);
    }
    
    auto data2 = h2.getElements();
    for(size_t i = 1; i < data2.size(); i++) {
         if(data2[i] != 0 && data2[i] > INT_MIN) combined.push_back(data2[i]);
    }

    // Constructor calls BuildHeap
    return BinaryHeap(combined);
}