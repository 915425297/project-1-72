#ifndef _PENNSH_H
#define
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>
#define MAX_BUFFER 1024
#define BASE 10
/*
  pid the array of pid of child
  number the stage of pipeline needed
*/
pid_t pid[MAX_BUFFER];
int number = 0;
void controlCHandler(int signal);
int parseInput(char * t); // checking the input is valid or not, onlu check whether the pointer is null
void flushInput(); // if input exceeds 1024b, flush them
/*
divides the input by "|"
@paras t the char that divide with
@paras i the input string
@paras array where to store the pointer of the splited array
@return the number of segment
*/
int divideBySpace(char t, char * i, char ** array) {
	int count = 0, x = 0;
	while(i[x]) {
		if (i[x] == t) count++;
		x++;
	}
	count++;
	array = malloc(sizeof(char *) * count);
	x = 0;
	array[0] = i; // the first of the array pointed to i, the first of the characters
	flag = 1;
	while(i[x]) {
		if (i[x] == t) {
			while(i[x] == t) {
			i[x] = 0;
			x++;	
			}
			if (i[x]) array[flag] = &i[x];
			flag++;
			continue;
		}
		x++;
	}
	return count;
}

int divideBy(char i, char ** array1, char ** array2);
/*
this function will deal with pipe and redirection, including execute the divided string array and 
check out the input error
*/
void doPipeAndRedirection(char ** array1);
#endif
