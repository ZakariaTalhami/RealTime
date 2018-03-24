#include "local.h"

int main(int argc , char * argv){

	int shmid;
	char * shmptr , * ptr;
	struct MSG msg;
	struct MSG * msgptr;
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

	while(1){
		/* Sending Struct messages though shared memory */
		msgptr = (struct MSG * )(shmptr +1);
		while(*shmptr != 'P');
		printf(":8> Read message %d:  %s\n", (* msgptr).pid ,(* msgptr).msg );fflush(stdout);
		printf(":8> Enter message: ");
		fflush(stdout);
		fgets(msg.msg , BUF_SIZE , stdin );
		msg.pid = getpid();

		memcpy(msgptr , &msg  , sizeof(struct MSG));
		*shmptr = 'C';
	}

	/*
		Detatch the Shared memory
	*/
		if ( shmdt(shmptr) == -1 )
		{
			perror(" Failed to Detatch the Shared memory");
		}
	/*
		Set Memory to be removed
	*/
		if ( shmctl( shmid , IPC_RMID , NULL ) )
		{
			perror("Failed to mark for removal");
			return errno;
		}
	

		return 0;
}
