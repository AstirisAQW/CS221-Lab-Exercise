/*
Job Scheduling with Deadlines (20 points)
You are given a set of jobs with weights and deadlines. The goal is to schedule the
maximum number of jobs such that each job is completed before its deadline. Design
a Greedy algorithm to solve this problem. Briefly explain the logic behind selecting
jobs and its impact on feasibility.

Sample Output:  Jobs: (weight, deadline) - (2, 1), (5, 2), (4, 1), (6, 3)
                Maximum jobs: 3 (Selection: (2, 1), (5, 2), (6, 3))
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Job {
    int weight;
    int deadline;

    Job(int w, int d) : weight(w), deadline(d) {}

    bool operator<(const Job& other) const {
        if (weight == other.weight) {
            return deadline > other.deadline; // Sort by decreasing deadline if weights are equal
        }
        return weight > other.weight; // Sort by decreasing weight
    }
};

void jobScheduling(vector<Job>& jobs) {
    sort(jobs.begin(), jobs.end());

    int maxJobs = 0;
    vector<Job> selectedJobs;

    vector<bool> slot(jobs.size(), false);

    for (const auto& job : jobs) {
        for (int i = min((int)jobs.size(), job.deadline) - 1; i >= 0; --i) {
            if (!slot[i]) {
                selectedJobs.push_back(job);
                slot[i] = true;
                ++maxJobs;
                break;
            }
        }
    }

    cout << "Jobs: (weight, deadline) -";
    for (const auto& job : jobs) {
        cout << " (" << job.weight << ", " << job.deadline << ")";
    }
    cout << endl;
    cout << "Maximum jobs: " << maxJobs << " (Selection:";
    for (const auto& job : selectedJobs) {
        cout << " (" << job.weight << ", " << job.deadline << ")";
    }
    cout << ")" << endl;
}

int main() {
    vector<Job> jobs = {{2, 1}, {5, 2}, {4, 1}, {6, 3}};
    jobScheduling(jobs);

    return 0;
}