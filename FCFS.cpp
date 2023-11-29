#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

//FCFS

struct process_t {
	int pid;
	int arrivalTime;
	int burstTime;
	int startTime;
	int completionTime;
	int turnaroundTime;
};

bool compareArrivals(process_t p1, process_t p2) { return p1.arrivalTime < p2.arrivalTime; }
bool compareID(process_t p1, process_t p2) { return p1.pid < p2.pid; }
int main() {
	int input;
	struct process_t processes[100];
	float avgTurnaround;
	int totalTurnaround(0);
	cout << "\n***FCFS***\n\n";
	cout << "Enter number of processes: ";
	cin >> input;
	cout << endl;
	for (int i = 0; i < input; i++) {
		cout << "Enter arrival time of process " << i << ": ";
		cin >> processes[i].arrivalTime;
		cout << "Enter execution time of process " << i << ": ";
		cin >> processes[i].burstTime;
		processes[i].pid = i;
		cout << endl;
	}

	sort(processes, processes + input, compareArrivals);
	for (int i = 0; i < input; i++) {
		if (i == 0) {
			processes[i].startTime = processes[i].arrivalTime;
		}
		else {
			processes[i].startTime = max(processes[i - 1].completionTime, processes[i].arrivalTime);
		}

		processes[i].completionTime = processes[i].startTime + processes[i].burstTime;
		processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
		totalTurnaround += processes[i].turnaroundTime;
	}

	avgTurnaround = (float)totalTurnaround / input;
	sort(processes, processes + input, compareID);
	cout << "\nPID\tArrival Time\tStart Time\t Completion Time\tTurnaround Time\t\n";
	for (int i = 0; i < input; i++) {
		cout << processes[i].pid << "\t\t" << processes[i].arrivalTime << "\t\t" << processes[i].startTime << "\t\t" << processes[i].completionTime << "\t\t" << processes[i].turnaroundTime << endl;
	}

	cout << "Average Turnaround Time = " << avgTurnaround << endl;
	return 0;
}