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

	/* Construct the clients message to the server */
	buf.mtype = mtype;
	buf.PID = getpid(); // so the server can reply to this message

	/* Get the client's message to the server */
	printf("Enter messages:> ");
	fgets(buf.msg , BUF_SIZE , stdin);

	/* Send the Message to the Server */
	while(send_message(qid , &buf , 0) == -1);

	/* Checks to see if there is a message in the queue */
	while( peek_message(qid , mtype) == -1);
	/* Read the message from the server */
	get_message(qid , &buf, buf.PID , 0);

	printf("rev:> %s\n", buf.msg );
}