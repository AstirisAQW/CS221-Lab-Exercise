/*
Quick Sort with Median of Three (20 points)
Implement a Divide-and-Conquer algorithm for sorting an sample_arrayay of integers using
Quick Sort with the Median of Three pivot selection strategy.

Sample Output:  Given sample_array: [8, 2, 4, 9, 1, 7, 5]
                Sorted sample_array: [1, 2, 4, 5, 7, 8, 9]


Time Complexity:    Best Case: O(n log n)
                    Average Case: O(n log n)
                    Worst Case: O(n^2)
*/

#include <iostream>
#include <vector>

using namespace std;

void swap(int& a, int& b) { // Function to swap two elements in the sample_array
    int temp = a;
    a = b;
    b = temp;
}

int median_of_three(vector<int>& sample_array, int low, int high) { // Function to find median of three elements
    int median = low + (high - low) / 2;
    
    if (sample_array[low] > sample_array[median])
        swap(sample_array[low], sample_array[median]);
    if (sample_array[median] > sample_array[high])
        swap(sample_array[median], sample_array[high]);
    if (sample_array[low] > sample_array[median])
        swap(sample_array[low], sample_array[median]);
    
    return median;
}

// Function to partition the sample_array based on the pivot
int partition(vector<int>& sample_array, int low, int high) {
    int pivotIndex = median_of_three(sample_array, low, high);
    int pivot = sample_array[pivotIndex];
    
    swap(sample_array[pivotIndex], sample_array[high]);
    
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (sample_array[j] <= pivot) {
            i++;
            swap(sample_array[i], sample_array[j]);
        }
    }
    
    swap(sample_array[i + 1], sample_array[high]);
    
    return i + 1;
}

// Function to perform Quick Sort
void quick_sort(vector<int>& sample_array, int low, int high) {
    if (low < high) {
        int pi = partition(sample_array, low, high);
        
        quick_sort(sample_array, low, pi - 1);
        quick_sort(sample_array, pi + 1, high);
    }
}

// Function to print the sample_array
void print_sample_array(vector<int>& sample_array) {
    cout << "Sorted sample_array: [";
    for (int i = 0; i < sample_array.size(); i++) {
        cout << sample_array[i];
        if (i != sample_array.size() - 1)
            cout << ", ";
    }
    cout << "]" << endl;
}

int main() {
    vector<int> sample_array = {8, 2, 4, 9, 1, 7, 5};
    int n = sample_array.size();
    
    cout << "Given sample_array: [";
    for (int i = 0; i < n; i++) {
        cout << sample_array[i];
        if (i != n - 1)
            cout << ", ";
    }
    cout << "]" << endl;
    
    quick_sort(sample_array, 0, n - 1);
    print_sample_array(sample_array);
    
    return 0;
}
