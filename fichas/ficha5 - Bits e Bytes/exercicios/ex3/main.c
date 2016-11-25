/**
* @file main.c
* @brief Description
* @date 2016-11-08
* @author Fernando Silva - 2140650
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <pthread.h>

#include "debug.h"
#include "memory.h"
#include "args.h"
//Error handling
#define C_ERRO_PTHREAD_CREATE 1
#define C_ERRO_PTHREAD_JOIN 2
#define C_ERRO_PARAM 3
#define ERR_ARGS 4
//Prototipos
int bit_n_to_zero(int input, size_t bit_to_zero);

int main(int argc, char *argv[]){
	/* Disable warnings */
	(void)argc; (void)argv;

	if (argc != 3) {
		printf("Usage: %s <number in hex> <bit to test>\n", argv[0]);
		exit(ERR_ARGS);
	}

	char *endptr = NULL;
	int number = strtol(argv[1], &endptr, 16);
	if (errno != 0)
	{
		ERROR(ERR_ARGS, "Invalid number");
	}
	size_t bit = atoi(argv[2]);
	printf("0x%04x: Bit(%zu) = 0x%04x\n", number, bit, bit_n_to_zero(number, bit));

	return 0;
}
//func
int bit_n_to_zero(int input, size_t bit_to_zero) 
{
	int mask = 1 << bit_to_zero;
	return input & ~mask;
}