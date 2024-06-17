#include <iostream>
#include <vector>

using namespace std;

struct Process {
    int id;
    int burstTime;
    int completionTime;
    int waitingTime;
    int turnAroundTime;
};

void calculateTimes(vector<Process>& processes) {
    int n = processes.size();
    int totalWT = 0, totalTAT = 0;

    // Calculating completion time for each process
    processes[0].completionTime = processes[0].burstTime;

    for (int i = 1; i < n; i++) {
        processes[i].completionTime = processes[i-1].completionTime + processes[i].burstTime;
    }

    // Calculating TAT and WT for each process
    for (int i = 0; i < n; i++) {
        processes[i].turnAroundTime = processes[i].completionTime;
        processes[i].waitingTime = processes[i].turnAroundTime - processes[i].burstTime;
        totalWT += processes[i].waitingTime;
        totalTAT += processes[i].turnAroundTime;
    }

    cout << "Process\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n";
    for (const auto& process : processes) {
        cout << process.id << "\t" << process.burstTime << "\t\t" << process.completionTime << "\t\t" << process.waitingTime << "\t\t" << process.turnAroundTime << "\n";
    }

    cout << "\nAverage Waiting Time: " << (float)totalWT / n << "\n";
    cout << "Average Turnaround Time: " << (float)totalTAT / n << "\n";
}

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    for (int i = 0; i < n; i++) {
        processes[i].id = i+1;
        cout << "Enter burst time for process " << i+1 << ": ";
        cin >> processes[i].burstTime;
    }

    calculateTimes(processes);

    return 0;
}
