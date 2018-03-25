#include "local.h"

void set_Server_addr(struct sockaddr_in * );
int Load_file(char * , char ** );
int send_file(int * ,char * , int * );


int main(int argc , char * argv){

	int Server_fd, new_fd;
	struct sockaddr_in srv;
	int srv_len = sizeof(srv);
	struct Pack pack;
	char * buf;
	int fileSize = 0;

	/* Create the Server listening Socket */
	if ((Server_fd = socket(AF_INET , SOCK_STREAM , 0))  == -1)
	{
		perror("Unable to Create the server Socket\n");
		return errno;
	}
	/* Set up the Addresss of the Server socket */
	set_Server_addr(&srv);

	/* Bind the Server Port Number */
	if (bind(Server_fd , (struct sockaddr *) &srv , srv_len) == -1 )
	{
		perror("Unable to Bind the server socket\n");
		return errno;
	}

	if(listen(Server_fd , 1) == -1){
		perror("Failed to listen");
		return errno;
	}


	/* Keep listening  */
	while(1){

		if((new_fd = accept(Server_fd , (struct sockaddr *) &srv , &srv_len)) == -1){
			perror("Failed to accept connection\n");
			return errno;
		}
		/* display connection */
		printf("Connected to: %s (port: %d)\n", inet_ntoa(srv.sin_addr), srv.sin_port);

		/* Get the Request Package */
		while(read(new_fd , &pack , sizeof(struct Pack)) <= 0 );
		printf("%s (port: %d):> request %s\n", inet_ntoa(srv.sin_addr),
									srv.sin_port ,
									pack.body);

		/*Check to see if the File exits*/
		if ((access(pack.body , F_OK)))
		{
			printf("The file %s doesnt exist\n", pack.body);
			return errno;
		}

		/* Load The file to be sent */
		fileSize = Load_file(pack.body , &buf);
		printf("Request file size = %d\n" , fileSize);
		
		/* Send the Size of the File First */
		pack.index = fileSize;
		while(write(new_fd , &pack , sizeof(struct Pack)) <= 0);

		/* Send the Packages */	

		if (send_file(&new_fd , buf , &fileSize) != fileSize)
		{
			perror("Failed tp send Complete File \n");
			continue;
		}
		printf("File Sent OK!\n");
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
	int size = 0;

	FILE * f ;
	if((f = fopen(filename , "rb")) == NULL){
		*ptr = NULL;
		return -1;
	}
	fseek(f , 0 , SEEK_END);
	size = ftell(f);
	fseek(f , 0 ,SEEK_SET);
	*ptr = (char *)malloc(size+1);

	if(size != fread(*ptr , sizeof(char) , size , f)){
		free(*ptr);
		return -2;
	}

	fclose(f);
	(*ptr)[size] = 0;
	fwrite(*ptr , 512 , 1 , stdout);
	fflush(stdout);
	return size;
}

int send_file(int * sock ,char * buf  , int *len ){
	int sent =0;
	int remainder = *len;
	int temp =0;

	while( sent < *len){
		if((temp = write(*sock , buf+sent , remainder)) == -1 ){
			return -1;
		}

		sent += temp;
		remainder -= temp;
	}
	return sent;
}