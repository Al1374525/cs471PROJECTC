#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Process.h"
#include "CPUScheduler.h"

std::vector<Process> readProcesses(const std::string& inputFile) {
    std::vector<Process> processes;
    std::ifstream file(inputFile);
    if (!file.is_open()) {
        std::cerr << "File not found: " << inputFile << std::endl;
        return processes;
    }

    int  arrivalTime, priority, cpuBurst;
    int id = 1;
    while (file >> arrivalTime >> cpuBurst >> priority) {
        processes.emplace_back(id, arrivalTime, priority, cpuBurst);
        std::cout << "Read Process - ID: " << id << ", Arrival Time: " << arrivalTime 
                  << ", Priority: " << priority << ", CPU Burst: " << cpuBurst << std::endl;
        id++;
    }

    return processes;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "Usage: ./Main <input file> <scheduling algorithm>" << std::endl;
        return 1;
    }

    std::string inputFile = argv[1];
    std::string algorithm = argv[2];
    std::vector<Process> processes = readProcesses(inputFile);

    if (algorithm == "FIFO") {
        fifoSchedule(processes);
    } else if (algorithm == "SJF") {
        sjfSchedule(processes);
    } else if (algorithm == "PRIORITY") {
        prioritySchedule(processes);
    } else {
        std::cout << "Unknown algorithm: " << algorithm << std::endl;
    }

    return 0;
}