#include <stdio.h>
#include <stdlib.h>
#include "mandelbrot.h"

#define LIMITE_MIN_DIMENSAO 1
#define LIMITE_MAX_DIMENSAO 20000
#define LIMITE_MIN_ITER     1
#define LIMITE_MAX_ITER     100000
#define LIMITE_MIN_THREADS  1
#define LIMITE_MAX_THREADS  256

static int converter_para_inteiro(const char *texto, const char *rotulo,
                                   int minimo, int maximo, int *destino) {
    char *ponteiro_final;
    long valor;

    if (texto == NULL || texto[0] == '\0') {
        fprintf(stderr, "Erro: %s nao pode ser vazio.\n", rotulo);
        return -1;
    }

    valor = strtol(texto, &ponteiro_final, 10);

    if (*ponteiro_final != '\0') {
        fprintf(stderr, "Erro: %s ('%s') nao e um numero inteiro valido.\n", rotulo, texto);
        return -1;
    }

    if (valor < minimo || valor > maximo) {
        fprintf(stderr, "Erro: %s deve estar entre %d e %d, mas foi recebido %ld.\n",
                rotulo, minimo, maximo, valor);
        return -1;
    }

    *destino = (int)valor;
    return 0;
}

static void mostrar_modo_de_uso(const char *nome_programa) {
    fprintf(stderr, "Uso: %s [largura] [altura] [max_iteracoes] [num_threads]\n", nome_programa);
}

int parse_args(int argc, char *argv[], Params *p) {
    const char *nome_programa = (argc > 0) ? argv[0] : "mandelbrot";

    if (argc != 5) {
        fprintf(stderr, "Erro: quantidade incorreta de argumentos (esperados 4, recebidos %d).\n",
                argc > 0 ? argc - 1 : 0);
        mostrar_modo_de_uso(nome_programa);
        return 1;
    }

    if (converter_para_inteiro(argv[1], "largura", LIMITE_MIN_DIMENSAO, LIMITE_MAX_DIMENSAO, &p->largura) != 0) {
        mostrar_modo_de_uso(nome_programa);
        return 2;
    }
    if (converter_para_inteiro(argv[2], "altura", LIMITE_MIN_DIMENSAO, LIMITE_MAX_DIMENSAO, &p->altura) != 0) {
        mostrar_modo_de_uso(nome_programa);
        return 2;
    }
    if (converter_para_inteiro(argv[3], "max_iteracoes", LIMITE_MIN_ITER, LIMITE_MAX_ITER, &p->max_iter) != 0) {
        mostrar_modo_de_uso(nome_programa);
        return 2;
    }
    if (converter_para_inteiro(argv[4], "num_threads", LIMITE_MIN_THREADS, LIMITE_MAX_THREADS, &p->num_threads) != 0) {
        mostrar_modo_de_uso(nome_programa);
        return 2;
    }

    return 0;
}
