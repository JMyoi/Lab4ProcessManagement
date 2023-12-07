#include <iostream>
#include "Algorithms.h"
#include "Process.h"
#include <vector>
#include <algorithm>
#include <cstring>
#include <limits.h>
using namespace std;

bool compareArrival(Process p1, Process p2) {
	return (p1.arrivalTime < p2.arrivalTime);
}
bool compareID(Process p1, Process p2) {
	return (p1.id < p2.id);
}



void SRTF(vector<Process> readyQueue) {
    int isCompleted[100], remainingTime[100];
	//set all elements in isCompleted to 0 to indicate not completed yet
    memset(isCompleted, 0, sizeof(isCompleted));
	//set the remaining time of all processes into the remainingTime array based on the burst time of the respective elements.
    for (int i = 0; i < readyQueue.size(); i++) {
        remainingTime[i] = readyQueue[i].burstTime;
    }

	//completed indicated the number of processes that are completed
    int totalTurnaround = 0, currentTime = 0, completed = 0;
	//used in the CPU efficiency calculation
	int totalSwitchingTime = 0;

	//previous process is used to keep track of the process that previously went. this is used to see if there was a switch in process from previous 
	//process if it is then we will have to increment currentTime +2 because that is how long it takes to switch based on the requirements.
	int previousProcess = 0;

	//while all the processes are not completed yet.
    while (completed != readyQueue.size()) {
        int index = -1;
        int min = INT_MAX;

		//get the smallest burst time our of all the processes that are currently in queue at current time.
        for (int i = 0; i < readyQueue.size(); i++) {
			//if it has not in the queue at this current time and not completed 
            if (readyQueue[i].arrivalTime <= currentTime && isCompleted[i] == 0) {
                if (remainingTime[i] < min) {
                    min = remainingTime[i];
                    index = i;
					//if its not the start of the program then set the prev process to be the smallest process.
					if(currentTime!=0){
						previousProcess = i;
					}
                }
            }
        }
		//if the process we are going to run is not the previous one that means that there was a preemtive switch which takes 2 tics.
		if(index!=previousProcess){
			currentTime+=2;
			totalSwitchingTime+=2;
			cout<<"switching process's\n";
		}

		//if it is -1 then that means there are no processes in this current time.
        if (index != -1) {
			//if it has no start time then set this process's start time to the current time.
            if (readyQueue[index].startTime == -1) {
                readyQueue[index].startTime = currentTime;
            }
            remainingTime[index]--;
            currentTime++;
			//increment the process's service time
			readyQueue.at(index).ServiceTime++;

			//for every process that is in the queue at this current time other than the one currently worked on increase the wait time by 1
			 for (int i = 0; i < readyQueue.size(); i++) {
				//if it has not in the queue at this current time and not completed 
				if (readyQueue[i].arrivalTime <= currentTime && isCompleted[i] == 0) {
					if(i!=index){
						readyQueue.at(i).waitTime++;
					}
				}
			}
			
			
			//if the process is finished then set the appropirate data for the process to indicate that it is finished. 
            if (remainingTime[index] == 0) {
                readyQueue[index].completionTime = currentTime;
                readyQueue[index].turnaroundTime = readyQueue[index].completionTime - readyQueue[index].arrivalTime;
                totalTurnaround += readyQueue[index].turnaroundTime;
                isCompleted[index] = 1;
                completed++;
            }
        } else {
            currentTime++;
			//for every process other than the one currently worked on increase the wait time by 1
			for(int i = 0; i < readyQueue.size(); i++){
				if(i!=index){
					readyQueue.at(i).waitTime++;
				}
			}

        }
    }

	cout<<"Total time: "<<currentTime<<endl;

	//average wait time start time - arrival time
	int totalWaitTime = 0;
	for(int i = 0; i < readyQueue.size(); i++){
		totalWaitTime+=readyQueue.at(i).waitTime;
	}
	int avgWaitTime = totalWaitTime/readyQueue.size();
	cout<<"Average Waiting Time: "<<avgWaitTime<<endl;

	//calculate avg turnaround time
    float avgTurnaround = (float)totalTurnaround / readyQueue.size();
	cout << "Average Turnaround Time = " << avgTurnaround << endl;

	//CPU efficiencycout
	cout<<"total Switching time for CPU calculaiton: "<< totalSwitchingTime <<endl;
	double CPUefficiency = (double)currentTime / (currentTime + totalSwitchingTime);
	cout<<"CPU Efficiency: "<<CPUefficiency<<"%\n";

	cout << "\nPID\tService Time\tTurnaround Time\tStart Time\tCompletion Time";
	for (int i = 0; i < readyQueue.size(); i++) {
        cout << readyQueue[i].id << "\t  " 
		<<  readyQueue.at(i).completionTime - readyQueue.at(i).arrivalTime - readyQueue.at(i).waitTime <<"\t\t   "
		<< readyQueue[i].turnaroundTime << "\t\t" 
        << readyQueue[i].startTime << "\t\t"
		<< readyQueue[i].completionTime 
        << endl;
    }
	// cout << "\nPID\tService Time (deep count ver)\n";
	// for (int i = 0; i < readyQueue.size(); i++) {
    //     cout << readyQueue[i].id << "\t" 
	// 	<< readyQueue[i].ServiceTime << "\t"
	// 	<< endl;
    // }
    // cout << "\nPID\tArrival Time\tStart Time\tCompletion Time\tTurnaround Time\n";
    // for (int i = 0; i < readyQueue.size(); i++) {
    //     cout << readyQueue[i].id << "\t" << readyQueue[i].arrivalTime << "\t\t" 
    //          << readyQueue[i].startTime << "\t\t" << readyQueue[i].completionTime 
    //          << "\t\t" << readyQueue[i].turnaroundTime << endl;
    // }

    
}















void SJN(vector<Process> readyQueue) {
	int isCompleted[500];
	int totalTurnaround(0);
	memset(isCompleted, 0, sizeof(isCompleted));
	int currentTime(0), completed(0);


	while (completed != readyQueue.size()) {
		int index(-1), max(500);
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
