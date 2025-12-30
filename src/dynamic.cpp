#include "dynamic.h"

using namespace std;

void printTable(const vector<int>& table, string name) {
    cout << "\nTable [" << name << "]: ";
    cout << "[ ";
    for (int val : table) cout << val << " ";
    cout << "]\n";
}

void print2DMatrix(const vector<vector<int>>& mat, string title) {
    cout << "\n--- " << title << " ---\n";
    for (const auto& row : mat) {
        for (int val : row) {
            if (val == -1) cout << setw(5) << "-";
            else cout << setw(5) << val << " ";
        }
        cout << endl;
    }
}

// ==========================================
// 1. FIBONACCI (Bottom-Up DP)
// ==========================================
void runFibonacciDP(int n) {
    if (n < 0) return;

    vector<int> SolTable(n + 1);

    SolTable[0] = 0;
    if (n > 0) SolTable[1] = 1;

    for (int i = 2; i <= n; i++) {
        SolTable[i] = SolTable[i - 1] + SolTable[i - 2];
    }

    cout << "\n--- Fibonacci Bottom-Up DP Table ---\n";
    printTable(SolTable, "SolTable");
    
    cout << "Result F(" << n << ") = " << SolTable[n] << endl;
}

// ==========================================
// 2. MINIMUM COST PATH (Top-Down Memoization)
// ==========================================

vector<vector<int>> memo; 
int N_SIZE;

// recursion top-down)
// M = cost matrix, i, j = current position
int MinimumCostPath_Recursive_Aux(const vector<vector<int>>& M, int i, int j) {
    if (i >= N_SIZE || j >= N_SIZE) return INT_MAX;

    if (i == N_SIZE - 1 && j == N_SIZE - 1) {
        return M[i][j];
    }

    if (memo[i][j] != -1) {
        return memo[i][j];
    }

    // Compute the cost of the path that goes through the down slot
    long long downCost = INT_MAX; 
    if (i + 1 < N_SIZE) {
        int res = MinimumCostPath_Recursive_Aux(M, i + 1, j);
        if (res != INT_MAX) downCost = res;
    }

    // Compute the cost of the path that goes through the right slot
    long long rightCost = INT_MAX;
    if (j + 1 < N_SIZE) {
        int res = MinimumCostPath_Recursive_Aux(M, i, j + 1);
        if (res != INT_MAX) rightCost = res;
    }

    // Min cost logic
    int minNext = min((int)downCost, (int)rightCost);
    
    // Memoization
    if (minNext != INT_MAX)
        memo[i][j] = M[i][j] + minNext;
    else
        memo[i][j] = M[i][j]; 

    return memo[i][j];
}

void runMinCostPath(const vector<vector<int>>& grid) {
    N_SIZE = grid.size();
    
    memo.assign(N_SIZE, vector<int>(N_SIZE, -1));

    cout << "\n--- Minimum Cost Path (Top-Down DP) ---\n";
    print2DMatrix(grid, "Cost Grid (Input)");

    int result = MinimumCostPath_Recursive_Aux(grid, 0, 0);

    print2DMatrix(memo, "DP Memoization Table (Calculated Costs)");
    cout << "Minimum Cost to reach (" << N_SIZE-1 << "," << N_SIZE-1 << "): " << result << endl;
}

// ==========================================
// 3. 0/1 KNAPSACK PROBLEM (DP Table)
// ==========================================
void runKnapsackDP(int W, const vector<Item>& items) {
    int n = items.size();

    // create table dp[n+1][W+1]
    // row 0..n (Items), columns 0..W (Capacity)
    vector<vector<int>> dp(n + 1, vector<int>(W + 1));

    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0) {
                dp[i][w] = 0;
            }
            else {
                int weight = items[i - 1].weight;
                int value = items[i - 1].value;

                if (weight <= w) {
                    // max(don't take, take)
                    // take_val = value + dp[i-1][w-weight]
                    // leave_val = dp[i-1][w]
                    dp[i][w] = max(dp[i - 1][w], value + dp[i - 1][w - weight]);
                } else {
                    // Ако не се побира
                    dp[i][w] = dp[i - 1][w];
                }
            }
        }
    }

    cout << "\n--- Knapsack DP Table (Rows: Items 0-" << n << ", Cols: Weight 0-" << W << ") ---\n";
    
    // Header row
    cout << "      ";
    for(int w = 0; w <= W; w++) cout << setw(4) << w << " ";
    cout << "\n";

    for (int i = 0; i <= n; i++) {
        cout << "i=" << i << " | ";
        for (int w = 0; w <= W; w++) {
            cout << setw(4) << dp[i][w] << " ";
        }
        cout << "\n";
    }

    cout << "\nMax Value: " << dp[n][W] << endl;
}