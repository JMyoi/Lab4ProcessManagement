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

}
void SJN(vector<Process> readyQueue) {

}
void RoundRobin(vector<Process> readyQueue) {

}