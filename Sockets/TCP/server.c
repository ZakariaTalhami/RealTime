#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>

/* 
 * File:   Server.c
 * Author: zakaria Talhami
 *
 * Created on March 14, 2018, 12:07 PM
 */
#define BUFSIZE 255
#define MAX_LINE_LENGTH 255
#define MAX_LINES 50
#define PORT 8080
int main(int argc , char * argv[]){
	int server_fd, newfd;
	char * cat = "cat";
	struct sockaddr_in address;
	int addlen = sizeof(address);

	/*Must specify the File to send to the Client*/
	if (argc != 2)
	{
		printf("Usage: Must provide only one Parameter\n");
		return errno;
	}
	/*Make sure the File exits*/
	if ((access(argv[1] , F_OK)))
	{
		printf("The file %s doesnt exist\n", argv[1]);
		return errno;
	}

	/*Create a socket For listening*/
	if((server_fd = socket(AF_INET , SOCK_STREAM , 0)) == 0){
		printf("Error: was unable to create a Socket!\n");
		return errno;
	}
	printf("Server Socket was created.\n");

	/*Setting up the Server Address struct*/
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);
	/*Bind the Server Port to 8080*/
	if(bind(server_fd , (struct sockaddr *) &address , sizeof(address)) < 0){
		printf("Error: Unable to bind the socket Port number\n");
		return errno;
	}
	printf("Socket was been bound\n");

	/*Set the Server to listen*/
	/*Only handles one client request*/
	if(listen(server_fd , 1)<0){
		printf("Error: Unable to activate Listen\n");
		return errno;
	}
	printf("Listening\n");

	/*Waite for the Client to Send Request and Accept when arrives*/
	/*Create a new socket for the incoming request*/
	if(newfd = accept(server_fd , (struct sockaddr *) &address , (socklen_t *)&addlen)<0){
		printf("Error: at accpet\n");
		return errno;
	}
	printf("Connected\n");
	while(send(server_fd , cat , strlen(cat) , 0)<=0){
		printf("Error Failed to Write\n");
		fflush(0);
	}
	printf("Server Wrote To the Socket\n");
	fflush(0);
	while(1);
	


	return (EXIT_SUCCESS);
}
