#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include <iostream>
#include <climits> // For INT_MIN

class BinaryHeap {
public:
    // Constructor (Creates empty heap)
    BinaryHeap(int capacity = 100);

    // Constructor (BuildHeap from existing array) - O(N)
    BinaryHeap(const std::vector<int>& items);

    bool isEmpty() const;
    int findMin() const;

    // Operations from slides
    void insert(int key);           // InsertKey
    void deleteMin();               // DeleteMin (void version)
    int deleteMinReturn();          // DeleteMin (returns value)
    
    // Additional Operations (from text description)
    void decreaseKey(int index, int delta);
    void increaseKey(int index, int delta);
    void deleteKey(int index);

    // Visualization
    void printHeap();
    const std::vector<int>& getElements() const; // Helper for merge

private:
    int currentSize;       // N
    std::vector<int> array; // The heap array (H)

    // Helper: Restore heap property downwards
    void percolateDown(int hole);
};

// Merge function (External to class as per description)
BinaryHeap mergeHeaps(const BinaryHeap& h1, const BinaryHeap& h2);

#endif