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
#define C_ERRO_MUTEX 3
#define N_THREADS 200


/* Estrutura para armazenar o contador e mutex */

typedef struct {
	int counter;
	pthread_mutex_t mutex;
} task_t;


/* Prototipos */
void *race_condition(void *arg);

int main(int argc, char *argv[])
{
	/* Disable warnings */
	(void)argc; (void)argv;

	/* Declaracao das treads */
	pthread_t t1[N_THREADS];
	
	task_t param;
	param.counter = 0;


	/* Inicia o mutex */
	if ( (errno = pthread_mutex_init(&param.mutex, NULL)) != 0) {
		ERROR(C_ERRO_MUTEX, "pthread_mutex_init() failed");
	}


	/* Criar de threads N_THREADS */
	int i;
	for (i = 0; i < N_THREADS; i++) {

		if ((errno = pthread_create(&t1[i],NULL,race_condition,&param)) != 0) {
			ERROR(C_ERRO_PTHREAD_CREATE, "pthread_create() failed!");
		}
		//printf("Criada thread n: %d\n", i + 1);
	}
	
	for (i = 0; i < N_THREADS; i++) {	
		if ((errno = pthread_join(t1[i], NULL)) != 0) {
			ERROR(C_ERRO_PTHREAD_JOIN, "pthread_join() failed!");
		}

	}

	//Destruir mutex
	if ( (errno = pthread_mutex_destroy(&param.mutex)) != 0) {
		ERROR(C_ERRO_MUTEX, "pthread_mutex_destroy() failed");
	}


	printf("Contador: %d\n", param.counter);
	return 0;
}


void *race_condition(void *arg)
{
	task_t *param = arg;
	for (int i = 0; i < 1000; ++i)
	{
		/* lock mutex */
		if ((errno = pthread_mutex_lock(&(param->mutex))) != 0) {
			ERROR(C_ERRO_MUTEX, "pthread_mutex_lock() failed");
		}

		/* SECCAO CRITICA
			 incrementar contador */
		param->counter++;

		/* unlock mutex */
		if ((errno = pthread_mutex_unlock(&(param->mutex))) != 0) {
			ERROR(C_ERRO_MUTEX, "pthread_mutex_unlock() failed");
		}
	}

	pthread_exit(NULL);
	return NULL;
}