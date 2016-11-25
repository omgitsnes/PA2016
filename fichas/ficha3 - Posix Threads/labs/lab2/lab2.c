#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include "debug.h"

#include <string.h>

int main (int argc, char *argv[])
{	
	
	/* Silencia os warnings */
	(void)argc;
	(void)argv;

	printf("Nome do Programa: %s\n", argv[0]);
	printf("PID do Processo: %d\n", getpid());
	printf("Nr de threads do processo atual:");
	fflush(stdout);
    char cmd[100];
    snprintf(cmd, sizeof(cmd), "ps -p %d -o nlwp |tail -1", getpid());
    system(cmd);


	exit(0);
}
