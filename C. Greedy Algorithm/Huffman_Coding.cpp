/*
Huffman Coding (20 points)
Given a set of characters and their frequencies, design a Greedy algorithm for Huffman
Coding to create an optimal prefix code for lossless data compression. Explain the steps
involved in building the Huffman tree and how the code is assigned to characters.

Sample Output:  Characters: [a, b, c, d]
                Frequencies: [4, 2, 1, 3]
                Huffman Tree: (root: (b, (a, c)), d)
                Code: a: 00, b: 01, c: 10, d: 11
*/

#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>
#include <functional>
using namespace std;

// A Huffman tree node
struct Node {
    char data;
    int freq;
    Node *left, *right;

    Node(char data, int freq) : data(data), freq(freq), left(nullptr), right(nullptr) {}
};

// Comparator function for priority queue
struct CompareNodes {
    bool operator()(const Node* left, const Node* right) {
        return left->freq > right->freq;
    }
};

// Function to build Huffman tree and assign codes
void buildHuffmanTree(const vector<char>& characters, const vector<int>& frequencies) {
    priority_queue<Node*, vector<Node*>, CompareNodes> minHeap;

    // Create leaf nodes and push them into the priority queue
    for (size_t i = 0; i < characters.size(); ++i) {
        minHeap.push(new Node(characters[i], frequencies[i]));
    }

    // Construct Huffman tree
    while (minHeap.size() > 1) {
        Node* left = minHeap.top();
        minHeap.pop();

        Node* right = minHeap.top();
        minHeap.pop();

        Node* newNode = new Node('$', left->freq + right->freq);
        newNode->left = left;
        newNode->right = right;

        minHeap.push(newNode);
    }

    // Assign codes to characters
    unordered_map<char, string> codes;
    string code = "";
    Node* root = minHeap.top();

    // Traverse the Huffman tree to assign codes
    function<void(Node*, string)> assignCodes = [&](Node* node, string code) {
        if (node) {
            if (node->data != '$') {
                codes[node->data] = code;
            }
            assignCodes(node->left, code + "0");
            assignCodes(node->right, code + "1");
        }
    };

    // Start assigning codes from root
    assignCodes(root, code);

    // Print codes
    cout << "Huffman Tree: ";
    cout << "(" << root->data << ": " << codes[root->data] << ")" << endl;
    cout << "Codes:" << endl;
    for (size_t i = 0; i < characters.size(); ++i) {
        cout << characters[i] << ": " << codes[characters[i]] << endl;
    }

    // Clean up memory
    delete root;
}

int main() {
    vector<char> characters = {'a', 'b', 'c', 'd'};
    vector<int> frequencies = {4, 2, 1, 3};

    buildHuffmanTree(characters, frequencies);

    return 0;
}