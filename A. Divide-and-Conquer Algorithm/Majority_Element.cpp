/*
Majority Element (20 points)
Given an array of integers, where one element appears more than half the times, find
that element. Design a Divide-and-Conquer algorithm to solve this problem. Briefly
explain the logic behind the approach and analyze its time complexity.

Sample Output:  Given array: [3, 2, 3, 1, 3, 4, 3, 8, 3]
                Majority element: 3 (appears 5 times)

Time Complexity:    Best Case: O(1)
                    Average Case: O()
                    Worst Case: O()

*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Function to find the majority element in an array using Divide-and-Conquer
int DCME(vector<int>& arr, int left, int right) {
    if (left == right) {
        return arr[left];
    }

    int mid = (left + right) / 2;
    int leftME = DCME(arr, left, mid);
    int rightME = DCME(arr, mid + 1, right);

    if (leftME == rightME) {
        return leftME;
    }

    int leftCount = count(arr.begin(), arr.end(), leftME);
    int rightCount = count(arr.begin(), arr.end(), rightME);

    return (leftCount > rightCount) ? leftME : rightME;
}

// Function to find the majority element in an array
int findMajority(vector<int>& arr) {
    int n = arr.size();
    return DCME(arr, 0, n - 1);
}

int main() {
    vector<int> arr = {3, 5, 3, 3, 4, 3};
    int result = findMajority(arr);
    cout << "Majority element in the array is " << result << endl;

    return 0;
}