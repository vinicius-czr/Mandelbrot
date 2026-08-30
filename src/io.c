#include <stdio.h>
#include "mandelbrot.h"

int escrever_pgm(const char *nome_arquivo, unsigned char *pixels, int largura, int altura) {
    FILE *arquivo = fopen(nome_arquivo, "w");
    if (arquivo == NULL) {
        fprintf(stderr, "Erro: nao foi possivel criar o arquivo de saida '%s'.\n", nome_arquivo);
        return -1;
    }

    for (int y = 0; y < altura; y++) {
        for (int x = 0; x < largura; x++) {
            fprintf(arquivo, "%d", pixels[y * largura + x]);
            if (x < largura - 1) {
                fprintf(arquivo, " ");
            }
        }
        fprintf(arquivo, "\n");
    }

    fclose(arquivo);
    return 0;
}

int registrar_tempo(const char *nome_arquivo, const char *label, double segundos) {
    FILE *arquivo = fopen(nome_arquivo, "a");
    if (arquivo == NULL) {
        fprintf(stderr, "Erro: nao foi possivel abrir o arquivo de tempos '%s'.\n", nome_arquivo);
        return -1;
    }

    fprintf(arquivo, "%s: %.6f segundos\n", label, segundos);

    fclose(arquivo);
    return 0;
}