#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "mandelbrot.h"

typedef struct {
    unsigned char *imagem;
    const Params *p;
    int linha_de;
    int linha_ate; /* exclusivo */
} BlocoTrabalho;

static void *processar_bloco(void *dados) {
    BlocoTrabalho *bloco = (BlocoTrabalho *)dados;
    int y;

    for (y = bloco->linha_de; y < bloco->linha_ate; y++) {
        calcular_linha(bloco->imagem, y, bloco->p);
    }

    return NULL;
}

int calcular_pthreads1(unsigned char *imagem, const Params *p) {
    int total_threads = p->num_threads;
    pthread_t *tid = malloc((size_t)total_threads * sizeof(pthread_t));
    BlocoTrabalho *blocos = malloc((size_t)total_threads * sizeof(BlocoTrabalho));
    int criadas = 0;
    int erro = 0;
    int i;

    if (tid == NULL || blocos == NULL) {
        fprintf(stderr, "Erro: falha ao alocar memoria para controle das threads.\n");
        free(tid);
        free(blocos);
        return -1;
    }

    for (i = 0; i < total_threads; i++) {
        /* distribui as linhas em blocos o mais parecidos possivel, mesmo quando altura nao eh multiplo de total_threads */
        blocos[i].linha_de  = (int)((long)p->altura * i / total_threads);
        blocos[i].linha_ate = (int)((long)p->altura * (i + 1) / total_threads);
        blocos[i].imagem = imagem;
        blocos[i].p = p;

        if (pthread_create(&tid[i], NULL, processar_bloco, &blocos[i]) != 0) {
            fprintf(stderr, "Erro: falha ao criar a thread numero %d.\n", i);
            erro = 1;
            break;
        }
        criadas++;
    }

    for (i = 0; i < criadas; i++) {
        pthread_join(tid[i], NULL);
    }

    free(tid);
    free(blocos);

    return erro ? -1 : 0;
}
