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
#include <arpa/inet.h>
//Error handling
#define C_ERRO_PTHREAD_CREATE 1
#define C_ERRO_PTHREAD_JOIN 2
#define C_ERRO_PARAM 3
#define ERR_ARGS 4
//Prototipos


int main(int argc, char *argv[]){
	/* Disable warnings */
	(void)argc; (void)argv;

	assert(sizeof(short) == 2);

	short netshort = 0x1234;

	short ret = htons(netshort);
	printf("%s\n", ret == netshort ? "big endian" : "little endian");  

	return 0;
}

//func
