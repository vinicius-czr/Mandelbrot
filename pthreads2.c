#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "mandelbrot.h"

typedef struct {
    unsigned char *imagem;
    const Params *p;
    pthread_mutex_t trava;
    int proxima_linha;
} FilaCompartilhada;

static void *consumir_fila(void *dados) {
    FilaCompartilhada *fila = (FilaCompartilhada *)dados;

    for (;;) {
        int minha_linha;

        pthread_mutex_lock(&fila->trava);
        minha_linha = fila->proxima_linha;
        fila->proxima_linha = fila->proxima_linha + 1;
        pthread_mutex_unlock(&fila->trava);

        if (minha_linha >= fila->p->altura) {
            break;
        }

        calcular_linha(fila->imagem, minha_linha, fila->p);
    }

    return NULL;
}

int calcular_pthreads2(unsigned char *imagem, const Params *p) {
    int total_threads = p->num_threads;
    pthread_t *tid = malloc((size_t)total_threads * sizeof(pthread_t));
    FilaCompartilhada fila;
    int criadas = 0;
    int erro = 0;
    int i;

    if (tid == NULL) {
        fprintf(stderr, "Erro: falha ao alocar memoria para controle das threads.\n");
        return -1;
    }

    fila.imagem = imagem;
    fila.p = p;
    fila.proxima_linha = 0;

    if (pthread_mutex_init(&fila.trava, NULL) != 0) {
        fprintf(stderr, "Erro: falha ao inicializar o mutex da fila de trabalho.\n");
        free(tid);
        return -1;
    }

    for (i = 0; i < total_threads; i++) {
        if (pthread_create(&tid[i], NULL, consumir_fila, &fila) != 0) {
            fprintf(stderr, "Erro: falha ao criar a thread numero %d.\n", i);
            erro = 1;
            break;
        }
        criadas++;
    }

    for (i = 0; i < criadas; i++) {
        pthread_join(tid[i], NULL);
    }

    pthread_mutex_destroy(&fila.trava);
    free(tid);

    return erro ? -1 : 0;
}
