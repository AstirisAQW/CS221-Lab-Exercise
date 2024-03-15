/*
CS221 - Lab Activity 03

3. Knapsack Problem
You are given a list of items with weights and values, and a maximum weight capacity for a knapsack.
Find the combination of items with the highest total value that doesn't exceed the weight limit.

Sample Result
Input:  weights = {2, 3, 1, 4}
        values = {10, 40, 30, 50}
        capacity = 5

Output: Maximum value achievable: 80
        Chosen items: 1, 4

*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int knapsack(vector<int>& weights, vector<int>& values, int capacity, vector<int>& chosenItems) {
    int n = weights.size();
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));
    
    for (int i = 1; i <= n; ++i) {
        for (int w = 1; w <= capacity; ++w) {
            if (weights[i - 1] > w) {
                dp[i][w] = dp[i - 1][w];
            } else {
                dp[i][w] = max(dp[i - 1][w], values[i - 1] + dp[i - 1][w - weights[i - 1]]);
            }
        }
    }
    
    int w = capacity;
    for (int i = n; i > 0 && w > 0; --i) {
        if (dp[i][w] != dp[i - 1][w]) {
            chosenItems.push_back(i - 1);
            w -= weights[i - 1];
        }
    }
    
    cout << "Table:" << endl;
    for (int i = 0; i <= n; ++i) {
        for (int w = 0; w <= capacity; ++w) {
            cout << dp[i][w] << " ";
        }
        cout << endl;
    }
    
    return dp[n][capacity];
}

int main() {
    vector<int> weights =   {1 ,  2 , 3 , 4 };
    vector<int> values =    {30, 10, 40, 50};
    int capacity = 5;
    vector<int> chosenItems;
    
    int result = knapsack(weights, values, capacity, chosenItems);
    
    cout << "Maximum value achievable: " << result << endl;

    cout << "Chosen items: ";
    
    for (int i = chosenItems.size() - 1; i >= 0; --i) {
        cout << chosenItems[i] + 1 << " ";
    }
    cout << endl;

    return 0;
}
