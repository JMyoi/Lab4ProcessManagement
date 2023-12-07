
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

    
   
    cout << "\n****************************************Shortest Job Next************************************\n";
    SJN(readyQueue);
    cout << "***********************************************************************************************\n";
    cout << "*************************************SRTF (preemptive)************************************\n";
    SRTF(readyQueue);
    cout << "***********************************************************************************************\n";
   
    fin.close();
}