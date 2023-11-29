#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string.h>
using namespace std;

//SJN

struct process_t {
	int pid;
	int arrivalTime;
	int burstTime;
	int startTime;
	int completionTime;
	int turnaroundTime;
};

int main() {

	cout << "\nShortest Job First\n";
	int size;
	struct process_t processes[100];
	int totalTurnaround(0);
	float avgTurnaround;
	int isCompleted[100];
	memset(isCompleted, 0, sizeof(isCompleted));
	cout << "Enter number of processes: ";
	cin >> size;
	cout << endl;
	for (int i = 0; i < size; i++) {

		cout << "Enter arrival time of process " << i << ": ";
		cin >> processes[i].arrivalTime;
		cout << "Enter execution time of process " << i << ": ";
		cin >> processes[i].burstTime;
		processes[i].pid = i;
		cout << endl;
	}

	int currentTime(0), completed(0);
	while (completed != size) {
		int index(-1), max(100);
		for (int i = 0; i < size; i++) {
			if (processes[i].arrivalTime <= currentTime && isCompleted[i] == 0) {
				if (processes[i].burstTime < max) {
					max = processes[i].burstTime;
					index = i;
				}
				if (processes[i].burstTime == max) {
					if (processes[i].arrivalTime < processes[index].arrivalTime) {
						max = processes[i].burstTime;
						index = i;
					}
				}
			}
		}

		if (index != -1) {
			processes[index].startTime = currentTime;
			processes[index].completionTime = processes[index].startTime + processes[index].burstTime;
			processes[index].turnaroundTime = processes[index].completionTime - processes[index].arrivalTime;
			totalTurnaround += processes[index].turnaroundTime;
			isCompleted[index] = 1;
			completed++;
			currentTime = processes[index].completionTime;
		}

		else {
			currentTime++;
		}

	}

	avgTurnaround = (float)totalTurnaround / size;
	cout << "\nPID\tArrival Time\tStart Time\tCompletion Time\tTurnaround Time\t\n";
	for (int i = 0; i < size; i++) {
		cout << processes[i].pid << "\t" << processes[i].arrivalTime << "\t\t" << processes[i].startTime << "\t\t" << processes[i].completionTime << "\t\t" << processes[i].turnaroundTime << endl;
	}

	cout << "Average Turnaround Time = " << avgTurnaround << endl;

	return 0;
}