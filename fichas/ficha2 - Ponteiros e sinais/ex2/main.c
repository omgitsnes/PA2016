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

int main(int argc, char *argv[]){
	/* Disable warnings */
	(void)argc; (void)argv;

	/* Main code */

	//Tratas os sinais SIGSR1 e SIGINT
	struct sigaction sa;
	sa.sa_handler = handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);

	...


	//Criar um processo filho
	if(pid == 0) {
		child_action
	}


	//Enviar ao pai o sinal SIGUSR1 de 5 em 5 seg.
	//Processo pai
	//Sempre recebe o sinal SIGUSR1 -> escreve a data atual
	//Se receber SIGINT termina o processo filho e sai




	return 0;
}

