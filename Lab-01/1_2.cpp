#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Process {
    int id;
    int burstTime;
    int arrivalTime;
    int completionTime;
    int waitingTime;
    int turnAroundTime;
};

bool compareArrivalTime(const Process& p1, const Process& p2) {
    return p1.arrivalTime < p2.arrivalTime;
}

void calculateTimes(vector<Process>& processes) {
    int n = processes.size();
    int totalWT = 0, totalTAT = 0;
    int currentTime = 0;

    sort(processes.begin(), processes.end(), compareArrivalTime);

    for (int i = 0; i < n; i++) {
        if (currentTime < processes[i].arrivalTime) {
            currentTime = processes[i].arrivalTime;
        }
        processes[i].completionTime = currentTime + processes[i].burstTime;
        processes[i].turnAroundTime = processes[i].completionTime - processes[i].arrivalTime;
        processes[i].waitingTime = processes[i].turnAroundTime - processes[i].burstTime;
        currentTime = processes[i].completionTime;

        totalWT += processes[i].waitingTime;
        totalTAT += processes[i].turnAroundTime;
    }

    cout << "Process\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n";
    for (const auto& process : processes) {
        cout << process.id << "\t" << process.arrivalTime << "\t\t" << process.burstTime << "\t\t" << process.completionTime << "\t\t" << process.waitingTime << "\t\t" << process.turnAroundTime << "\n";
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
        cout << "Enter arrival time for process " << i+1 << ": ";
        cin >> processes[i].arrivalTime;
        cout << "Enter burst time for process " << i+1 << ": ";
        cin >> processes[i].burstTime;
    }

    calculateTimes(processes);

    return 0;
}
