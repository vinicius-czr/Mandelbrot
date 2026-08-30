#include <stdio.h>
#include "mandelbrot.h"

int escrever_pgm(const char *nome_arquivo, const unsigned char *imagem, const Params *p) {
    FILE *arquivo = fopen(nome_arquivo, "w");
    int y, x;

    if (arquivo == NULL) {
        fprintf(stderr, "Erro: nao foi possivel criar o arquivo de saida '%s'.\n", nome_arquivo);
        return -1;
    }

    for (y = 0; y < p->altura; y++) {
        const unsigned char *linha = imagem + (size_t)y * (size_t)p->largura;

        for (x = 0; x < p->largura; x++) {
            fprintf(arquivo, x == 0 ? "%d" : " %d", linha[x]);
        }
        fprintf(arquivo, "\n");
    }

    if (ferror(arquivo)) {
        fprintf(stderr, "Erro: falha ao escrever no arquivo '%s'.\n", nome_arquivo);
        fclose(arquivo);
        return -1;
    }

    if (fclose(arquivo) != 0) {
        fprintf(stderr, "Erro: falha ao fechar o arquivo '%s'.\n", nome_arquivo);
        return -1;
    }

    return 0;
}
