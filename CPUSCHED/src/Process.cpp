#include "Process.h"

Process::Process(int id, int arrivalTime, int priority, int cpuBurst) {
    this->id = id;
    this->arrivalTime = arrivalTime;
    this->priority = priority;
    this->cpuBurst = cpuBurst;
}

int Process::getId() {
    return id;
}

void Process::setId(int id) {
    this->id = id;
}

int Process::getArrivalTime() {
    return arrivalTime;
}

void Process::setArrivalTime(int arrivalTime) {
    this->arrivalTime = arrivalTime;
}

int Process::getPriority() {
    return priority;
}

void Process::setPriority(int priority) {
    this->priority = priority;
}

int Process::getCpuBurst() {
    return cpuBurst;
}

void Process::setCpuBurst(int cpuBurst) {
    this->cpuBurst = cpuBurst;
}