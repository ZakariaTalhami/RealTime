#ifndef __LOCAL_H_
#define __LOCAL_H_

/*
 * Common header file: parent, producer and consumer
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <wait.h>
#include <signal.h>
#include <errno.h>

#ifndef KEY
#define KEY 5677
#endif

#ifndef SHM_SIZE
#define SHM_SIZE 27
#endif

#ifndef BUF_SIZE
#define BUF_SIZE 80
#endif

struct MSG{
	int pid;
	char msg[BUF_SIZE];
};
union semun {
	int val;
	struct semid_ds * buf;
	struct seminfo * __buf;
	void * __pad;
};

#endif
