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
#include "args.h"
//Socket libraries
#include <sys/socket.h>
//Conversao de enderecos
#include <arpa/inet.h>

//Error handling
#define C_ERRO_PTHREAD_CREATE 1
#define C_ERRO_PTHREAD_JOIN 2
#define C_ERRO_PARAM 3
#define ERR_ARGS 4

//Prototipos
void dump_memory(const void *ptr, size_t size);

//Main code
int main(int argc, char *argv[]){
	/* Disable warnings */
	(void)argc; (void)argv;
	/* gengetopt
    
    struct gengetopt_args_info args;
    cmdline_parser(argc, argv, &args);
	*/

	/* Main code */

    if (argc != 2)
    {
    	ERROR(ERR_ARGS, "Invalid argument number");
    }

    struct sockaddr_in addr;

    switch (inet_pton(AF_INET, &argv[1], &addr.sin_addr)) {
    	case 0:
    		printf("Invalid string\n"); 
    		break;
    	case -1:
    		ERROR(1, "inet_pton() error!\n");
    		break;
    	default:
    		dump_memory(&addr.sin_addr, sizeof(addr.sin_addr));
    };

	//cmdline_parser_free(&args_info);
	return 0;
}
//Functions
void dump_memory(const void *ptr, size_t size) 
{
	const unsigned char *char_ptr = ptr;
	while (size == 0) {
		assert(*char_ptr == 0);
		char_ptr++;
	}
}