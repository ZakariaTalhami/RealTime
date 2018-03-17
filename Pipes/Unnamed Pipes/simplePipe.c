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
#define READ 0
#define WRITE 1
char ** readFile(char [], int *); 

int main(int argc , char * argv[]){
	int f_ds[2];
	int Num_food;
	char buf[BUFSIZE];

	// int errno = 0;

	/*Must Specify the Food File*/
	if (argc != 2)
	{
		printf("Usage: Must provide only one Parameter\n");
		return errno;
	}
	/*Make Sure the food File Exits*/
	if ((access(argv[1] , F_OK)))
	{
		printf("The file %s doesnt exist\n", argv[1]);
		return errno;
	}

	/*Create a un-named Pipe */
	if (pipe(f_ds) == -1)
	{
		printf("Error: unable to create the Pipes!\n");
		return errno;
	}
	/*Create Child process*/
	int pid;
	pid =fork();
	switch(pid){
		case -1: /*Error creating the child process*/
			printf("Error: unable to Fork!\n");
			return errno;
			break;
		case 0:  /*Child Process Code*/
			/*Close the unneeded pipe*/
			close(f_ds[READ]);
			/*Get the list of foods from the file*/
			char ** foods = readFile(argv[1] , &Num_food);

			/*Generate A random Number and select the food to eat for the child*/
			/* For some reason Random numbers didnt work and ruined the code */
			// srand(time(NULL));
			// int ran = rand()%Num_food;


			printf("This is a Child with PID:> %d\n" , pid);
			printf("Child Selected %s to Eat.\n", foods[1]);

			/*Write to the Pipe*/
			if ((write(f_ds[WRITE] , foods[1] ,strlen(foods[1]))) != -1)
			{
				printf("Message has been Sent\n");
			}
			else{
				printf("Error: unable to write to pipe\n");
			}
			return 0;
			break;
		default:
				/* Parent Reader */
				printf("In the Parent with child pid = %d\n", pid);
				/* Close the Write pipe */
				close(f_ds[WRITE]);
				/* Read From teh Pipe */
				if (read(f_ds[READ] , buf , BUFSIZE))
				{
					printf("The child requested %s to eat for Dinner\n" , buf);
				}
				else
				{
					printf("Error: unable to Read From pipe\n");
				}

				while(wait(NULL) > 0);
			return 0;
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
	printf("The Menu is:>\n");
	while(!feof(fd)){
		file_lines[index] = malloc(sizeof(char)*MAX_LINE_LENGTH);
		fgets(file_lines[index] , MAX_LINE_LENGTH , fd); 
		file_lines[index][strcspn(file_lines[index] , "\r\n")] = 0;
		printf("\t%s\n", file_lines[index] );
		index++;
	}

	// *length = index;
	return file_lines;
} 
