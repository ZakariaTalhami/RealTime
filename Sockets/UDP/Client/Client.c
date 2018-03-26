#include "local.h"

void set_Server_addr(struct sockaddr_in * );
int Load_file(char * , char ** );
int send_file(int * ,char * , int * );

int main(int argc , char * argv){

	int Server_fd ;
	struct sockaddr_in srv;
	int srv_len = sizeof(struct sockaddr_in);
	struct MSG msg;
	FILE *f;
	char version[BUF_SIZE];

	fd_set readfds;

	/* Create the server socker */
	if ((Server_fd = socket(AF_INET , SOCK_DGRAM , 0)) == -1)
	{
		perror("Failed to create socket\n");
		return errno;
	}

	/* Set Bind the Server Port number*/
	set_Server_addr(&srv);
	srv.sin_addr.s_addr = inet_addr("127.0.0.1");
	/*
		Read the Version from the file.
	*/
	f = fopen("sh_file.txt" , "rb");
	fgets(msg.body , BUF_SIZE , f);
	msg.body[strlen(msg.body)-1] = '\0';
	printf("Read Version!\n");
	printf("The Current version is :> %s\n", msg.body );
	printf("The Current version is :> %s\n", msg.body );

	/*
		Wait for requests to the Server *
	*/
	

	sendto(Server_fd , &msg , sizeof(struct MSG) , 0 , (struct sockaddr *)&srv , srv_len);
	
	return 0;
}





void set_Server_addr(struct sockaddr_in * srv){

	(*srv).sin_family = AF_INET;
		(*srv).sin_port = htons(PORT);
	
}


/*
	Loads a File and Returns the buffer with ptr input
		returns the file size  
*/
int Load_file(char * filename , char ** ptr ){

}

int send_file(int * sock ,char * buf  , int *len ){

}