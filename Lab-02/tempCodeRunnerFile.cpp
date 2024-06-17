#include <bits/stdc++.h>

using namespace std;

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int waitingTime;
    int turnaroundTime;
};

void calculateWaitingTime(vector<Process> &processes, int currentTime) {
    for (auto &process : processes) {
        process.waitingTime = process.turnaroundTime - process.burstTime;
    }
}

void calculateTurnaroundTime(vector<Process> &processes) {
    for (auto &process : processes) {
        process.turnaroundTime = process.waitingTime + process.burstTime;
    }
}

void printResults(const vector<Process> &processes) {
    double totalWaitingTime = 0, totalTurnaroundTime = 0;
    cout << "Process ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n";
    for (const auto &process : processes) {
        cout << process.id << "\t\t" << process.arrivalTime << "\t\t" << process.burstTime << "\t\t" << process.waitingTime << "\t\t" << process.turnaroundTime << endl;
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
        cout << "Enter arrival time for process " << i + 1 << ": ";
        cin >> processes[i].arrivalTime;
        cout << "Enter burst time for process " << i + 1 << ": ";
        cin >> processes[i].burstTime;
        processes[i].remainingTime = processes[i].burstTime;
    }

    int currentTime = 0, completedProcesses = 0, minRemainingTime = INT_MAX, shortest = 0;
    bool found = false;

    while (completedProcesses != numProcesses) {
        for (int i = 0; i < numProcesses; ++i) {
            if ((processes[i].arrivalTime <= currentTime) && (processes[i].remainingTime < minRemainingTime) && processes[i].remainingTime > 0) {
                minRemainingTime = processes[i].remainingTime;
                shortest = i;
                found = true;
            }
        }

        if (!found) {
            currentTime++;
            continue;
        }

        processes[shortest].remainingTime--;

        minRemainingTime = processes[shortest].remainingTime;
        if (minRemainingTime == 0) {
            minRemainingTime = INT_MAX;
        }

        if (processes[shortest].remainingTime == 0) {
            completedProcesses++;
            processes[shortest].turnaroundTime = currentTime + 1 - processes[shortest].arrivalTime;
        }
        currentTime++;
    }

    calculateWaitingTime(processes, currentTime);
    calculateTurnaroundTime(processes);

    printResults(processes);

    return 0;
}
