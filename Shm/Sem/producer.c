#include "local.h"

int main(int argc , char * argv){

	int 		shmid, semid;
	char 		* shmptr , * ptr;
	struct 		MSG msg;
	struct 		MSG * msgptr;
	union		semun un_sem;
	struct 		sembuf acquire = {0 , -1 , SEM_UNDO},
				  	   release = {0 , 1 , SEM_UNDO};
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
		Create Semaphore 
	*/
	if ((semid = semget(KEY , 1  , IPC_CREAT | 0666)) == -1)
	{
		perror("Failed to create a Semaphore");
	}

	/*
		Init the Sem
	*/
	un_sem.val = 1;
	if(semctl(semid , 0  , SETVAL , un_sem) == -1 ){
		perror("Init the Semaphore\n");
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
			Must acquire the Semaphore before writing
		*/

		if( semop(semid , &acquire , 1) != -1){
			/*
				Copy the Messge to the shared memory 
			*/
			if (*shmptr != '*')
			{
				memcpy(msgptr , &msg  , sizeof(struct MSG));
				*shmptr = '*';
			}
			semop(semid , &release , 1);
		}
		
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