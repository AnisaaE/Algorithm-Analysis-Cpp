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

// Сравнителна функция: Сортираме задачите по продължителност (възходящ ред)
bool compareJobs(const Job& a, const Job& b) {
    return a.duration < b.duration;
}

void jobScheduling(vector<Job>& jobs) {
    if (jobs.empty()) return;

    // 1. Greedy Стъпка: Сортиране по най-къса задача (SJF)
    sort(jobs.begin(), jobs.end(), compareJobs);

    cout << "\n--- OPTIMAL JOB SCHEDULE (Shortest Job First) ---\n";
    cout << "Execution Order: ";
    
    double currentCompletionTime = 0;
    double totalCompletionTime = 0; // Използваме това за средното време

    // 2. Изчисляване на времената
    for (size_t i = 0; i < jobs.size(); i++) {
        currentCompletionTime += jobs[i].duration;
        totalCompletionTime += currentCompletionTime;
        
        cout << "J" << jobs[i].id << "(" << jobs[i].duration << ")";
        if (i < jobs.size() - 1) cout << " -> ";
    }
    cout << endl;

    // 3. Резултат: Средно време за завършване
    double averageTime = totalCompletionTime / jobs.size();
    cout << "Total Completion Time: " << totalCompletionTime << endl;
    cout << "Average Completion Time: " << fixed << setprecision(2) << averageTime << endl;
}

// ==========================================
// 2. ACTIVITY SELECTION (Max Non-overlapping)
// ==========================================

// Сравнителна функция: Сортираме по време на ПРИКЛЮЧВАНЕ (Finish Time)
bool compareActivities(const Activity& a, const Activity& b) {
    return a.finish < b.finish;
}

void activitySelection(vector<Activity>& activities) {
    if (activities.empty()) return;

    // 1. Greedy Стъпка: Сортиране по Finish Time
    sort(activities.begin(), activities.end(), compareActivities);

    cout << "\n--- ACTIVITY SELECTION (Max Non-Overlapping Subset) ---\n";
    
    // Покажи сортирания списък (за проверка)
    /*
    cout << "Activities sorted by finish time:\n";
    for(const auto& a : activities) {
        cout << "A" << a.id << "[" << a.start << "-" << a.finish << "] ";
    }
    cout << endl;
    */

    vector<Activity> selected;
    
    // 2. Винаги избираме първата дейност (тази, която свършва най-рано)
    selected.push_back(activities[0]);
    int lastFinishTime = activities[0].finish;

    // 3. Обхождаме останалите
    for (size_t i = 1; i < activities.size(); i++) {
        // Ако новата дейност започва СЛЕД или КОГАТО свършва предишната
        if (activities[i].start >= lastFinishTime) {
            selected.push_back(activities[i]);
            lastFinishTime = activities[i].finish; // Обновяваме края
        }
    }

    // 4. Резултат
    cout << "Selected Activities (" << selected.size() << " total): ";
    for (const auto& a : selected) {
        cout << "A" << a.id << " ";
    }
    cout << endl;
}

// ==========================================
// 3. HUFFMAN CODING (Data Compression)
// ==========================================

// Помощна рекурсивна функция за принтиране на кодовете (Обхождане на дървото)
void printCodes(HuffmanNode* root, string code) {
    if (!root) return;

    // Ако е листо (има буква, а не е $), принтираме кода
    if (root->data != '$') {
        cout << "'" << root->data << "': " << code << endl;
    }

    // Рекурсия: Наляво добавяме '0', Надясно добавяме '1'
    printCodes(root->left, code + "0");
    printCodes(root->right, code + "1");
}

void huffmanCoding(const string& text) {
    cout << "\n--- HUFFMAN CODING LOGIC ---\n";
    cout << "Input Text: \"" << text << "\"\n";

    // 1. Преброяване на честотите (Frequency Count)
    map<char, unsigned> freqMap;
    for (char c : text) {
        freqMap[c]++;
    }

    // Принтиране на честотите (за проверка)
    cout << "Frequencies: ";
    for (auto pair : freqMap) {
        cout << pair.first << ":" << pair.second << " ";
    }
    cout << endl;

    // 2. Създаване на Min-Heap (Priority Queue)
    // Използваме Comparator от greedy.h
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> minHeap;

    for (auto pair : freqMap) {
        minHeap.push(new HuffmanNode(pair.first, pair.second));
    }

    // 3. Построяване на дървото (Build Tree Bottom-Up)
    while (minHeap.size() != 1) {
        // Вадим двете най-малки честоти
        HuffmanNode* left = minHeap.top();
        minHeap.pop();

        HuffmanNode* right = minHeap.top();
        minHeap.pop();

        // Създаваме нов вътрешен възел (родител) със сумата от честотите
        // '$' е символ за вътрешен възел (не се ползва)
        HuffmanNode* top = new HuffmanNode('$', left->freq + right->freq);
        
        top->left = left;
        top->right = right;

        // Връщаме новия възел в опашката
        minHeap.push(top);
    }

    // 4. Принтиране на резултатите
    cout << "Generated Huffman Codes:\n";
    printCodes(minHeap.top(), "");
    
    // Забележка: В истинска програма тук трябва да освободим паметта (delete),
    // но за целите на университетски проект това е достатъчно.
}