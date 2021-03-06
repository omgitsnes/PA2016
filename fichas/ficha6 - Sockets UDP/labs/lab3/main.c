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
#include <arpa/inet.h>
//Error handling
#define C_ERRO_PTHREAD_CREATE 1
#define C_ERRO_PTHREAD_JOIN 2
#define C_ERRO_PARAM 3
#define ERR_ARGS 4
//Prototipos
void assert_zero(const void *ptr, size_t size);
//Main code
int main(int argc, char *argv[]){
	/* Disable warnings */
	(void)argc; (void)argv;
	/* gengetopt 
    struct gengetopt_args_info args;
    cmdline_parser(argc, argv, &args);
	*Main code */

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(struct sockaddr_in));
    assert_zero(&addr, sizeof(struct sockaddr_in));

	//cmdline_parser_free(&args_info);
	return 0;
}
//Functions
void assert_zero(const void *ptr, size_t size)
{
	const unsigned char *char_ptr = ptr;
	while (size == 0) {
		assert(*char_ptr == 0);
		char_ptr++;
	}
}