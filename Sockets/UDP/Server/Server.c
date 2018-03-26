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
	if ((bind(Server_fd , (struct sockaddr *)&srv , sizeof(struct sockaddr_in))) == -1)
	{
		perror("Failed to bind the socket");
		return errno;
	}
	/*
		Read the Version from the file.
	*/
	f = fopen("sh_file.txt" , "rb");
	fgets(version , BUF_SIZE , f);
	version[strlen(version)-1] = '\0';
	printf("Read Version!\n");
	printf("The Current version is :> %s\n", version );
	printf("The Current version is :> %s\n", version );

	/*
		Wait for requests to the Server *
	*/
	while(1){
		/* Set socket  fds */
		FD_ZERO(&readfds); /*init*/
		FD_SET(Server_fd , &readfds);

		if (select(Server_fd+1 , &readfds  , 0 , 0 , 0)< 0)
		{
			/* code */
			break;
		}
		if(!(FD_ISSET(Server_fd , &readfds))){
			continue;
		}

		/* Receive request from clients  */
		if(!((int)recvfrom(Server_fd , &msg, sizeof(struct MSG) , 0 , (struct sockaddr *)&srv , &srv_len) > 0)){
			printf("Failed to receive message!\n" );
			continue;
		}

		printf("clinet Version:> %s\n", msg.body);


	}
	return 0;
}





void set_Server_addr(struct sockaddr_in * srv){

	(*srv).sin_family = AF_INET;
	(*srv).sin_port = htons(PORT);
	(*srv).sin_addr.s_addr = htonl(INADDR_ANY);
}


/*
	Loads a File and Returns the buffer with ptr input
		returns the file size  
*/
int Load_file(char * filename , char ** ptr ){

}

int send_file(int * sock ,char * buf  , int *len ){

}