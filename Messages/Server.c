#include "local.h"
#include "queue.h"

#ifndef KEY
#define KEY 500
#endif


/*
int open_queue(key_t );
int send_message(int  , struct MSG * , int);
int get_message(int  , struct MSG *  , long  ,int );
int peek_message(int  , long );
int remove_queue(int );
int stat_queue(int  , struct msqid_ds * );
*/

void main (int args , char * argv){

	int qid;
	struct MSG buf;
	int mtype = 1;

	/* open the message queue */
	if((qid = open_queue(KEY)) == -1){
		exit(1);
	}
	printf(":8>Message Queue was opened\n");

	/*
		Start receiving messages from clients
	*/

	while(1){
		/* wait until the message queue has a message*/
		/* dont really need this because the msgrcv can be set to blocking*/
		while( peek_message(qid , mtype) == -1);
		get_message(qid , &buf, mtype , 0);

		/* Read and Set new message */
		printf("Rev:> %s\n" , buf.msg);
		fflush(stdout);
		/* Get servers Reply to the client from the terminal */
		printf("Enter Message:> ");
		fgets(buf.msg , BUF_SIZE , stdin);

		/* prepare the next message */
		buf.mtype = buf.PID;	// the client will be listening by using it PID
		buf.PID = getpid();		//set the PID so the client can send again

		/* Send the servers reply message */
		while(send_message(qid , &buf , 0) == -1);
	}

} 