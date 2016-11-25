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
#include <pthread.h> // uso das threads

#include "args.h" // use de args.ggo
#include "debug.h" // DEBUG, ERROR, etc
#include "memory.h" // memoria dinamica

#define C_ERRO_PTHREAD_CREATE 1
#define C_ERRO_PTHREAD_JOIN 2
#define C_ERRO_PARAM 3

typedef struct {
    char *filename;
    int thread_count;
    int block_size;
    unsigned long final_histogram[26]; // histograma final
} task_t;

typedef struct {
    int offset; // posicao_inicial
    unsigned long histogram[26];
    task_t *shared;
} param_t;

void *histogram(void *);

int main(int argc, char *argv[]){
	/* gengetopt */
    struct gengetopt_args_info args;
    cmdline_parser(argc, argv, &args);
    /* .gengetopt */
    
    if (args.threads_arg < 1)
    {
    	ERROR(C_ERRO_PARAM, "Invalid nr of threads");
    }

    if (args.blocksize_arg <= 0)
    {
    	ERROR(C_ERRO_PARAM, "Invalid block size");	
    }

    task_t shared;
    shared.filename = args.file_arg;
    shared.thread_count = args.threads_arg;
    shared.block_size = args.blocksize_arg;
    memset(shared.final_histogram, 0, sizeof(shared.final_histogram));

    /* Declaracao das treads e parametros para cada thread */
	pthread_t *tids = MALLOC(sizeof(pthread_t) * shared.thread_count);
	param_t *param = MALLOC(sizeof(param_t) * shared.thread_count);
	/* Cria n threads e aguarde que terminem
	 quando termina uma thread soma o histograma 
	 que a thead recolheu com o final 
	*/
	for (int i = 0; i < shared.thread_count; i++) {
		if ((errno = pthread_create(&tids[i],NULL, histogram, &param[i])) != 0) {
			ERROR(C_ERRO_PTHREAD_CREATE, "pthread_create() failed!");
		}
	}
	for (int i = 0; i < shared.thread_count; i++) {	
		if ((errno = pthread_join(tids[i], NULL)) != 0) {
			ERROR(C_ERRO_PTHREAD_JOIN, "pthread_join() failed!");
		}
        for (int j = 0; j < 26; ++j) {
            shared.final_histogram[j] += param[i].histogram[j];
        }
	}
    for (int i = 0; i < 26; ++i) {
        printf("%c: %lu\n", i + 'a', shared.final_histogram[i]);
    }


	FREE(param);
    FREE(tids);
    cmdline_parser_free(&args);
	return 0;
}


void *histogram(void *args) 
{
    (void)args;
	//param_t *param = arg;
	// FILE *input = fopen(filename, "r");
    // if (input == NULL) {
    //     ERROR(ERR_ARGS, "File not found: %s", filename);
    // }

    // int ch;
    // while ((ch = fgetc(input)) != EOF) {
    //     ch = tolower(ch);
    //     if (ch >= 'a' && ch <= 'z') {
    //         histogram[ch - 'a']++;
    //     }
    // }
    // if (!feof(input)) {
    //     ERROR(ERR_IO, "fgetc() failed");
    // }
    // fclose(input);

	//int ch = tolower(fgetch())

	//if (ch >= 'a' && ch <= 'z')
	//{
	//	histogram[ch - 'a']++
	//}
    return NULL;
}
	