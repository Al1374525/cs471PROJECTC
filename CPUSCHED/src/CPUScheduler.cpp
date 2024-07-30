#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include "Process.h"
#include "CPUScheduler.h"

void fifoSchedule(std::vector<Process>& processes, std::ostream& out) {
    int currentTime = 0;
    int totalWaitTime = 0;
    int totalTurnaroundTime = 0;
    int totalResponseTime = 0;
    int completedProcesses = 0;
    int totalElapsedTime = 0;
    int cpuActiveTime = 0;
    const int maxProcesses = 500;

    for (auto& process : processes) {
        if (completedProcesses >= maxProcesses) break;

        int waitingTime = std::max(0, currentTime - process.getArrivalTime());
        int turnaroundTime = waitingTime + process.getCpuBurst();
        int responseTime = (process.getArrivalTime() > currentTime) ? 0 : waitingTime;

        totalWaitTime += waitingTime;
        totalTurnaroundTime += turnaroundTime;
        totalResponseTime += responseTime;
        completedProcesses++;
        totalElapsedTime = currentTime;

        currentTime = std::max(currentTime, process.getArrivalTime()) + process.getCpuBurst();
        cpuActiveTime += process.getCpuBurst();

        //out << "Process ID: " << process.getId() << ", Waiting Time: " << waitingTime << ", Turnaround Time: " << turnaroundTime << std::endl;
    }

    totalElapsedTime = currentTime; // update totalElapsedTime to the latest currentTime

    out << "Number of processes: " << completedProcesses << std::endl;
    out << "Total elapsed time: " << totalElapsedTime << std::endl;
    out << "Throughput: " << static_cast<double>(completedProcesses) / totalElapsedTime << std::endl;
    out << "CPU utilization: " << (static_cast<double>(cpuActiveTime) / totalElapsedTime) * 100 << "%" << std::endl;
    out << "Average Waiting Time: " << static_cast<double>(totalWaitTime) / completedProcesses << std::endl;
    out << "Average Turnaround Time: " << static_cast<double>(totalTurnaroundTime) / completedProcesses << std::endl;
    out << "Average Response Time: " << static_cast<double>(totalResponseTime) / completedProcesses << std::endl;
}

void sjfSchedule(std::vector<Process>& processes, std::ostream& out) {
    std::sort(processes.begin(), processes.end(), [](Process& p1, Process& p2) {
        return p1.getCpuBurst() < p2.getCpuBurst();
    });
    fifoSchedule(processes, out);
}

void prioritySchedule(std::vector<Process>& processes, std::ostream& out) {
    std::sort(processes.begin(), processes.end(), [](Process& p1, Process& p2) {
        return p1.getPriority() < p2.getPriority();
    });
    fifoSchedule(processes, out);
}