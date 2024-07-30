#ifndef CPUSCHEDULER_H
#define CPUSCHEDULER_H

#include <vector>
#include "Process.h"
#include <ostream>

void fifoSchedule(std::vector<Process>& processes, std::ostream& out);
void sjfSchedule(std::vector<Process>& processes, std::ostream& out);
void prioritySchedule(std::vector<Process>& processes, std::ostream& out);

#endif 