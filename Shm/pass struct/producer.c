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
	ptr = shmptr;
	while(1){
		/* Sending Struct messages though shared memory */

		/*
			Struct Message starts after flag
		*/
		msgptr = (struct MSG *)(shmptr + 1);

		/*
			Get the Message to be sent
		*/
		printf(":8> Enter message: ");
		fflush(stdout);
		fgets(msg.msg , BUF_SIZE , stdin );
		msg.pid = getpid();

		/*
			Copy the Messge to the shared memory 
		*/
		memcpy(msgptr , &msg  , sizeof(struct MSG));

		/*
			Wait until the receiver gets the message and
			sends his own
		*/
		*shmptr  = 'P';
		while( *shmptr == 'P');
		// reply has arrived
		printf(":8> the memory was changed\n");
		printf(":8> Read Message %d:%s\n", (* msgptr).pid  ,(*msgptr).msg );
		
	}
	/*
		Detatch the Shared memory
	*/
		if ( shmdt(shmptr) == -1 )
		{
			perror(" Failed to Detatch the Shared memory");
			return errno;
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