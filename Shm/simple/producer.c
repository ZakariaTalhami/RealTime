#include "local.h"

int main(int argc , char * argv){

	int shmid;
	char * shmptr , * ptr;
	struct MSG msg;
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
	*shmptr  ='K';

	while( *shmptr == 'K');

	printf(":8> the memory was changed\n");

	


}