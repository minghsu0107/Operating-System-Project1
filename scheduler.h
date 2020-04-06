#ifndef _SCHEDULING_H_
#define _SCHEDULING_H_

#include "process.h"

#define FIFO 1
#define RR 2
#define SJF 3
#define PSJF 4

/* Running scheduler */
int scheduling(struct process *proc, int nproc, int policy);

#endif