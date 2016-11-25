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
#define N_THREADS 200

int CONTADOR = 0;

/* Prototipos */
void *race_condition(void *arg);

int main(int argc, char *argv[])
{
	/* Disable warnings */
	(void)argc; (void)argv;
	
	/* Declaracao das treads */
	pthread_t t1[N_THREADS];
	
	/* Criar de threads N_THREADS */
	int i;
	for (i = 0; i < N_THREADS; i++) {

		if ((errno = pthread_create(&t1[i],NULL,race_condition,NULL)) != 0) {
			ERROR(C_ERRO_PTHREAD_CREATE, "pthread_create() failed!");
		}
		//printf("Criada thread n: %d\n", i + 1);
	}
	
	for (i = 0; i < N_THREADS; i++) {
		if ((errno = pthread_join(t1[i], NULL)) != 0) {
			ERROR(C_ERRO_PTHREAD_JOIN, "pthread_join() failed!");
		}

	}

	printf("Contador: %d\n", CONTADOR);

	return 0;
}


void *race_condition(void *arg)
{
	(void)arg;
	int i;
	for (int i = 0; i < 1000; ++i)
	{
		/* code */
		CONTADOR++;
	}

	pthread_exit(NULL);
	return NULL;
}

