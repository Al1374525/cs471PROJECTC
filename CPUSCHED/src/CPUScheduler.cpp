#include <iostream>
#include <vector>
#include <algorithm>
#include "Process.h"
#include "CPUScheduler.h"

void fifoSchedule(std::vector<Process>& processes) {
    int currentTime = 0;
    int totalWaitTime = 0;
    int totalTurnaroundTime = 0;

    for (auto& process : processes) {
        int waitingTime = std::max(0, currentTime - process.getArrivalTime());
        int turnaroundTime = waitingTime + process.getCpuBurst();

        totalWaitTime += waitingTime;
        totalTurnaroundTime += turnaroundTime;

        currentTime = std::max(currentTime, process.getArrivalTime()) + process.getCpuBurst();

        std::cout << "Process ID: " << process.getId() << ", Waiting Time: " << waitingTime << ", Turnaround Time: " << turnaroundTime << std::endl;
    }

    std::cout << "Average Waiting Time: " << static_cast<double>(totalWaitTime) / processes.size() << std::endl;
    std::cout << "Average Turnaround Time: " << static_cast<double>(totalTurnaroundTime) / processes.size() << std::endl;
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