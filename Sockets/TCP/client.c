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
#include <netdb.h>
#include <arpa/inet.h>

/* 
 * File:   client.c
 * Author: zakaria  Talhami
 *
 * Created on March 16, 2018, 1:40 PM
 */
#define BUFSIZE 255
#define MAX_LINE_LENGTH 255
#define MAX_LINES 50
#define PORT 8080
int main(int argc , char * argv[]){
	int Client_fd, newfd;
	struct sockaddr_in address;
	struct hostent * hp;
	int addlen = sizeof(address);
	char buf[BUFSIZE] = {0};

	/*Must specify the File name to save from the server*/
	if (argc != 3)
	{
		printf("Usage: Must provide two Parameter\n");
		return errno;
	}

	/*Create a socket */
	if((Client_fd = socket(AF_INET , SOCK_STREAM , 0)) == 0){
		printf("Error: was unable to create a Socket!\n");
		return errno;
	}
	printf("Client Socket was created.\n");
	/*Get the host address of the provided Domain*/
	if ((hp = gethostbyname(argv[1])) == NULL)
	{
		printf("Error: Wasnt able to Convert Domain to IP\n");
		return errno;
	}

	/*Settting up address of the server*/
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = ((struct in_addr *) (hp->h_addr))->s_addr;
	address.sin_port = htons(PORT);
	printf("%s\n", inet_ntoa(address.sin_addr));

	/*Connect to the server*/
	if(connect(Client_fd , (struct sockaddr*) &address , sizeof(address)) <0){
		printf("Error : Unable to  connect to the Server\n");
		return errno;
	}
	printf("Connected to %s\n", argv[1]);
	read(Client_fd , buf , BUFSIZE);
	printf("Rec: %s\n", buf );

	return (EXIT_SUCCESS);
}
