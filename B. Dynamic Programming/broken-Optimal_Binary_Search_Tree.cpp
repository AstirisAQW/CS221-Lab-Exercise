/*
Optimal Binary Search Tree (20 points)
Given a sequence of keys and their access frequencies, construct the optimal binary
search tree that minimizes the total access cost (considering search frequency). Design
a dynamic programming algorithm to solve this problem. Briefly explain the DP table
construction and how to find the optimal tree structure.

Sample Output:  Keys: [A, B, C, D]
                Frequencies: [2, 3, 1, 4]
                Optimal BST: (root: B, left: A, right: (C, right: D))
*/
#include <iostream>
#include <climits>
using namespace std;

// A utility function to get sum of array elements freq[i] to freq[j]
int sum(int freq[], int i, int j) {
    int s = 0;
    for (int k = i; k <= j; k++)
        s += freq[k];
    return s;
}

// A recursive function to calculate cost of optimal binary search tree
int optCost(int freq[], int i, int j, int& root_index) {
    // Base cases
    if (j < i) // no elements in this subarray
        return 0;
    if (j == i) { // one element in this subarray
        root_index = i;
        return freq[i];
    }

    // Get sum of freq[i], freq[i+1], ... freq[j]
    int fsum = sum(freq, i, j);

    // Initialize minimum value
    int min = INT_MAX;

    // One by one consider all elements as root and recursively find cost of the BST,
    // compare the cost with min and update min if needed
    for (int r = i; r <= j; ++r) {
        int left_root, right_root;
        int cost = optCost(freq, i, r - 1, left_root) + optCost(freq, r + 1, j, right_root) + fsum;
        if (cost < min) {
            min = cost;
            root_index = r;
        }
    }

    // Return minimum value
    return min;
}

// The main function that calculates minimum cost of a Binary Search Tree.
// It mainly uses optCost() to find the optimal cost.
int optimalSearchTree(char keys[], int freq[], int n) {
    int root_index;
    // Here array keys[] is assumed to be sorted in increasing order.
    // If keys[] is not sorted, then add code to sort keys, and rearrange freq[] accordingly.
    return optCost(freq, 0, n - 1, root_index);
}

// A utility function to print the structure of the optimal BST
void printOptimalBST(char keys[], int freq[], int i, int j, int parent_index) {
    if (i <= j) {
        if (parent_index == -1)
            cout << "root: " << keys[parent_index] << ", ";
        else
            cout << (keys[parent_index] < keys[j] ? "left" : "right") << ": " << keys[parent_index] << ", ";
        
        if (i == j)
            cout << keys[i];
        else {
            int root_index = -1;
            optCost(freq, i, j, root_index);
            printOptimalBST(keys, freq, i, root_index - 1, root_index);
            cout << ", ";
            printOptimalBST(keys, freq, root_index + 1, j, root_index);
        }
    }
}

int main() {
    char keys[] = {'A', 'B', 'C', 'D'};
    int freq[] = {2, 3, 1, 4};
    int n = sizeof(keys) / sizeof(keys[0]);
    cout << "Keys: [";
    for (int i = 0; i < n; i++) {
        cout << keys[i];
        if (i < n - 1) cout << ", ";
    }
    cout << "] Frequencies: [";
    for (int i = 0; i < n; i++) {
        cout << freq[i];
        if (i < n - 1) cout << ", ";
    }
    cout << "]" << endl;

    int cost = optimalSearchTree(keys, freq, n);
    cout << "Optimal BST: (";
    printOptimalBST(keys, freq, 0, n - 1, -1);
    cout << ")" << endl;
    cout << "Cost of Optimal BST is " << cost;

    return 0;
}
