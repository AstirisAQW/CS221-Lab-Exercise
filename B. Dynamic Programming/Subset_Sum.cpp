/*
Subset Sum (20 points)
Given a set of non-negative integers and a target sum, find if there exists a subset of
the numbers that add up to the target sum. Design a dynamic programming algorithm
to solve this problem. Briefly explain the DP table construction and how to check for
the existence of a subset.

Sample Output:  Set: [3, 2, 7] Target sum: 5
                Result: True (Subset: [2, 3])

Time Complexity:    Best Case: O(n)
                    Average Case: O(n * target)
                    Worst Case: O(n * target)
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Dynamic programming approach to solve the Subset Sum problem
bool subsetSum(vector<int>& nums, int target, vector<int>& subset) {
    int n = nums.size();
    vector<vector<bool>> dp(n + 1, vector<bool>(target + 1, false));

    // Base case: when the target sum is 0, there's always an empty subset
    for (int i = 0; i <= n; ++i) {
        dp[i][0] = true;
    }

    // Dynamic programming to fill the dp table
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= target; ++j) {
            if (j >= nums[i - 1]) {
                dp[i][j] = dp[i - 1][j] || dp[i - 1][j - nums[i - 1]];
            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }

    // Reconstruct the subset
    if (dp[n][target]) {
        int i = n, j = target;
        while (i > 0 && j > 0) {
            if (dp[i][j] && !dp[i - 1][j]) {
                subset.push_back(nums[i - 1]);
                j -= nums[i - 1];
            }
            --i;
        }
        reverse(subset.begin(), subset.end());
        return true;
    }

    return false;
}

int main() {
    vector<int> nums = {3, 2, 7};
    int target = 5;
    vector<int> subset;

    cout << "Set: [";
    for (int i = 0; i < nums.size(); ++i) {
        cout << nums[i];
        if (i < nums.size() - 1) {
            cout << ", ";
        }
    }
    cout << "] \nTarget sum: " << target << endl;

    if (subsetSum(nums, target, subset)) {
        cout << "Result: True (Subset: [";
        for (int i = 0; i < subset.size(); ++i) {
            cout << subset[i];
            if (i < subset.size() - 1) {
                cout << ", ";
            }
        }
        cout << "])" << endl;
    } else {
        cout << "Result: False" << endl;
    }

    return 0;
}
