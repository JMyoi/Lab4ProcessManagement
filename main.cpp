
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
    }
     int size;
     fin>>size;
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
  
   
    cout << "\n****************************************Shortest Job Next************************************\n";
    SJN(readyQueue);
    cout << "***********************************************************************************************\n";
    cout << "*************************************SRTF (preemptive)************************************\n";
    SRTF(readyQueue);
    cout << "***********************************************************************************************\n";
   
    fin.close();
}