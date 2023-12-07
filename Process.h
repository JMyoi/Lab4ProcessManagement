#pragma once

struct Process{
        int id;
        int turnaroundTime;
        int burstTime;
        int arrivalTime;
        int priority;
        int startTime = -1;
        int completionTime;
        int waitTime=0;
        int ServiceTime = 0;
};