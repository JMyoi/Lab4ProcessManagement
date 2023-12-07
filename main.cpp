
#include <iostream>
#include <vector>
#include <fstream>
#include "Algorithms.h"
#include "Process.h"
using namespace std;

int main() {

    ifstream fin;
    fin.open("ProcessData.txt");
    if(!fin.is_open()){
        cout<<"file not found"<<endl;
    }else{
        cout<<"file opned"<<endl;
    }
     int size;
     fin>>size;
     cout<<"size is: "<<size<<endl;
    vector<Process> readyQueue(size);
    int processNumber, arrivalTime, burstTime;

    int i = 0;
    while(!fin.eof()){
        fin>>processNumber;
        readyQueue.at(i).id = processNumber;
        fin>>arrivalTime;
        readyQueue.at(i).arrivalTime = arrivalTime;
        fin>>burstTime;
        readyQueue.at(i).burstTime = burstTime;
        i++;
    }
    for(int i = 0; i<readyQueue.size(); i++){
        cout<<"id: "<< readyQueue.at(i).id<<endl;
        cout<<"\tburst time: "<< readyQueue.at(i).burstTime;
        cout<<"\tarrival time: "<< readyQueue.at(i).arrivalTime<<endl;
    }
    cout<<"burst time: ";
    for(int i = 0; i<readyQueue.size(); i++){
        cout<<" "<< readyQueue.at(i).burstTime;
    }
    cout<<"\narrival time: ";
    for(int i = 0; i<readyQueue.size(); i++){
        cout<<" "<< readyQueue.at(i).arrivalTime;
    }


/*
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
        //cout << "\n\tpriority: ";
        //cin >> readyQueue.at(i).priority;
        cout << endl;
        readyQueue.at(i).id = i + 1;
    }*/
    
   
    cout << "****************************************Shortest Job Next************************************\n";
    SJN(readyQueue);
    cout << "***********************************************************************************************\n";
    cout << "*************************************SRTF (preemptive)************************************\n";
    SRTF(readyQueue);
    cout << "***********************************************************************************************\n";
   
    //fin.close();
}