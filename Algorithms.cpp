#include "Algorithms.h"
#include "Process.h"
#include <vector>
#include <algorithm>
#include<iostream>
using namespace std;

bool compareArrival(Process p1, Process p2) {
	return (p1.arrivalTime < p2.arrivalTime);
}
bool compareID(Process p1, Process p2) {
	return (p1.id < p2.id);
}

void FCFS(vector<Process> readyQueue) {
	//sort by arrival time
	sort(readyQueue.begin(), readyQueue.end(), compareArrival);
	int totalTAT = 0;
	for (int i = 0; i < readyQueue.size(); i++) {
		//cout<<readyQueue.at(i).arrivalTime<<" ";
		if (i == 0) {
			readyQueue.at(i).startTime = readyQueue.at(i).arrivalTime;
		}
		else {
			readyQueue.at(i).startTime = max(readyQueue.at(i - 1).completionTime, readyQueue.at(i).arrivalTime);
		}
		readyQueue.at(i).completionTime = readyQueue.at(i).startTime + readyQueue.at(i).burstTime;
		readyQueue.at(i).turnaroundTime = readyQueue.at(i).completionTime - readyQueue.at(i).arrivalTime;
		totalTAT += readyQueue.at(i).turnaroundTime;
	}
	int averageTAT = totalTAT / readyQueue.size();
	//sort by Id to display 
	sort(readyQueue.begin(), readyQueue.end(), compareID);
	cout << "\nPID\tArrival Time\tStart Time\t Completion Time\tTurnaround Time\t\n";
	for (int i = 0; i < readyQueue.size(); i++) {
		cout << readyQueue.at(i).id << "\t\t" << readyQueue.at(i).arrivalTime << "\t\t" << readyQueue.at(i).startTime << "\t\t" << readyQueue.at(i).completionTime << "\t\t" << readyQueue.at(i).turnaroundTime << endl;
	}
	cout << "Average Turnaround Time: " << averageTAT << endl;


}

void Priority(vector<Process> readyQueue) {
	int totalTurnaround(0);
	float avgTurnaround;
	int timeRemaining[100];
	int isCompleted[100];
	memset(isCompleted, 0, sizeof(isCompleted));
	for (int i = 0; i < readyQueue.size(); i++) {
		timeRemaining[i] = readyQueue.at(i).burstTime;
	}
	int currentTime(0), completed(0);

	while (completed != readyQueue.size()) {
		int index(-1), max(100);
		for (int i = 0; i < readyQueue.size(); i++) {
			if (readyQueue.at(i).arrivalTime <= currentTime && isCompleted[i] == 0) {
				if (readyQueue.at(i).priority < max) {
					max = readyQueue.at(i).priority;
					index = i;
				}
				if (readyQueue.at(i).priority == max) {
					if (readyQueue.at(i).arrivalTime < readyQueue.at(index).arrivalTime) {
						max = readyQueue.at(i).priority;
						index = i;
					}
				}
			}
		}
		if (index != -1) {
			if (timeRemaining[index] == readyQueue.at(index).burstTime) {
				readyQueue.at(index).startTime = currentTime;
			}
			timeRemaining[index] -= 1;
			currentTime++;
			if (timeRemaining[index] == 0) {
				readyQueue.at(index).completionTime = currentTime;
				readyQueue.at(index).turnaroundTime = readyQueue.at(index).completionTime - readyQueue.at(index).arrivalTime;
				totalTurnaround += readyQueue.at(index).turnaroundTime;
				isCompleted[index] = 1;
				completed++;
			}
		}
		else {
			currentTime++;
		}
	}
	avgTurnaround = (float)totalTurnaround / readyQueue.size();
	cout << "\nPID\tArrival Time\tStart Time\t Completion Time\tTurnaround Time\t\n";
	for (int i = 0; i < readyQueue.size(); i++) {
		cout << readyQueue.at(i).id << "\t" << readyQueue.at(i).arrivalTime << "\t\t" << readyQueue.at(i).startTime << "\t\t" << readyQueue.at(i).completionTime << "\t\t" << readyQueue.at(i).turnaroundTime << endl;
	}

	cout << "Average Turnaround Time = " << avgTurnaround << endl;

	
}


void SJN(vector<Process> readyQueue) {
	int isCompleted[100];
	int totalTurnaround(0);
	memset(isCompleted, 0, sizeof(isCompleted));
	int currentTime(0), completed(0);


	while (completed != readyQueue.size()) {
		int index(-1), max(100);
		for (int i = 0; i < readyQueue.size(); i++) {
			if (readyQueue.at(i).arrivalTime <= currentTime && isCompleted[i] == 0) {
				if (readyQueue.at(i).burstTime < max) {
					max = readyQueue.at(i).burstTime;
					index = i;
				}
				if (readyQueue.at(i).burstTime == max) {
					if (readyQueue.at(i).arrivalTime < readyQueue.at(index).arrivalTime) {
						max = readyQueue.at(i).burstTime;
						index = i;
					}
				}
			}
		}

		if (index != -1) {
			readyQueue.at(index).startTime = currentTime;
			readyQueue.at(index).completionTime = readyQueue.at(index).startTime + readyQueue.at(index).burstTime;
			readyQueue.at(index).turnaroundTime = readyQueue.at(index).completionTime - readyQueue.at(index).arrivalTime;
			totalTurnaround += readyQueue.at(index).turnaroundTime;
			isCompleted[index] = 1;
			completed++;
			currentTime = readyQueue.at(index).completionTime;
		}

		else {
			currentTime++;
		}

	}

	float avgTurnaround;
	avgTurnaround = (float)totalTurnaround / readyQueue.size();
	cout << "\nPID\tArrival Time\tStart Time\tCompletion Time\tTurnaround Time\t\n";
	for (int i = 0; i < readyQueue.size(); i++) {
		cout << readyQueue.at(i).id << "\t" << readyQueue.at(i).arrivalTime << "\t\t" << readyQueue.at(i).startTime << "\t\t" << readyQueue.at(i).completionTime << "\t\t" << readyQueue.at(i).turnaroundTime << endl;
	}

	cout << "Average Turnaround Time = " << avgTurnaround << endl;


}
void RoundRobin(vector<Process> readyQueue) {
	cout << "TBD" << endl;
}