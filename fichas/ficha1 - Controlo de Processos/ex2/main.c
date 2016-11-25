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
#include "args.h"

#define ERR_SYS_CALL 1
#define ERR_ARGS 2

int main(int argc, char *argv[]){

    struct gengetopt_args_info args;
    cmdline_parser(argc, argv, &args);

    // Verifica se o nr de processos é um nr valido
    // Caso nao se verifique termina a execucao do programa

    int n = args.num_procs_arg;
    if (n <= 0) {
        printf("Invalid number of processes: %d\n", n);
        exit(ERR_ARGS);
    }

    // Cria "n" processos e apresenta o PID

    for (int i = 0; i < n; i++) {
    	pid_t pid = fork();
    	if (pid > 0) {
    		printf("Criado o processo #%d (PID = %d)\n", i + 1, pid);
    	} else if (pid == 0) {
    		printf("PROCESSO #%d EXECUTADO\n", i + 1);
    		exit(0); // saida sem erros;
    	} else {
    		ERROR(ERR_SYS_CALL, "Erro no fork()");
    	}
    }


	return 0;
}

