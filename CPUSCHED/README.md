# cs471PROJECTC
Overview
This project simulates a CPU scheduler for handling process scheduling using three different algorithms: First-In-First-Out (FIFO), Shortest Job First (SJF) without preemption, and Priority with preemption. The simulation processes the arrival of new processes and calculates various scheduling statistics.

## Project Structure
* Process.h and Process.cpp: Define the Process class, which represents a process with parameters such as ID, arrival time, priority, and CPU burst time.
* CPUScheduler.h and CPUScheduler.cpp: Implement the scheduling algorithms (FIFO, SJF, Priority) and handle the scheduling logic.
* Main.cpp: The main entry point of the program. It reads processes from an input file, invokes the appropriate scheduling algorithm, and outputs the results to both the console and a file.

### Input File Format
The input file should contain process information with each line representing a process in the following format:
"<Arrival Time> <CPU Burst Time> <Priority>"

#### Output
The program outputs the scheduling results to both the console and a specified output file located in the output directory. The results include the following statistics:

-  Number of processes
- Total elapsed time (for the scheduler)
- Throughput (processes per unit time)
- CPU utilization
- Average waiting time
- Average turnaround time
- Average response time

#### How to build and run:
Prereqs: 
- C++17 or later
- A C++ compiler

##### Compilation:
cd to the src directory first
Compile the code using the following command:
'g++ -std=c++17 -o Main Main.cpp CPUScheduler.cpp Process.cpp'

##### Running the program:
To run the program, use this command to run the compiled program with the input file and the scheduling algorithm as arguments: 
'./Main ../data/Datafile1-txt.txt FIFO'
- change the wording from "FIFO" to the other scheduling algorithms we want to look at

###### Results:
The Results will be displayed onto a separate "results.txt" file in the 'output' directory. The results will be updated after each different run/testing of different scheduling algorithm