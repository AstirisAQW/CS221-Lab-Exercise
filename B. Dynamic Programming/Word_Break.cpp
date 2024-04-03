/*
Word Break (20 points)
Given a dictionary of words and a string, determine if the string can be segmented into
space-separated sequences (words) that exist in the dictionary. Design a dynamic
programming algorithm to solve this problem. Briefly explain the DP table construction
and how to check for possible segmentation.

Sample Output:  Dictionary: ["apple", "pear", "pie"] String: "applepie"
                Result: True ("apple pie")

Time Complexity:    Best Case:      O(n)
                    Average Case:   O(n^3 * m)
                    Worst Case:     O(n^3 * m)
*/
#include <iostream>
#include <unordered_set>
#include <vector>
#include <string>

using namespace std;

bool wordBreak(string s, unordered_set<string>& wordDict) {
    int n = s.length();
    vector<bool> dp(n + 1, false);

    dp[0] = true;

    // Dynamic programming approach to determine if the string can be segmented
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < i; j++) {
            if (dp[j] && wordDict.find(s.substr(j, i - j)) != wordDict.end()) {
                dp[i] = true;
                break;
            }
        }
    }

    return dp[n];
}

// Helper function to recursively reconstruct the segmented string
void reconstructString(string& s, unordered_set<string>& wordDict, string& result, int start) {
    if (start == s.length()) {
        result.pop_back(); // Remove the extra space at the end
        return;
    }

    for (int i = start; i < s.length(); i++) {
        string prefix = s.substr(start, i - start + 1);
        if (wordDict.find(prefix) != wordDict.end()) {
            string tempResult = result;
            tempResult += prefix + " ";
            reconstructString(s, wordDict, tempResult, i + 1);
            if (wordBreak(s.substr(i + 1), wordDict)) {
                result = tempResult;
            }
        }
    }
}

int main() {
    string s = "applepie";
    unordered_set<string> wordDict = {"apple", "pear", "pie"};

    cout << "Dictionary: ";
    for (const string& word : wordDict) {
        cout << word << " ";
    }
    cout << "\nString: " << s << "\nResult: ";

    if (wordBreak(s, wordDict)) {
        string result = "";
        reconstructString(s, wordDict, result, 0);
        cout << "True (\"" << result << "\")";
    } else {
        cout << "False";
    }

    cout << endl;

    return 0;
}
