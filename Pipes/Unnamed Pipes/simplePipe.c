#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>

/* 
 * File:   newmain.c
 * Author: zakaria
 *
 * Created on March 11, 2018, 9:43 PM
 */
#define BUFSIZE 255
#define MAX_LINE_LENGTH 255
#define MAX_LINES 50
char ** readFile(char [], int *); 

int main(int argc , char * argv[]){
	int f_ds[2];
	int Num_food;
	 char buf[BUFSIZE];
	 char * s = malloc(MAX_LINES);
	 s = "hellop";
	// int errno = 0;
	if (argc != 2)
	{
		printf("Usage: Must provide only one Parameter\n");
		return errno;
	}
	if ((access(argv[1] , F_OK)))
	{
		printf("The file %s doesnt exist\n", argv[1]);
		return errno;
	}
	if (pipe(f_ds) == -1)
	{
		printf("Error: unable to create the Pipes!\n");
		return errno;
	}

	switch(fork()){
		case -1:
			printf("Error: unable to Fork!\n");
			return errno;
			break;
		case 0:
			close(f_ds[0]);
			// char ** foods = readFile(argv[1] , &Num_food);
			// srand(time(NULL));
			// // printf("%s\n", foods[rand()%Num_food]);
			// int ran = rand()%Num_food;
			printf("This is a Child\n");
			// strcpy(buf , "hello me !");
			// if (write(f_ds[1] , foods[ran] ,strlen(foods[ran])) != -1)
			// if (write(f_ds[1] , buf , BUFSIZE) != -1)
			// if (write(f_ds[1] , s , MAX_LINES) != -1)
			// {
			// 	printf("Message has been Sent\n");
			// }
			// else{
			// 	printf("Error: unable to write to pipe\n");
			// // }
			int x = write(f_ds[1] , s , MAX_LINES);
			printf("%d\n",x );
			printf("Looping\n");
			while(1);
			return 0;
			break;
		default:
				close(f_ds[0]);
				int f;
				while((f =wait(NULL)>0) >0);

				printf("waiting to read %d\n", f);
				if (read(f_ds[1] , s , MAX_LINES))
				{
					printf("The child requested %s to eat for Dinner\n" , buf);
				}
				else
				{
					printf("Error: unable to Read From pipe\n");
				}

				
			return errno;
		break;

	}



	return (EXIT_SUCCESS);
}

char ** readFile(char file [], int *length){
	char ** file_lines = malloc(sizeof(char *) * MAX_LINES);
	FILE * fd = fopen(file , "r");
	int index =0;
	if(file_lines == NULL){
		printf("Error: Out of Memory\n");
		exit(0);
	}
	if(fd == NULL){
		printf("Error: Unable to open %s\n", file);
		exit(0);
	}

	while(!feof(fd)){
		file_lines[index] = malloc(sizeof(char)*MAX_LINE_LENGTH);
		fgets(file_lines[index] , MAX_LINE_LENGTH , fd); 
		file_lines[index][strcspn(file_lines[index] , "\r\n")] = 0;
		printf("IN the Function: %s\n", file_lines[index] );
		index++;
	}

	// *length = index;
	return file_lines;
} 
