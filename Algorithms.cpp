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



void SRTF(vector<Process> readyQueue) {
    int isCompleted[100], remainingTime[100];
    memset(isCompleted, 0, sizeof(isCompleted));
    for (int i = 0; i < readyQueue.size(); i++) {
        remainingTime[i] = readyQueue[i].burstTime;
    }

    int totalTurnaround = 0, currentTime = 0, completed = 0;

    while (completed != readyQueue.size()) {
        int index = -1;
        int min = INT_MAX;

        for (int i = 0; i < readyQueue.size(); i++) {
            if (readyQueue[i].arrivalTime <= currentTime && isCompleted[i] == 0) {
                if (remainingTime[i] < min) {
                    min = remainingTime[i];
                    index = i;
                }
            }
        }

        if (index != -1) {
            if (readyQueue[index].startTime == -1) {
                readyQueue[index].startTime = currentTime;
            }
            remainingTime[index]--;
            currentTime++;

            if (remainingTime[index] == 0) {
                readyQueue[index].completionTime = currentTime;
                readyQueue[index].turnaroundTime = readyQueue[index].completionTime - readyQueue[index].arrivalTime;
                totalTurnaround += readyQueue[index].turnaroundTime;
                isCompleted[index] = 1;
                completed++;
            }
        } else {
            currentTime++;
        }
    }

    float avgTurnaround = (float)totalTurnaround / readyQueue.size();
    cout << "\nPID\tArrival Time\tStart Time\tCompletion Time\tTurnaround Time\n";
    for (int i = 0; i < readyQueue.size(); i++) {
        cout << readyQueue[i].id << "\t" << readyQueue[i].arrivalTime << "\t\t" 
             << readyQueue[i].startTime << "\t\t" << readyQueue[i].completionTime 
             << "\t\t" << readyQueue[i].turnaroundTime << endl;
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
