#include "local.h"

/* WHY DO I GET AND ERROR IF THESE ARE PLACED IN THE LOCAL.H */
#include <netdb.h>
#include <sys/stat.h>
#include <fcntl.h>

void set_Server_addr(struct sockaddr_in * );
int rev_file(int *  , char *  , int * );


int main (int argc , char * argv[]){

	int Client_fd, fileSize;
	struct hostent * hp;
	struct sockaddr_in cli;
	int cli_len = sizeof(cli);
	char * buf;
	struct Pack pack;
	

	/* Check the Inputed Args */
	if(argc != 3){
		perror("Usage: address , file name");
		return -1;
	} 

	/* Translate the request address */
	if((hp = gethostbyname(argv[1])) == NULL){
		perror("Unable to Translate the domain name");
		return errno;
	}

	/* Set the server address */
	set_Server_addr(&cli );

	cli.sin_addr.s_addr = ((struct in_addr *)(hp->h_addr))->s_addr;

	/* Creating the client socket*/
	if((Client_fd = socket(AF_INET , SOCK_STREAM , 0)) == -1){
		perror("Failed to Create Client Socket\n");
		return errno;
	} 

	/* Connect to the server */
	if (connect(Client_fd,(struct sockaddr *) &cli, cli_len ) == -1){
		perror("Cant connect to the Server!\n");
		return errno;
	}

	/* Setting up the Request message */
	pack.index = -1;
	// pack.body = argv[2];
	sprintf(pack.body , "%s" , argv[2]);

	/* Sending the Request message */
	while(write(Client_fd , &pack , sizeof(struct Pack)) <= 0);
	printf("Request was Sent\n");

	while(read(Client_fd , &pack , sizeof(struct Pack)) <= 0);
	fileSize = pack.index;
	printf("The File size is :> %d\n", fileSize );

	/* create a new mp3 file*/

	/* receive File */
	if(rev_file(&Client_fd , buf , &fileSize) == -1){
		perror("Failed to receive complete file!\n");
		return errno;
	}
	printf("File received ok!\n");

	/* Play the Song */
	system("vlc-wrapper my.mp3");
	return 0;
}



void set_Server_addr(struct sockaddr_in * srv ){

	(*srv).sin_family = AF_INET;
	(*srv).sin_port = htons(PORT);
}

int rev_file(int * sock , char * buf , int * len){
	int rev = 0;
	int temp = 0;
	int remainder = *len;
	char workbuf[*len] ;

	while(rev < *len){
		if((temp = read(*sock , workbuf+rev , remainder)) == -1){
			return -1;
		}
		if(temp == 0){
			break;
		}

		rev += temp;
		remainder -=temp;
		printf("State :> temp(%d) rev(%d) rem(%d)\n", temp, rev , remainder );
	}
	if (temp == 0)
	{
		/* code */
		printf("Hi me S\n");
	}
	printf("Ended\n");
	printf("rev:> %d\n" ,rev);
	// memcpy(buf , workbuf , sizeof(workbuf));
	// fwrite(workbuf , 512 , 1 , stdout);
	// fflush(stdout);
	int f = open("my.mp3" , O_CREAT|0666);
	// while(write(f , workbuf , *len)> 0);
	write(f , workbuf , *len);
	close(f);
	printf("HERE?\n");
	return rev;
}