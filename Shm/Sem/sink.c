#include "local.h"

#ifndef MSG_FLAG
#define MSG_FLAG '*'
#endif

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

	/* Simulates a Messenger  */
	while(1){
		/* Read sent Messages */
		msgptr = (struct MSG * )(shmptr +1);
		while(*shmptr != MSG_FLAG );

		/*
			should i leave it un synched?
		*/

		printf("Process (%d) :> %s\n", (*msgptr).pid ,(*msgptr).msg );
		*shmptr = 0; //marks as read
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
