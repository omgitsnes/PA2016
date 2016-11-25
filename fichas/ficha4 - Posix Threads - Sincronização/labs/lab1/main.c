#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "debug.h"

#define C_ERRO_PTHREAD_CREATE           1
#define C_ERRO_PTHREAD_JOIN             2
#define C_ERRO_MUTEX_INIT               3
#define C_ERRO_MUTEX_DESTROY            4
#define C_ERRO_CONDITION_INIT           5
#define C_ERRO_CONDITION_DESTROY        6

#define MAX 5 /* Capacidade do buffer */
#define LIMITE 20 /* Total de elementos a produzir */

typedef struct 
{
    int buffer[MAX];
    int index_leitura;
    int index_escrita;
    int total;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} PARAM_T;


void *produtor(void *arg);
void *consumidor(void *arg);

int main(int argc, char *argv[]) 
{
    pthread_t t1, t2;
    PARAM_T param;

    (void)argc;(void)argv;

    /* Inicia o mutex */
	if ((errno = pthread_mutex_init(&param.mutex, NULL)) != 0)
		ERROR(C_ERRO_MUTEX_INIT, "pthread_mutex_init() failed!");

    /* Inicia variavel de condicao */
	if ((errno = pthread_cond_init(&param.cond, NULL)) != 0)
		ERROR(C_ERRO_CONDITION_INIT, "pthread_cond_init() failed!");

    /* Inicia os restantes parametros a passar 'as threads */
    memset(param.buffer, 0, sizeof(param.buffer));
    param.total = 0;
    param.index_escrita = 0;
    param.index_leitura = 0;

    /* Cria thread para executar o consumidor */
	if ((errno = pthread_create(&t1, NULL, consumidor, &param)) != 0)
		ERROR(C_ERRO_PTHREAD_CREATE, "pthread_create() failed!");
	
	/* Cria thread para executar o produtor */
	if ((errno = pthread_create(&t2, NULL, produtor, &param)) != 0)
		ERROR(C_ERRO_PTHREAD_CREATE, "pthread_create() failed!");

    /* Espera que todas as threads terminem */
	if ((errno = pthread_join(t1, NULL)) != 0)
		ERROR(C_ERRO_PTHREAD_JOIN, "pthread_join() failed!");
	
	if ((errno = pthread_join(t2, NULL)) != 0)
		ERROR(C_ERRO_PTHREAD_JOIN, "pthread_join() failed!");

	/* Destroi o mutex */
	if ((errno = pthread_mutex_destroy(&param.mutex)) != 0)
		ERROR(C_ERRO_MUTEX_DESTROY, "pthread_mutex_destroy() failed!");
	
	/* Destroi a condicao */
	if ((errno = pthread_cond_destroy(&param.cond)) != 0)
		ERROR(C_ERRO_CONDITION_DESTROY, "pthread_cond_destroy() failed!");

    return 0;
}

void *produtor(void *arg)
{
    PARAM_T *p = (PARAM_T *) arg; 
    int i;

    for (i=0; i<LIMITE; i++) {
		if ((errno = pthread_mutex_lock(&(p->mutex))) != 0) {
			WARNING("pthread_mutex_lock() failed\n");
			return NULL;
		}

        /* Espera que o buffer tenha espaco disponivel */
        while (p->total == MAX)
			if ((errno = pthread_cond_wait(&(p->cond), &(p->mutex))) != 0) {
				WARNING("pthread_cond_wait() failed");
				return NULL;
			}

        /* Coloca um valor no buffer */
        p->buffer[p->index_escrita] = random() % 100 + 1;
        printf(">> %d\n", p->buffer[p->index_escrita]);
        p->index_escrita = (p->index_escrita + 1) % MAX;
        p->total++;

        /* Notifica consumidores 'a espera */
        if (p->total == 1)
			if ((errno = pthread_cond_signal(&(p->cond))) != 0) {
				WARNING("pthread_cond_signal() failed");
				return NULL;
			}

        /* Sai da seccao critica */	
		if ((errno = pthread_mutex_unlock(&(p->mutex))) != 0) {
			WARNING("pthread_mutex_unlock() failed");
			return NULL;
		}

        /* Adormece entre 0 a 4 segundos */
        sleep(random() % 5);
    }
    return NULL;
}

void *consumidor(void *arg) 
{
    PARAM_T *p = (PARAM_T *) arg; 
    int i;

    for (i=0; i<LIMITE; i++) {
		if ((errno = pthread_mutex_lock(&(p->mutex))) != 0) {
			WARNING("pthread_mutex_lock() failed\n");
			return NULL;
		}

        /* Espera que o buffer tenha dados */
        while (p->total == 0)
			if ((errno = pthread_cond_wait(&(p->cond), &(p->mutex))) != 0) {
				WARNING("pthread_cond_wait() failed");
				return NULL;
			}

        /* Retira um valor no buffer */
        printf("<< %d\n", p->buffer[p->index_leitura]);
        p->index_leitura = (p->index_leitura + 1) % MAX;
        p->total--;

        /* Notifica produtores 'a espera */
        if (p->total == MAX-1)
			if ((errno = pthread_cond_signal(&(p->cond))) != 0) {
				WARNING("pthread_cond_signal() failed");
				return NULL;
			}

        /* Sai da seccao critica */	
		if ((errno = pthread_mutex_unlock(&(p->mutex))) != 0) {
			WARNING("pthread_mutex_unlock() failed");
			return NULL;
		}

        /* Adormece entre 0 a 4 segundos */
        sleep(random() % 5);
    }
    return NULL;
}
