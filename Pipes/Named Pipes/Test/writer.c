#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <linux/stat.h>

#define FIFO_FILE "MYFIFO"
#define BUF_SIZE 80
struct MSG
{
	int pid;
	char msg[BUF_SIZE];
};
int main(int argc, char const *argv[])
{
	int fp;
	struct MSG mymsg;
	if(argc != 2){
		printf("Usage: Message\n");
		return 0;
	}
	if((fp = open(FIFO_FILE , O_WRONLY)) == -1){
		printf("ERROR: cant open FIFO\n");
		return 0;
	}
	mymsg.pid = getpid();
	sprintf( mymsg.msg, "%s" , argv[1]);
	// fputs(argv[1] , fp);
	write((int) fp , &mymsg , sizeof(struct MSG));
	close(fp);
	return 0;
}