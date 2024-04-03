/*
Activity Selection Problem (20 points)
You are given a set of activities with start and end times. The goal is to select the
maximum number of activities that do not conflict (no two activities overlap in time).
Design a Greedy algorithm to solve this problem. Briefly explain the logic behind
selecting activities and its impact on feasibility.

Sample Output:  Activities: (start, end) - (1, 2), (3, 4), (0, 6), (5, 7), (8, 9)
                Maximum activities: 3
                Selection: (1, 2), (3, 4), (8, 9)

*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Activity {
    int start, end;
    Activity(int s, int e) : start(s), end(e) {}
};

bool compareEnd(const Activity& a, const Activity& b) {
    return a.end < b.end;
}

void selectActivities(vector<Activity>& activities) {
    sort(activities.begin(), activities.end(), compareEnd);
    
    vector<Activity> selected;
    selected.push_back(activities[0]);
    
    for (int i = 1; i < activities.size(); ++i) {
        if (activities[i].start >= selected.back().end) {
            selected.push_back(activities[i]);
        }
    }
    
    cout << "Maximum activities: " << selected.size() << endl;
    cout << "Selection:";
    for (const auto& activity : selected) {
        cout << " (" << activity.start << ", " << activity.end << ")";
    }
    cout << endl;
}

int main() {
    vector<Activity> activities = {{1, 2}, {3, 4}, {0, 6}, {5, 7}, {8, 9}};
    
    cout << "Activities: (start, end) -";
    for (const auto& activity : activities) {
        cout << " (" << activity.start << ", " << activity.end << ")";
    }
    cout << endl;
    
    selectActivities(activities);
    
    return 0;
}
