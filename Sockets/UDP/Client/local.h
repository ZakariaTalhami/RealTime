#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#ifndef BUF_SIZE
#define BUF_SIZE 100
#endif

#ifndef PORT
#define PORT 5454
#endif

struct MSG
{
	int index;
	char body[BUF_SIZE];
};
