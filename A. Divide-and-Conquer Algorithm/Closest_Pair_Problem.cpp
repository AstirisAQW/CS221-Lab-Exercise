/*
Closest Pair Problem (20 points)
Given a set of n points in the plane, find the pair of points with the minimum distance
between them. Describe a Divide-and-Conquer algorithm to solve this problem.

Sample Output:  Given points: [(2, 3), (12, 30), (4, 1), (7, 16), (5, 5)]
                Closest pair: (2, 3) and (4, 1) with distance = sqrt(5)

Time Complexity:    Best Case: O(n log n)
                    Average Case: O(n log n)
                    Worst Case: O(n log n)
*/

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct Point {
    int x, y;
};

// Function to calculate the distance between two points
double distance(Point p1, Point p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

// Function to compare points based on their x-coordinates
bool compareX(Point p1, Point p2) {
    return p1.x < p2.x;
}

// Function to compare points based on their y-coordinates
bool compareY(Point p1, Point p2) {
    return p1.y < p2.y;
}

// Function to find the minimum distance between two points in a given vector of points
double closestPairUtil(vector<Point>& points, int left, int right) {
    if (right - left <= 3) {
        double minDist = numeric_limits<double>::max();
        for (int i = left; i < right; ++i) {
            for (int j = i + 1; j < right; ++j) {
                minDist = min(minDist, distance(points[i], points[j]));
            }
        }
        return minDist;
    }

    int mid = (left + right) / 2;
    double dLeft = closestPairUtil(points, left, mid);
    double dRight = closestPairUtil(points, mid, right);
    double d = min(dLeft, dRight);

    vector<Point> strip;
    for (int i = left; i < right; ++i) {
        if (abs(points[i].x - points[mid].x) < d) {
            strip.push_back(points[i]);
        }
    }

    sort(strip.begin(), strip.end(), compareY);

    double minStrip = d;
    for (size_t i = 0; i < strip.size(); ++i) {
        for (size_t j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) < minStrip; ++j) {
            minStrip = min(minStrip, distance(strip[i], strip[j]));
        }
    }

    return min(d, minStrip);
}

// Function to find the closest pair of points in a given vector of points
void closestPair(vector<Point>& points) {
    sort(points.begin(), points.end(), compareX);
    double minDist = closestPairUtil(points, 0, points.size());
    cout << "Closest pair: ";
    for (int i = 0; i < points.size(); ++i) {
        for (int j = i + 1; j < points.size(); ++j) {
            if (distance(points[i], points[j]) == minDist) {
                cout << "(" << points[i].x << ", " << points[i].y << ") and (" 
                     << points[j].x << ", " << points[j].y << ") with distance = " 
                     << minDist << endl;
                return;
            }
        }
    }
}

int main() {
    vector<Point> points = {{2, 3}, {12, 30}, {4, 1}, {7, 16}, {5, 5}};
    cout << "Given points: [";
    for (int i = 0; i < points.size(); ++i) {
        cout << "(" << points[i].x << ", " << points[i].y << ")";
        if (i != points.size() - 1)
            cout << ", ";
    }
    cout << "]" << endl;

    closestPair(points);
    
    return 0;
}
