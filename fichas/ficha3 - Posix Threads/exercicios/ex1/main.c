/**
* @file main.c
* @brief Description
* @date 2015-10-24
* @author name of author
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

#define C_ERRO_PTHREAD_CREATE 1
#define C_ERRO_PTHREAD_JOIN 2
#define C_ERRO_PARAM 3
#define ERR_SYS_CALL 4

void *print(void *);

int main(int argc, char *argv[]){
	/* Disable warnings */
	(void)argc; (void)argv;
	
	for(int i = 0; i < 3; i++) {
		pid_t pid = fork();
		if (pid > 0) {
			
    	} else if (pid == 0) {

			pthread_t *tids = MALLOC(sizeof(pthread_t) * 2);

    		for (int i = 0; i < 2; i++) {
				if ((errno = pthread_create(&tids[i],NULL, print, NULL)) != 0) {
					ERROR(C_ERRO_PTHREAD_CREATE, "pthread_create() failed!");
				}
			}
			for (int i = 0; i < 2; i++) {	
				if ((errno = pthread_join(tids[i], NULL)) != 0) {
					ERROR(C_ERRO_PTHREAD_JOIN, "pthread_join() failed!");
				}
	   		}	
    		exit(0); // saida sem erros;
    	} else {
    		ERROR(ERR_SYS_CALL, "Erro no fork()");
    	}
	}


	return 0;
}

void *print(void *args)
{
	(void)args;
	printf("-----\n");
	printf("PID: %d\nPPID: %d\nTID: %lu\n", getpid(), getppid(), pthread_self());
	return NULL;
}

