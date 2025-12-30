#include "greedy.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <map>
#include <queue>
#include <string>

using namespace std;

// ==========================================
// 1. JOB SCHEDULING (Shortest Job First)
// ==========================================

bool compareJobs(const Job& a, const Job& b) {
    return a.duration < b.duration;
}

void jobScheduling(vector<Job>& jobs) {
    if (jobs.empty()) return;

    sort(jobs.begin(), jobs.end(), compareJobs);

    cout << "\n--- OPTIMAL JOB SCHEDULE (Shortest Job First) ---\n";
    cout << "Execution Order: ";
    
    double currentCompletionTime = 0;
    double totalCompletionTime = 0; 

    for (size_t i = 0; i < jobs.size(); i++) {
        currentCompletionTime += jobs[i].duration;
        totalCompletionTime += currentCompletionTime;
        
        cout << "J" << jobs[i].id << "(" << jobs[i].duration << ")";
        if (i < jobs.size() - 1) cout << " -> ";
    }
    cout << endl;

    double averageTime = totalCompletionTime / jobs.size();
    cout << "Total Completion Time: " << totalCompletionTime << endl;
    cout << "Average Completion Time: " << fixed << setprecision(2) << averageTime << endl;
}

// ==========================================
// 2. ACTIVITY SELECTION (Max Non-overlapping)
// ==========================================

// compare  by finish time
bool compareActivities(const Activity& a, const Activity& b) {
    return a.finish < b.finish;
}

void activitySelection(vector<Activity>& activities) {
    if (activities.empty()) return;

    sort(activities.begin(), activities.end(), compareActivities);

    cout << "\n--- ACTIVITY SELECTION (Max Non-Overlapping Subset) ---\n";
    
    vector<Activity> selected;
    
    selected.push_back(activities[0]);
    int lastFinishTime = activities[0].finish;

    for (size_t i = 1; i < activities.size(); i++) {
        if (activities[i].start >= lastFinishTime) {
            selected.push_back(activities[i]);
            lastFinishTime = activities[i].finish; 
        }
    }

    cout << "Selected Activities (" << selected.size() << " total): ";
    for (const auto& a : selected) {
        cout << "A" << a.id << " ";
    }
    cout << endl;
}

// ==========================================
// 3. HUFFMAN CODING (Encode & Decode)
// ==========================================

// saving the codes in map
void storeCodes(HuffmanNode* root, string str, map<char, string>& huffmanCode) {
    if (!root) return;

    // Ако е листо (буква)
    if (root->data != '$') {
        huffmanCode[root->data] = str;
    }

    storeCodes(root->left, str + "0", huffmanCode);
    storeCodes(root->right, str + "1", huffmanCode);
}

// DECODE Logic
void decodeText(HuffmanNode* root, string encodedStr) {
    cout << "\n[DECODING STEP]: Converting bits back to text...\n";
    
    string decodedResult = "";
    HuffmanNode* curr = root;

    for (char bit : encodedStr) {
        if (bit == '0') {
            curr = curr->left;
        } else {
            curr = curr->right;
        }

        if (!curr->left && !curr->right) {
            decodedResult += curr->data; 
            curr = root;
        }
    }
    cout << "Decoded Text: " << decodedResult << endl;
}

void huffmanCoding(const string& text) {
    cout << "\n--- HUFFMAN CODING (ENCODE & DECODE) ---\n";
    cout << "Original Input: \"" << text << "\"\n";

    map<char, unsigned> freqMap;
    for (char c : text) {
        freqMap[c]++;
    }

    // creating Min-Heap (Priority Queue)
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> minHeap;
    for (auto pair : freqMap) {
        minHeap.push(new HuffmanNode(pair.first, pair.second));
    }

    // Build Tree Bottom-Up
    while (minHeap.size() != 1) {
        HuffmanNode* left = minHeap.top(); minHeap.pop();
        HuffmanNode* right = minHeap.top(); minHeap.pop();

        HuffmanNode* top = new HuffmanNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;

        minHeap.push(top);
    }
    
    // saving the root for decode
    HuffmanNode* root = minHeap.top();

    // generate encode table
    map<char, string> huffmanCode;
    storeCodes(root, "", huffmanCode);

    cout << "\n[CODE TABLE generated]:\n";
    for (auto pair : huffmanCode) {
        cout << "'" << pair.first << "': " << pair.second << endl;
    }

    string encodedString = "";
    for (char c : text) {
        encodedString += huffmanCode[c];
    }
    cout << "\n[ENCODED STRING] (Compressed Data):\n" << encodedString << endl;

    decodeText(root, encodedString);

    
    // memory calculations

    // Original size (8 bits per char)
    int originalBits = text.length() * 8;

    // Compressed size (Huffman)
    int compressedBits = 0;
    for (auto pair : freqMap) {
        char c = pair.first;
        int freq = pair.second;
        int codeLength = huffmanCode[c].length();
        compressedBits += freq * codeLength;
    }

    cout << "\n[MEMORY USAGE]\n";
    cout << "Original size:   " << originalBits << " bits\n";
    cout << "Compressed size: " << compressedBits << " bits\n";

    double compressionRatio =
        (double)compressedBits / originalBits * 100;

    cout << "Compression ratio: " 
         << compressionRatio << " %\n";

    cout << "Memory saved: "
         << (100 - compressionRatio) << " %\n";

}