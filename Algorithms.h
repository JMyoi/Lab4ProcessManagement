#pragma once
#include "Process.h"
#include <vector>
using namespace std;


//first come first serve
void FCFS(vector<Process> readyQueue);
void Priority(vector<Process> readyQueue);
//shortest job next
void SJN(vector<Process> readyQueue);
void SRTF(vector<Process> readyQueue);
void RoundRobin(vector<Process> readyQueue);