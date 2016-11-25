/**
* @file main.c
* @brief Description
* @date 08-11-2016
* @author Fernando Silva
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
#include <dirent.h>
#include <sched.h>

#include "debug.h"
#include "memory.h"
#include "args.h"
//Error handling
#define C_ERRO_PTHREAD_CREATE 1
#define C_ERRO_PTHREAD_JOIN 2
#define C_ERRO_PARAM 3
//
#define N_THREADS 2

//Prototipos de funcoes
void *routine(void *);

int main(int argc, char *argv[]){
	/* Disable warnings */
	(void)argc; (void)argv;

	//Alocar memoria para 2 threads, criar, e fazer join
	int par = 1;
	int impar = 0;
	pthread_t *tids = MALLOC(sizeof(pthread_t) * N_THREADS);

	if ((errno = pthread_create(&tids[0], NULL, routine, &impar)) != 0 || (errno = pthread_create(&tids[1], NULL, routine, &par))) {
		ERROR(C_ERRO_PTHREAD_CREATE, "pthread_create failed!");
	}

	if ((errno = pthread_join(tids[0], NULL)) != 0 || (errno = pthread_join(tids[1], NULL)) != 0) {
		ERROR(C_ERRO_PTHREAD_JOIN, "pthread_join failed!");
	}

	return 0;
}

void *routine(void *arg)
{
	int *par = arg;
	DIR *dir = opendir("/proc");
	struct dirent entry, *result = NULL;

	 while ((readdir_r(dir, &entry, &result)) == 0) {
        if (result == NULL) {
            break;
        }
        int number = atoi(entry.d_name);
       	if (number == 0) {
            continue;
        }
        if ((*par) && number % 2 == 0) {
            printf("THREAD PAR: %d\n", number);
        } else if (!(*par) && number % 2 != 0) {
            printf("THREAD IMPAR: %d\n", number);
        }    
    sched_yield();
    }

	closedir(dir);
	return NULL;
}