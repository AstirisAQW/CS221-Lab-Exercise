/*
CS221 - Lab Activity 03

1. Coin Change Problem:
Given denominations of coins and a target amount, find the minimum number of
coins needed to make change (using various coin combinations).

Sample Result
Input:  coins = 1, 2, 5
        amount = 11

Output: Minimum number of coins needed: 3 (using 1 coin of value 5 and 2 coins of value 2

*/

#include<bits/stdc++.h>
using namespace std;

// Function to find the minimum number of coins required to make the amount
vector<int> coinChange(int coins[], int n, int amount) {
    vector<int> dp(amount + 1, INT_MAX);
    dp[0] = 0; // Base case: 0 coins are needed to make the amount 0

    for (int i = 1; i <= amount; i++) {
        for (int j = 0; j < n; j++) {
            if (coins[j] <= i) {
                int sub_res = dp[i - coins[j]];
                if (sub_res != INT_MAX && sub_res + 1 < dp[i])
                    dp[i] = sub_res + 1;
            }
        }
    }

    // If dp[amount] is still INT_MAX, it means we cannot make the amount with the given coins
    if (dp[amount] == INT_MAX) {
        cout << "No combination can sum to " << amount << endl;
        return {};
    }

    // Reconstruct the coin combination
    vector<int> result;
    int curr_amount = amount;
    for (int i = n - 1; i >= 0; i--) {
        while (curr_amount >= coins[i] && dp[curr_amount - coins[i]] == dp[curr_amount] - 1) {
            result.push_back(coins[i]);
            curr_amount -= coins[i];
        }
    }

    return result;
}

int main() {
    int coins[] = {1, 5, 6, 9};
    int n = sizeof(coins) / sizeof(coins[0]);
    int amount = 11;

    vector<int> result = coinChange(coins, n, amount);

    // Output the minimum number of coins and the specific coin combinations
    cout << "Minimum number of coins required is " << result.size() << endl;
    cout << "Coin combinations used:" << endl;

    for (const auto& coin : result) {
        cout << coin << " ";
    }

    return 0;
}
