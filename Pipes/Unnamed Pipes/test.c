#include <stdio.h>
#include <string.h>
#include <unistd.h>
#define READ 0
#define WRITE 1

char * phrase = "Stuff this in your pipe and smoke it";

void main (){

	int fd[2] , BytesRead;
	char message[100] = {0};
	pipe(fd);

	if(fork() == 0){
		/* CHild Writer */
		close(fd[READ]);
		write(fd[WRITE] , phrase , strlen(phrase)+1);
		close(fd[WRITE]);
		printf("Child: Wrote '%s' to the pipe\n", phrase);
	}
	else{
		/* Parent Reader */
		close(fd[WRITE]);
		BytesRead = read(fd[READ] , message , 100);
		close(fd[READ]);
		printf("Parent: Read '%d' bytes from the pipe: %s\n", BytesRead,message);
	}

}