#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>

/* 
 * File:   newmain.c
 * Author: zakaria
 *
 * Created on March 11, 2018, 7:39 PM
 */
int Count;
void (* old_handler)(int);
void CC(int);
void timeout(int);
/*
 * 
 */
int main(int argc, char** argv) {

	printf("%d\n", getpid() );

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
	signal(SIGALRM , timeout);
	old_handler = signal(SIGINT , CC);
	alarm(10);
    while(Count > 0);
    alarm(0);
	printf("The Count has reached Zero\n");
	signal(SIGINT , old_handler);
    return (EXIT_SUCCESS);
}

void CC(int signum){
	sigset_t Maskset;
    sigset_t old_set;
	signal(SIGINT , CC);
	sigfillset(&Maskset);
    sigprocmask(SIG_SETMASK , &Maskset , &old_set);
	Count--;
	printf("\rCount = %d\n" , Count);
	sigprocmask(SIG_SETMASK , &old_set , &Maskset);
}
void timeout(int signum){
	printf("Time Ran Out\n");
	exit(0);
}