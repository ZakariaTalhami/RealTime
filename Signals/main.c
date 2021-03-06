#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>

/* 
 * File:   newmain.c
 * Author: zakaria
 *
 * Created on March 11, 2018, 7:39 PM
 */
int Count;
void (* old_handler)(int);
void CC(int);
/*
 * 
 */
int main(int argc, char** argv) {

	if(argc == 1){
		printf("Usage: must specify a Count value\n");
		return 0;
	}
	if (argc > 2)
	{
		printf("Usage: Takes only one Value\n");
		return 0;
	}
	for (int i = 1; i < argc; ++i)
	{
		printf("%s\n", argv[i] );
	}
	char * p;
	Count = (int)strtol(argv[1] , &p ,  10);
	if ( *p != '\0')
	{
		printf("Usage: incorrect Count value\n");
		return 0;
	}
	printf("The Count Value is :> %d\n", Count );

	old_handler = signal(SIGINT , CC);
	while(Count > 0);
	printf("The Count has reached Zero\n");
	signal(SIGINT , old_handler);
    return (EXIT_SUCCESS);
}

void CC(int signum){
	signal(SIGINT , CC);
	Count--;
	printf("\rCount = %d\n" , Count);
}
