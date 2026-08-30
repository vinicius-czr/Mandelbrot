#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mandelbrot.h"

static int parse_inteiro_positivo(const char *str, int *saida) {
    char *fim;
    long valor = strtol(str, &fim, 10);
    if (*fim != '\0' || fim == str) return -1;
    if (valor <= 0) return -1;
    *saida = (int)valor;
    return 0;
}

int parse_args(int argc, char *argv[], Config *cfg) {
    if (argc != 5) {
        fprintf(stderr, "Erro: numero incorreto de argumentos.\n");
        fprintf(stderr, "Uso: %s [largura] [altura] [max_iteracoes] [num_threads]\n", argv[0]);
        return 1;
    }

    if (parse_inteiro_positivo(argv[1], &cfg->largura) != 0) {
        fprintf(stderr, "Erro: largura invalida '%s'. Deve ser um inteiro positivo.\n", argv[1]);
        return 2;
    }
    if (parse_inteiro_positivo(argv[2], &cfg->altura) != 0) {
        fprintf(stderr, "Erro: altura invalida '%s'. Deve ser um inteiro positivo.\n", argv[2]);
        return 2;
    }
    if (parse_inteiro_positivo(argv[3], &cfg->max_iteracoes) != 0) {
        fprintf(stderr, "Erro: max_iteracoes invalido '%s'. Deve ser um inteiro positivo.\n", argv[3]);
        return 2;
    }
    if (parse_inteiro_positivo(argv[4], &cfg->num_threads) != 0) {
        fprintf(stderr, "Erro: num_threads invalido '%s'. Deve ser um inteiro positivo.\n", argv[4]);
        return 2;
    }

    return 0;
}