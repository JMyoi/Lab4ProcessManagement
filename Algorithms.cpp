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
			//if it is not in the queue at this current time and not completed 
            if (readyQueue[i].arrivalTime <= currentTime && isCompleted[i] == 0) {
                if (remainingTime[i] < min) {
                    min = remainingTime[i];
                    index = i;
                }
            }
        }

		if(currentTime == 0){
			previousProcess = index;
		}
		//if the process we are going to run is not the previous one that means that there was a preemtive switch which takes 2 tics.
		if(index!=previousProcess){
			currentTime+=2;
			totalSwitchingTime+=2;
			//since all processes are at a halt because of the switch every process that is in the queue and not complete yet increments their wait time by 2
			for(int i = 0; i<readyQueue.size(); i++){
				if (readyQueue[i].arrivalTime <= currentTime && isCompleted[i] == 0){
				readyQueue.at(i).waitTime+=2;
				}
			}
		}
		//if its not the start of the program then set the prev process to be the smallest process.
		previousProcess = index;
					

		//if it is -1 then that means there are no processes in this current time.
        if (index != -1) {
			//if it has no start time then set this process's start time to the current time.
            if (readyQueue[index].startTime == -1) {
                readyQueue[index].startTime = currentTime;
            }
            remainingTime[index]--;
            currentTime++;
			//increment the process's service time

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
			//for every process other than the one currently worked that is in the queue or not finished  increase the wait time by 1
			for(int i = 0; i < readyQueue.size(); i++){
				if(i!=index && readyQueue[i].arrivalTime <= currentTime && isCompleted[i] == 0){
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

	//CPU efficiency
	cout<<"total Switching time for CPU calculaiton: "<< totalSwitchingTime <<endl;
	double CPUefficiency = (double)currentTime / (currentTime + totalSwitchingTime);
	cout<<"CPU Efficiency: "<<CPUefficiency<<"%\n";

	cout << "\nPID\tService Time\tTurnaround Time\tStart Time\tCompletion Time\tWait Time\n";
	for (int i = 0; i < readyQueue.size(); i++) {
        cout << readyQueue[i].id << "\t  " 
		<<  readyQueue.at(i).completionTime - readyQueue.at(i).arrivalTime - readyQueue.at(i).waitTime <<"\t\t   "
		<< readyQueue[i].turnaroundTime << "\t\t" 
        << readyQueue[i].startTime << "\t\t"
		<< readyQueue[i].completionTime <<"\t\t"
		<<readyQueue[i].waitTime 
        << endl;
    }

}





void SJN(vector<Process> readyQueue) {
	//is completed array keeps track of the status of the process in its respective index.
	int isCompleted[500];
	int totalTurnaround = 0;
	memset(isCompleted, 0, sizeof(isCompleted));
	int currentTime = 0, completed = 0;
	int totalSwitchingTime = 0;

	while (completed != readyQueue.size()) {
		int index = -1, max = 500;

		for (int i = 0; i < readyQueue.size(); i++) {
			//check to see which process that is in the queue and not completed has the shortest burst time.
			if (readyQueue.at(i).arrivalTime <= currentTime && isCompleted[i] == 0) {
				if (readyQueue.at(i).burstTime < max) {
					max = readyQueue.at(i).burstTime;
					index = i;
				}
				if (readyQueue.at(i).burstTime == max) {//if they are equal check which one came first 
					if (readyQueue.at(i).arrivalTime < readyQueue.at(index).arrivalTime) {
						max = readyQueue.at(i).burstTime;
						index = i;
					}
				}
			}
		}
		//since there is a switch in process we have to increment wait time and switch time and current time by 2
		//but not for the first one
		if(currentTime!=0){
			currentTime+=2;
			totalSwitchingTime+=2;
			for(int i = 0; i<readyQueue.size(); i++) {
				if (readyQueue.at(i).arrivalTime <= currentTime && isCompleted[i] == 0){
					readyQueue.at(i).waitTime+=2;
				}
			}
		}

		if (index != -1) {
			for(int i = 0; i<readyQueue.size(); i++) {
				if (readyQueue.at(i).arrivalTime <= currentTime && isCompleted[i] == 0 && i!=index){
					readyQueue.at(i).waitTime++;
				}
			}
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
			for(int i = 0; i<readyQueue.size(); i++) {
				if (readyQueue.at(i).arrivalTime <= currentTime && isCompleted[i] == 0){
					readyQueue.at(i).waitTime++;
				}
			}
		}

	}

	cout<<"Total Time: "<<currentTime<<endl;

	//average waiting time
	int totalWaitTime = 0;
	for(int i = 0; i < readyQueue.size(); i++){
		totalWaitTime+=readyQueue.at(i).waitTime;
	}
	int avgWaitTime = totalWaitTime/readyQueue.size();
	cout<<"Average Waiting Time: "<<avgWaitTime<<endl;

	//average TAT
	float avgTurnaround;
	avgTurnaround = (float)totalTurnaround / readyQueue.size();
	cout << "Average Turnaround Time = " << avgTurnaround << endl;

	//cpu efficiency
	cout<<"total Switching time for CPU calculaiton: "<< totalSwitchingTime <<endl;
	double CPUefficiency = (double)currentTime / (currentTime + totalSwitchingTime);
	cout<<"CPU Efficiency: "<<CPUefficiency<<"%\n";

	cout << "\nPID\tService Time\tTurnaround Time\tStart Time\tCompletion Time\tWait Time\n";
	for (int i = 0; i < readyQueue.size(); i++) {
		cout << readyQueue.at(i).id << "\t"
		<<  readyQueue.at(i).completionTime - readyQueue.at(i).arrivalTime - readyQueue.at(i).waitTime <<"\t\t   "
		<< readyQueue.at(i).turnaroundTime <<"\t\t"
		 << readyQueue.at(i).startTime << "\t\t"
		  << readyQueue.at(i).completionTime << "\t\t"
		<<readyQueue[i].waitTime << endl;
	}


}
