/*
CS221 - Lab Activity 04

4. Edit Distance
Given two strings, find the minimum number of single-character edits (insertions, deletions, substitutions)
required to transform one string into the other.

Sample Result

Input:  str1 = "kitten"
        str2 = "sitting"

Output: Minimum edit distance: 3

*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int minDistance(string word1, string word2) {
    int m = word1.size();
    int n = word2.size();
    
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    
    for (int i = 0; i <= m; ++i) {
        dp[i][0] = i;
    }
    for (int j = 0; j <= n; ++j) {
        dp[0][j] = j;
    }
    
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (word1[i - 1] == word2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = 1 + min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});
            }
        }
    }
    
    return dp[m][n];
}

int main() {
    string str1 = "kittenssss";
    string str2 = "sitting";
    
    int result = minDistance(str1, str2);
    
    cout << "Minimum edit distance: " << result << endl;

    return 0;
}
