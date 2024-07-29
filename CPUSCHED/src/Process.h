#ifndef PROCESS_H
#define PROCESS_H

class Process {
private:
    int id;
    int arrivalTime;
    int priority;
    int cpuBurst;

public:
    Process(int id, int arrivalTime, int priority, int cpuBurst);
    int getId();
    void setId(int id);
    int getArrivalTime();
    void setArrivalTime(int arrivalTime);
    int getPriority();
    void setPriority(int priority);
    int getCpuBurst();
    void setCpuBurst(int cpuBurst);
};

#endif // PROCESS_H