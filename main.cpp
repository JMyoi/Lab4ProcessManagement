#include <iostream>
#include <vector>
#include "Algorithms.h"
#include "process.h"
using namespace std;

int main(){
    cout<<"Enter the number of processes to run: "<<endl;
    int readyQueueSize;
    cin>>readyQueueSize;
    vector<process> readyQueue(readyQueueSize);
    cout<<"Enter the burst time, arrival time, and priority for each process: \n";
    for(int i = 0; i<readyQueueSize; i++){
        cout<<"Process "<<i+1<<"\n\tArrival Time: ";
        cin>>readyQueue.at(i).arrivalTime;
        cout<<"\n\tBurst Time:";
        cin>>readyQueue.at(i).burstTime;
        cout<<"\n\tpriority: ";
        cin>>readyQueue.at(i).priority;
        cout<<endl;
    }
    for(int i = 0; i<readyQueueSize; i++){
       cout<< readyQueue.at(i).arrivalTime<<endl;
        cout<< readyQueue.at(i).burstTime<<endl;
       cout<< readyQueue.at(i).priority<<endl;

    }




}