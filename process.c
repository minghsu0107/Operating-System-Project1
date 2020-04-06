#define _GNU_SOURCE
#include "process.h"
#include <sched.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
// #include <sys/types.h>
// #include <sys/syscall.h>
// #define GET_TIME 548
// #define PRINTK 549

int proc_assign_cpu(int pid, int core) {
	if (core > sizeof(cpu_set_t)) {
		fprintf(stderr, "Core index error.");
		return -1;
	}

	cpu_set_t mask;
	CPU_ZERO(&mask);
	CPU_SET(core, &mask);
		
	if (sched_setaffinity(pid, sizeof(mask), &mask) < 0) {
		perror("sched_setaffinity");
		exit(1);
	}

	return 0;
}

int proc_exec(struct process proc) {
	int pid = fork();

	if (pid < 0) {
		perror("fork");
		return -1;
	}

	if (pid == 0) {
		unsigned long start_sec, start_nsec, end_sec, end_nsec;
		char to_dmesg[200];
		
		struct timespec tm;
		clock_gettime(CLOCK_REALTIME, &tm);
		start_sec = tm.tv_sec;
		start_nsec = tm.tv_nsec;
		
		//syscall(GET_TIME, &start_sec, &start_nsec);

		for (int i = 0; i < proc.t_exec; i++) {
			UNIT_T();
#ifdef DEBUG
			if (i % 100 == 0)
				fprintf(stderr, "%s: %d/%d\n", proc.name, i, proc.t_exec);
#endif
		}
		
		clock_gettime(CLOCK_REALTIME, &tm);
		end_sec = tm.tv_sec;
		end_nsec = tm.tv_nsec;

		//syscall(GET_TIME, &end_sec, &end_nsec);

		sprintf(to_dmesg, "[Project1] %d %lu.%09lu %lu.%09lu\n", getpid(), start_sec, start_nsec, end_sec, end_nsec);
		
		//syscall(PRINTK, to_dmesg);
		
		FILE* fp = fopen("/dev/kmsg", "a+");
		fputs(to_dmesg, fp);
		
		exit(0);
	}
	
	/* Assign child to another core prevent from interupted by parant */
	proc_assign_cpu(pid, CHILD_CPU);

	return pid;
}

int proc_block(int pid) {
	struct sched_param param;
	
	/* SCHED_IDLE should set priority to 0 */
	param.sched_priority = 0;

	int ret = sched_setscheduler(pid, SCHED_IDLE, &param);
	
	if (ret < 0) {
		perror("sched_setscheduler:block");
		return -1;
	}

	return ret;
}

int proc_wakeup(int pid) {
	struct sched_param param;
	
	/* SCHED_OTHER should set priority to 0 */
	param.sched_priority = 0;

	int ret = sched_setscheduler(pid, SCHED_OTHER, &param);
	
	if (ret < 0) {
		perror("sched_setscheduler:wake");
		return -1;
	}

	return ret;
}
