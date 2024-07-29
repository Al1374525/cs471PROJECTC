#ifndef CPUSCHEDULER_H
#define CPUSCHEDULER_H

#include <vector>
#include "Process.h"

void fifoSchedule(std::vector<Process>& processes);
void sjfSchedule(std::vector<Process>& processes);
void prioritySchedule(std::vector<Process>& processes);

#endif 