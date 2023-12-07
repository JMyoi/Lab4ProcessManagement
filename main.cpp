
#include <iostream>
#include <vector>
#include "Algorithms.h"
#include "Process.h"
using namespace std;

int main() {
    cout << "Enter the number of processes to run: " << endl;
    int readyQueueSize;
    cin >> readyQueueSize;
    vector<Process> readyQueue(readyQueueSize);
    cout << "Enter the burst time, arrival time, and priority for each process: \n";
    for (int i = 0; i < readyQueueSize; i++) {
        cout << "Process " << i + 1 << "\n\tArrival Time: ";
        cin >> readyQueue.at(i).arrivalTime;
        cout << "\n\tBurst Time:";
        cin >> readyQueue.at(i).burstTime;
        cout << "\n\tpriority: ";
        cin >> readyQueue.at(i).priority;
        cout << endl;
        readyQueue.at(i).id = i + 1;
    }
   
    cout << "****************************************Shortest Job Next************************************\n";
    SJN(readyQueue);
    cout << "***********************************************************************************************\n";
    cout << "*************************************SRTF (preemptive)************************************\n";
    SRTF(readyQueue);
    cout << "***********************************************************************************************\n";
   

}