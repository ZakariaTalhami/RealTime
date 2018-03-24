#include "local.h"

int main(int argc , char * argv){

	int shmid;
	char * shmptr , * ptr;
	struct MSG msg;
	char readChar;
	/*
		Create the Shared memory
	*/
	if ((shmid = shmget(KEY , SHM_SIZE , IPC_CREAT | 0666)) == -1)
	{
		perror("Failed to create shared memory\n");
		return errno;
	}

	/*
		Map the Shared memory to the process
	*/
	if ((shmptr = shmat(shmid , NULL , 0)) == (char *)-1)
	{
		perror("Failed to Attach the segment");
		return errno;
	}

	/*
		simple test to see if it works
	*/
	while(*shmptr != 'K');
	readChar = *shmptr;
	printf(":8> The K message was read!\n");

	*shmptr = 'D';


}