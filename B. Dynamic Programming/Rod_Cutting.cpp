/*
Rod Cutting (20 points)
You have a rod of length n that can be cut into pieces of lengths p1, p2, ..., pn. Each
piece of length pi has a price pi. Design a dynamic programming algorithm to find the
maximum revenue obtainable by cutting the rod into pieces.

Sample Output:  Rod length: 5
                Prices: (1, 2, 3, 4)
                Maximum revenue: 6 (Cut: 2 pieces of length 2)

*/

#include <iostream>
#include <vector>
#include <climits>
using namespace std;

// Function to calculate the maximum revenue obtainable by cutting the rod
int cutRod(int price[], int n) {
    // Initialize a table to store maximum revenue for rods of all lengths
    vector<int> revenue(n + 1, 0);

    // Iterate through rod lengths from 1 to n
    for (int i = 1; i <= n; ++i) {
        // Consider all possible cut lengths for the current rod
        for (int j = 1; j <= i; ++j) {
            // Calculate the potential revenue by cutting the rod into a piece of
            // length j and selling the remaining piece
            int potentialRevenue = price[j - 1] + revenue[i - j];

            // Update the table entry if the potential revenue is higher
            revenue[i] = max(revenue[i], potentialRevenue);
        }
    }

    return revenue[n]; // Return the maximum revenue for the entire rod
}

int main() {
    int n = 5; // Rod length (pre-defined)
    int prices[] = {1, 2, 3, 4, 5}; // Prices for lengths 1 to 5 (pre-defined)

    // Calculate and print the maximum revenue
    int maxRevenue = cutRod(prices, n);

    cout << "Rod length: " << n << endl;
    cout << "Prices: (";
    for (int i = 0; i < n; ++i) {
        cout << prices[i];
        if (i != n - 1) {
            cout << ", ";
        }
    }
    cout << ")" << endl;
    cout << "Maximum revenue: " << maxRevenue << endl;

    return 0;
}