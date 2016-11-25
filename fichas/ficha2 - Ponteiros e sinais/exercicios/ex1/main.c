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

#include "debug.h"
#include "memory.h"

#define ERR_ARGS 1
#define ERR_SYS_CALL 2

int continua = 1;

void trata_sinal(int sinal);

void trata_sinal(int sinal)
{
	int aux;
	aux = errno;

	if (sinal == SIGHUP){
		printf("Recebeu um sinal SUGHUP\n");
	} else {
		continua = 0;
	}

	errno = aux;
}

int main(int argc, char *argv[])
{
	//Check arguments
	if (argc != 2) {
		printf("Usage: %s <text file>\n", argv[0]);
		exit(ERR_ARGS);
	}

	//Signal handling
	struct sigaction act;

	act.sa_handler = trata_sinal;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);

	if (sigaction(SIGHUP, &act, NULL) < 0) {
		ERROR(1, "sigaction - ERROR");
	}

	printf("PID do processo: %d\n", getpid() );

	char cmd[100];
    snprintf(cmd, sizeof(cmd), "cat %s", argv[1]);
		
	while (continua) {
	  pause(); /* Espera bloqueante */
	  printf("Pause interrompido\n");
	  system(cmd);
	}

	exit(0);
}

