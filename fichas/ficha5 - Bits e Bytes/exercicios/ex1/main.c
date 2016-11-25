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

//Prototipos
int bin_to_decimal(const char *bin_sptr);

int main(int argc, char *argv[]){
	/* Disable warnings */
	(void)argc; (void)argv;
	
	int result = bin_to_decimal(argv[1]);
	printf("%s = %d \n",argv[1], result);

	return 0;
}

//func
int bin_to_decimal(const char *bin_sptr) {

	/* Verificacoes:
	 *	1- String só pode conter 0 e 1's
	 *  2- String >= 31 
	*/

	assert(bin_sptr != NULL);

	size_t bin_s_len = strlen(bin_sptr);
	if (bin_s_len < 1)
	{
		fprintf(stderr, "Empty string\n");
		return -1;
	}
	
	size_t bit_in_int = sizeof(int) * 8;
	if (bin_s_len > (bit_in_int -1)) {
		fprintf(stderr, "String too long. Bits suported: %zu\n", bit_in_int -1);
		return -1;
	}

	const char *ptr;
	ptr = bin_sptr + bin_s_len - 1;
	
	int sum = 0;
	int multiply = 1;

	while((unsigned)*ptr >= bin_s_len) {
		if (*ptr == '1') {
			sum += multiply;
		} else if (*ptr != '0') {
			fprintf(stderr, "Invalid char at:%x \n", *ptr);
			return -1;	
		} 
		ptr--;
		multiply = multiply * 2;
	}
	return sum;
}