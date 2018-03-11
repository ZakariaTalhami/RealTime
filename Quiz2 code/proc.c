/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: zakaria
 *
 * Created on March 7, 2018, 8:38 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define FIFO_FILE "Temp"

void Process(int);
FILE * fileptr;
FILE * fifoptr;
int *buffer;
int filelen =0;
int pid, temp;

/*
 * 
 */
int main(int argc, char** argv) {
    /*Create a Array to store the numbers from the file*/
    buffer = (int *) malloc((100)*sizeof(int));
    /*Open the  File*/
    fileptr = fopen("list.txt" , "r");
    /*Create the Named Pipe*/
    mkfifo(FIFO_FILE , 0666);
    // fifoptr = fopen(FIFO_FILE , "r");
    /*Read all the Numbers from the file and addd to the array*/
    while(!feof(fileptr)){
    	fscanf(fileptr , "%d" , &buffer[filelen]);
    	/*Track the files length*/
        filelen++;
    }
    /*Create the Sub processes*/
    for (int i = 0; i < 4; ++i)
    {	
    	pid = fork();
    	if (pid ==0)
    	{
    		Process(i);
    		printf("Child\n");
    		break;
    	}
    }
   
    /*Wait for the Children to Finish Processing*/
    if (pid != 0)
    {

	    for (int i = 0; i < 4; ++i)
	    {
	    	pid = wait();
	    	printf("Process: %d finished\n", pid );
	    }
        // fifoptr = fopen(FIFO_FILE , "r");
        // int section;
        // double avg;
        // // for (int i = 0; i < 4; ++i)
        // // {
        //     fscanf(fifoptr , "%d" , &section);
        //     fscanf(fifoptr , "%lf" , &avg);
        //     printf("%d\t%lf\n", section , avg);
        // // }
        //     fclose(fifoptr);
    }
    printf("Process: %d exits\n", getpid() );
    
    return (EXIT_SUCCESS);
}


void Process(int section ){
    int start = section*(filelen/4);
    int end = (section+1)*(filelen/4);
    double sum = 0;
    double avg;
    // printf("The Processing list (%d) of process (%d) :>\n", section , getpid() );
    for (int i = start; i < (section+1)*(filelen/4); ++i)
    {
        sum += buffer[i];
        // printf("\t-%d\n", buffer[i]);
    }

    avg = sum / (end - start);
    // printf("The Avg (%lf) of process (%d) :>\n", avg , getpid() );
    FILE * fifoptr2;
    fifoptr2 = fopen(FIFO_FILE , "w");
    fprintf(fifoptr2, "%d\n", section );
    fprintf(fifoptr2, "%lf\n", avg );
    printf("Added the Avg (%d)\n", section);
    fclose(fifoptr2);
    // while(1);
}   