#ifndef GREEDY_H
#define GREEDY_H

#include <vector>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <map>
#include <queue>
#include <string>

// --- Job Scheduling Structures ---
struct Job {
    int id;
    int duration;
};

// --- Activity Selection Structures ---
struct Activity {
    int id;
    int start;
    int finish;
};

// --- HUFFMAN STRUCTURES (NEW) ---
struct HuffmanNode {
    char data;      // 'a', 'b' etc. ('$' for internal nodes)
    unsigned freq;  // Frequency
    HuffmanNode *left, *right;

    HuffmanNode(char data, unsigned freq) {
        left = right = nullptr;
        this->data = data;
        this->freq = freq;
    }
};

// Comparator for Priority Queue (Min-Heap behavior)
struct Compare {
    bool operator()(HuffmanNode* l, HuffmanNode* r) {
        return (l->freq > r->freq);
    }
};

// --- ALGORITHMS ---
void jobScheduling(std::vector<Job>& jobs);
void activitySelection(std::vector<Activity>& activities);
void huffmanCoding(const std::string& text);

#endif