# Project 1
## Description
You are asked to design a user-space scheduler based on the priority-driven scheduler built in Linux kernel for a set of child processes. You may change priority of each child process directly for the specified scheduling policy by sched_setscheduler. The goal is to get a result as close to the expected schedule as possible. The more correct finish time and order of processes, the more points you will get. For more accuracy, you need to measure the start and finish time of each child process in Linux kernel. You might need to write your own system call based on the function getnstimeofday and show the information through printk.

In the main process, it first reads the input parameters from the standard input. The parameters will specify the scheduling policy, the number of child processes to create, and the set of child processes. The scheduling policy may be first in, first out (FIFO), round-robin (RR), shortest job first (SJF), or preemptive shortest job first (PSJF). In the input, each child process is described by a 3-tuple specifying its name, ready time, and execution time.

A process with a ready time X should be created via the system call fork after X units of time since the start of the main process. Similarly, a process with an execution time Y should execute, not sleep, Y units of time. The unit of time is defined as the execution time of an empty for-loop of one million iterations as follows.

```C
{ volatile unsigned long i; for(i=0;i<1000000UL;i++); } 
```
For convenience of debugging, each round (time quantum) of RR scheduler is defined as 500 time units in this project, and ready time of processes will not be the multiple of 500 time units. If the process finishes before the time quantum timer expires, then it is swapped out of the CPU just like FIFO algorithm.
### Program Input
```
S // the scheduling policy, one of the following strings: FIFO, RR, SJF, PSJF.
N // the number of processes
N1 R1 T1
N2 R2 T2
…
Nn Rn Tn
//Ni - a character string with a length less than 32 bytes, specifying the name of the i-th process.
//Ri - a non-negative integer, specifying the ready time of the i-th process.
//Ti - a non-negative integer, specifying the execution time of the i-th process.
```
### Program Output
```
TAG PID ST FT
//TAG - the tag to identify the message of this project.
//PID - the process ID of this process
//ST - the start time of this process in the format seconds.nanoseconds.
//FT - the finish time of this process in the format seconds.nanoseconds.
```
The output from the command `dmesg` might contain:
```
[Project1] 4007 1394530429.657899070 1394530430.004979285
[Project1] 4008 1394530429.668132665 1394530430.218223930
[Project1] 4009 1394530429.676547365 1394530430.221544405
```
## Usage
Generate test output:
```
./run.sh
```
