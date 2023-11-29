#pragma once

struct Process{
        int id;
        //Turn around time completion time - arrival time 
        int turnaroundTime;
        int burstTime;
        int arrivalTime;
        int priority;
        int startTime;
        int completionTime;
};