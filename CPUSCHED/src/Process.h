#ifndef PROCESS_H
#define PROCESS_H

class Process {
private:
    int id;
    int arrivalTime;
    int priority;
    int cpuBurst;
    int waitingTime;
    int turnaroundTime;
    int responseTime;

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

    int getWaitingTime();
    void setWaitingTime(int waitingTime);

    int getTurnaroundTime();
    void setTurnaroundTime(int turnaroundTime);

    int getResponseTime();
    void setResponseTime(int responseTime);
};
#endif // PROCESS_H