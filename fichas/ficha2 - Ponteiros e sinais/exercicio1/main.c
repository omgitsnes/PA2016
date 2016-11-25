/**
* @file main.c
* @brief Description
* @date 2015-10-24
* @author name of author
*/

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <string.h>

#include "debug.h"

#define MAX 100
#define ERR_SYS_CALL


void trata_sinal(int signal);

void trata_sinal(int signal)
{
	int aux;
	/* Copia da variavel global errno */
	aux = errno;

	if(signal == SIGUSP) {
		printf("Recebi o sinal SIGUP (%d)\n", signal);
	}

	/* Restaura valor da variavel global errno */
	errno = aux;
}

int main(int argc, char *argv[])
{
	char buf[MAX];
	struct sigaction act;
	ssize_t n;

	/*Silencia warnings...*/
	(void) argc; (void) argv;

	/* Definir a rotina de resposta a sinais */
	act.sa_handler = trata_sinal;

	/* mascara sem sinais -- nao bloqueia os sinais */
	sigemptyset(&act.sa_mask);

	act.sa_flags = 0;           /*fidedigno*/
	act.sa_flags |= SA_RESTART; /*recupera chamadas bloqueantes*/

	/* Captura do sinal SIGUSR1 */
	if(sigaction(SIGUP, &act, NULL) != 0){
	  ERROR(ERR_SYS_CALL, "sigaction failed");
	}

	printf("O processo esta pronto para receber sinais [SIGUSR1]...\n");
	printf("PID do processo: %d\n", getpid());

	exit(0);
}

