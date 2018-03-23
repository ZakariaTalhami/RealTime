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
	umask(0);
	mknod(FIFO_FILE , S_IFIFO | 0666 , 0);
	while(1){
		fp = open(FIFO_FILE , O_RDONLY);
		// fgets(ReadBuf , 80 , fp);
		read((int)fp , &mymsg , sizeof(struct MSG));
		printf("REV: %s\n", mymsg.msg );
		close(fp);
	}
	return 0;
}