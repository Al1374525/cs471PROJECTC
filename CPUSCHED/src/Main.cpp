#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <sys/stat.h> 
#include "Process.h"
#include "CPUScheduler.h"
#include <filesystem>

std::vector<Process> readProcesses(const std::string& inputFile) {
    std::vector<Process> processes;
    std::ifstream file(inputFile);
    if (!file.is_open()) {
        std::cerr << "File not found: " << inputFile << std::endl;
        return processes;
    }

    std::string line;
    // Skip the header line
    std::getline(file, line);

    int arrivalTime, cpuBurst, priority;
    int id = 1; // ID generator starting from 1
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        if (iss >> arrivalTime >> cpuBurst >> priority) {
            processes.emplace_back(id, arrivalTime, priority, cpuBurst);
            id++;
        } else {
            std::cerr << "Error reading line: " << line << std::endl;
        }
    }

    if (processes.empty()) {
        std::cerr << "No processes read from the file." << std::endl;
    }

    return processes;
}

void writeResultsToFile(const std::string& filename, const std::string& results) {
    std::ofstream outFile(filename);
    if (outFile.is_open()) {
        outFile << results;
        outFile.close();
    } else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "Usage: ./Main <input file> <scheduling algorithm>" << std::endl;
        return 1;
    }

    std::string inputFile = argv[1];
    std::string algorithm = argv[2];
    std::vector<Process> processes = readProcesses(inputFile);

    if (processes.empty()) {
        std::cerr << "No processes to schedule." << std::endl;
        return 1;
    }

    // Capture the output in a string
    std::ostringstream results;

    if (algorithm == "FIFO") {
        fifoSchedule(processes, results);
    } else if (algorithm == "SJF") {
        sjfSchedule(processes, results);
    } else if (algorithm == "PRIORITY") {
        prioritySchedule(processes, results);
    } else {
        std::cout << "Unknown algorithm: " << algorithm << std::endl;
        return 1;
    }


    // Write results to a file
    std::string outputFile = "../output/results.txt";
    writeResultsToFile(outputFile, results.str());

    // Also print the results to the console
    std::cout << results.str();

    return 0;
}