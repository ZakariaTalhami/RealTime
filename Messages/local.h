#ifndef __LOCAL_H__
#define __LOCAL_H__


#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

#ifndef BUF_SIZE
#define BUF_SIZE 80
#endif
struct MSG
{
	long mtype;
	int PID;
	char msg[BUF_SIZE];
};

#endif