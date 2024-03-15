/*
CS221 - Lab Activity 02

2. Longest Common Subsequence (LCS)
Given two strings, find the longest subsequence that appears in both strings in the same order.
Sample Result

Input:  text1 = "AGGTAB"
        text2 = "GXTXAYB”

Output: Length of Longest Common Subsequence: 4

*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int longestCommonSubsequence(string text1, string text2) {
    int m = text1.size();
    int n = text2.size();
    
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (text1[i - 1] == text2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    
    return dp[m][n];
}

int main() {
    string text1 = "AGGTAB";
    string text2 = "GXTXAYB";
    
    int result = longestCommonSubsequence(text1, text2);
    
    cout << "Length of Longest Common Subsequence: " << result << endl;

    return 0;
}
