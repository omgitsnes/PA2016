/**
* @file main.c
* @brief Description
* @date 2016-11-08
* @author Fernando Silva - 2140650
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <signal.h>
#include <assert.h>
#include <fcntl.h>
#include <pthread.h>

#include "debug.h"
#include "memory.h"
#include "args.h"
//Socket libraries
#include <sys/types.h>
#include <sys/socket.h>

//Error handling
#define C_ERROR_SOCKET_CREATE 5
#define N_THREADS 2

//Function prototypes

int main(int argc, char *argv[]){
	/* Disable warnings */
	(void)argc; (void)argv;

	int socket1, socket2, socket3, socket4;
	
	//Create IPv4 UDP socket
	if ((socket1 = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
		ERROR(C_ERROR_SOCKET_CREATE, "socket() error!\n");
	}
	printf("Socket 1 descriptor: %d\n", socket1);

	//Criar um socket UDP / IPv6
	if ((socket2 = socket(AF_INET6, SOCK_DGRAM, 0)) == -1) {
		ERROR(C_ERROR_SOCKET_CREATE, "socket() error!\n");
	}
	printf("Socket 2 descriptor: %d\n", socket2);

	//Criar um socket TCP / IPv4
	if ((socket3 = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		ERROR(C_ERROR_SOCKET_CREATE, "socket() error!\n");
	}
	printf("Socket 3 descriptor: %d\n", socket3);

	//Criar um socket TCP/IPv6
	if ((socket4 = socket(AF_INET6, SOCK_STREAM, 0)) == -1) {
		ERROR(C_ERROR_SOCKET_CREATE, "socket() error!\n");
	}
	printf("Socket 4 descriptor: %d\n", socket4);

	close(socket1);
	close(socket2);
	close(socket3);
	close(socket4);

	return 0;
}
