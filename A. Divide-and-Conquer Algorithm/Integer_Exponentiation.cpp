/*
Integer Exponentiation (20 points)
Design a Divide-and-Conquer algorithm to compute a^b (a raised to the power of b)
efficiently. Explain each step of the algorithm and analyze its time complexity
compared to a naive approach (repeated multiplication).

Sample Output:  Compute 3^5
                Result: 243

Time Complexity:    Best Case: O(1)
                    Average Case: O()
                    Worst Case: O()

Time Complexity of Naive Approach: O(n)

*/

#include <iostream>

using namespace std;

// Function to compute a^b using Divide-and-Conquer algorithm
int power(int a, int b) {

    if (b == 0)    // Base case
        return 1;
    
    int temp = power(a, b / 2);    // Recursive steps
    int result = temp * temp;
    
    if (b % 2 != 0)    // If b is odd, multiply by a one more time
        result *= a;
    
    return result;
}

int main() {
    int a = 3, b = 5;
    cout << "Compute " << a << "^" << b << endl;
    cout << "Result: " << power(a, b) << endl;
    return 0;
}
