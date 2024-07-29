#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include "Process.h"
#include "CPUScheduler.h"

void fifoSchedule(std::vector<Process>& processes) {
    int currentTime = 0;
    int totalWaitTime = 0;
    int totalTurnaroundTime = 0;
    int totalResponseTime = 0;
    int completedProcesses = 0;

    for (auto& process : processes) {
        if (completedProcesses >= 500) break;
        int waitingTime = std::max(0, currentTime - process.getArrivalTime());
        int turnaroundTime = waitingTime + process.getCpuBurst();
        int responseTime = waitingTime;  // For FIFO, waiting time is the same as response time

        totalWaitTime += waitingTime;
        totalTurnaroundTime += turnaroundTime;
        totalResponseTime += responseTime;
        completedProcesses++;
        

        currentTime = std::max(currentTime, process.getArrivalTime()) + process.getCpuBurst();

        process.setWaitingTime(waitingTime);
        process.setTurnaroundTime(turnaroundTime);
        process.setResponseTime(responseTime);

        //std::cout << "Process ID: " << process.getId() << ", Waiting Time: " << waitingTime << ", Turnaround Time: " << turnaroundTime << std::endl;
    }
     

    double averageWaitTime = static_cast<double>(totalWaitTime) / processes.size();
    double averageTurnaroundTime = static_cast<double>(totalTurnaroundTime) / processes.size();
    double averageResponseTime = static_cast<double>(totalResponseTime) / processes.size();
    double totalElapsedTime = currentTime;

    std::cout << "Number of processes: " << processes.size() << std::endl;
    std::cout << "Total elapsed time (for the scheduler): " << totalElapsedTime << std::endl;
    std::cout << "Throughput (processes per unit time): " << processes.size() / totalElapsedTime << std::endl;
    std::cout << "CPU utilization: " << (totalElapsedTime - totalWaitTime) / totalElapsedTime * 100 << "%" << std::endl;
    std::cout << "Average waiting time: " << averageWaitTime << std::endl;
    std::cout << "Average turnaround time: " << averageTurnaroundTime << std::endl;
    std::cout << "Average response time: " << averageResponseTime << std::endl;
}

void sjfSchedule(std::vector<Process>& processes) {
    std::sort(processes.begin(), processes.end(), [](Process& p1, Process& p2) {
        return p1.getCpuBurst() < p2.getCpuBurst();
    });
    fifoSchedule(processes);
}

void prioritySchedule(std::vector<Process>& processes) {
    std::sort(processes.begin(), processes.end(), [](Process& p1, Process& p2) {
        return p1.getPriority() < p2.getPriority();
    });
    fifoSchedule(processes);
}