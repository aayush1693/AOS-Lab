#include <bits/stdc++.h>

using namespace std;

struct Process {
    int id;
    int burstTime;
    int waitingTime;
    int turnaroundTime;
};

bool compareBurstTime(Process a, Process b) {
    return a.burstTime < b.burstTime;
}

void calculateWaitingTime(vector<Process> &processes) {
    processes[0].waitingTime = 0;
    for (size_t i = 1; i < processes.size(); ++i) {
        processes[i].waitingTime = processes[i - 1].waitingTime + processes[i - 1].burstTime;
    }
}

void calculateTurnaroundTime(vector<Process> &processes) {
    for (auto &process : processes) {
        process.turnaroundTime = process.waitingTime + process.burstTime;
    }
}

void printResults(const vector<Process> &processes) {
    double totalWaitingTime = 0, totalTurnaroundTime = 0;
    cout << "Process ID\tBurst Time\tWaiting Time\tTurnaround Time\n";
    for (const auto &process : processes) {
        cout << process.id << "\t\t" << process.burstTime << "\t\t" << process.waitingTime << "\t\t" << process.turnaroundTime << endl;
        totalWaitingTime += process.waitingTime;
        totalTurnaroundTime += process.turnaroundTime;
    }
    cout << "Average Waiting Time: " << totalWaitingTime / processes.size() << endl;
    cout << "Average Turnaround Time: " << totalTurnaroundTime / processes.size() << endl;
}

int main() {
    int numProcesses;
    cout << "Enter the number of processes: ";
    cin >> numProcesses;

    vector<Process> processes(numProcesses);

    for (int i = 0; i < numProcesses; ++i) {
        processes[i].id = i + 1;
        cout << "Enter burst time for process " << i + 1 << ": ";
        cin >> processes[i].burstTime;
    }

    sort(processes.begin(), processes.end(), compareBurstTime);

    calculateWaitingTime(processes);
    calculateTurnaroundTime(processes);

    printResults(processes);

    return 0;
}
