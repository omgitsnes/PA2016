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
#define ERR_SYS_CALL 1

int main(int argc, char *argv[]){
	/* Disable warnings */
	(void)argc; (void)argv;

	/* Main code */
	printf("PID=%d (%d)\n", getpid(), getppid());
	long result = sysconf(_SC_OPEN_MAX);
	if (result == -1) {
        ERROR(ERR_SYS_CALL, "sysconf() failed");
    }
    // Garantia que a chamada foi executada com sucesso
    printf("Max open files: %ld\n", result);



	return 0;
}

